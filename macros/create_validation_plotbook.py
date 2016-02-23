#! /usr/bin/env python

## author: Sina bahrasemani <sina.bahrasemani@cern.ch>

import ROOT
import os
import subprocess
import argparse

def CreateEmptyPlot( filename ):
    can = ROOT.TCanvas("","",860,900)
    can.SaveAs( filename )

## set the bound for plotting
def SetBounds( refHist, testHist ):
    maximum = max(refHist.GetMaximum(), testHist.GetMaximum())
    maximum = maximum + 0.1*abs(maximum)
    minimum = min(refHist.GetMinimum(), testHist.GetMinimum())
    minimum = minimum - 0.1*abs(minimum)
    refHist.SetMinimum(minimum)
    refHist.SetMaximum(maximum)
    return refHist

## retrieve histograms saved in the root files
def get_hists(path='', refName='', testName='', pName='', var=''):

    # read TFiles
    ref_file = ROOT.TFile.Open(path+refName, 'READ')
    test_file = ROOT.TFile.Open(path+testName, 'READ')

    # go to the specified directory (same as the particle name) and the get the TH1Ds.
    ref_h = ref_file.GetDirectory( pName).Get( pName+"_"+var )
    test_h = test_file.GetDirectory( pName).Get( pName+"_"+var )
    
    return ref_h, test_h

def MakeComparisonPlot( refHist, testHist, plotName, path, doNorm = True, doRatio = True ):
    labelsize = 0.14
    titlesize = 0.18
    #check that test histogram exists
    if not refHist:
        print('WARNING Ref Histogram not found: '+plotName)

    if not testHist:
        print('WARNING Test histogram not found: '+plotName)
        print('        Creating empty plot')
        CreateEmptyPlot( path+'/'+plotName+'.png' )
        return

    #if doNorm set, scale hists to area = 1
    if refHist:
        refint = refHist.Integral()
    else:
        refint = 0
    testint = testHist.Integral()

    if doNorm:
        if refint != 0:
           refHist.Scale( 1./refint )
        elif refHist:
           print( 'WARNING empty ref plot ' + plotName )

        if testint != 0:
           testHist.Scale( 1./testint )
        else:
           print( 'WARNING empty test plot ' + plotName )
    #ROOT.gROOT.ForceStyle()
    canvas = ROOT.TCanvas("", "", 1000, 800)# , 860, 900 )
    canvas.SetLeftMargin( 0 )
    # canvas.SetFillColor(ROOT.kGreen);
    # canvas.SetLineColor(ROOT.kBlack);
    # canvas.SetHighLightColor(ROOT.kRed)
    
    padMain = ROOT.TPad( 'padMain', 'padMain', 0, 0.30, 1, 0.95 )
    padMain.SetBottomMargin( 0 )
    padMain.Draw()

    if doRatio:
        padRatio = ROOT.TPad( 'padRatio', 'padRatio', 0, 0.1, 1, 0.30 )
        padRatio.SetTopMargin( 0 )
        padRatio.SetBottomMargin( 0.13)
        padRatio.Draw()
    ROOT.TLine()
    padMain.cd()

    if refint > 0 and testint > 0:
        chi = testHist.Chi2Test( refHist, 'WW' )
        if chi < 0.05:    
            padMain.SetFillColor(ROOT.kRed -7)
            padRatio.SetFillColor(ROOT.kRed-7)

        else:
            
            padMain.SetFillColor(ROOT.kGreen -7)
            padRatio.SetFillColor(ROOT.kGreen-7)

    leg = ROOT.TLegend( 0.82, 0.77, 0.96, .96 )
    leg.SetFillColor( ROOT.kWhite )
    leg.SetTextSizePixels(20)

    testHist.SetMarkerColor(ROOT.kBlue)
    testHist.SetLineColor(ROOT.kBlue)
    leg.AddEntry(testHist, "test",'P')
    testHist.GetYaxis().SetTitleOffset( 1.4 )
    testHist.GetYaxis().SetTitleSize( labelsize*0.4 )
    testHist.SetLabelSize( labelsize*0.4, 'Y' )
    testHist.SetFillStyle(3001)
 
    refHist.SetMarkerColor(ROOT.kBlack)
    refHist.SetLineColor(ROOT.kBlack)
    leg.AddEntry(refHist, "ref", 'P') 
    refHist = SetBounds(refHist, testHist)
    refHist.Draw("HIST")# PESAME
    testHist.Draw("HISTSAME")
    leg.Draw()

    ## ks & chi^2 values
    if refint > 0 and testint > 0:
        # ks = testHist.KolmogorovTest( refHist, 'WW' )
        # kstext = ROOT.TLatex( 0.18, .955, 'KS = %0.3f'%(ks))
        # kstext.SetNDC(ROOT.kTRUE)
        # kstext.SetTextSize(0.055)
        # kstext.Draw()
        chitext = ROOT.TLatex( 0.3, .955, 'p(#chi^{2}) = %0.3f'%(chi))
        chitext.SetNDC(ROOT.kTRUE)
        chitext.SetTextSize(0.060)
        chitext.Draw()
    if refint == 0 or testint == 0:
        print( 'WARNING No ratio plot available: '+ plotName )
    elif not doRatio:
        print( 'INFO skipping ratio plot for '+ plotName )
    else:
        padRatio.cd()
        ratioHist = testHist.Clone()
        ratioHist.Divide( refHist )
        ratioHist.SetMarkerColor( ROOT.kBlack )
        ratioHist.SetMarkerStyle( 21)
        
        #ratioHist.SetMaximum(1.5)
        #ratioHist.SetMinimum(0.5)
        ratioHist.SetLineColor( ROOT.kBlack )
        ratioHist.GetYaxis().SetTitle( "test / ref" )
        xtitle = ratioHist.GetName()#GetXaxis().GetTitle()

        ratioHist.GetXaxis().SetTitleSize( titlesize )
        ratioHist.GetYaxis().SetTitleSize( labelsize )
        ratioHist.SetLabelSize( labelsize, 'XY' )
        #ratioHist.GetXaxis().SetTitleOffset( 1.0 )
        ratioHist.GetYaxis().SetTitleOffset( .5 )
        ratioHist.Draw("p") #PE
        ratioHist.GetXaxis().SetTitle(xtitle)
      
        lineRatio = ROOT.TLine( ratioHist.GetXaxis().GetXmin(), 1,
                                ratioHist.GetXaxis().GetXmax(), 1 )
        lineRatio.SetLineColor( ROOT.kRed )
        lineRatio.SetLineWidth( 2 )
        lineRatio.Draw("same")

    canvas.cd()
    canvas.SaveAs( path + '/' + plotName + '.png' )
    del canvas, padRatio, padMain

## main function to run to produce plot book.
def main():
    #parse options
    parser = argparse.ArgumentParser()
    parser.add_argument( '-r', '--reference', help = 'reference sample ROOT file' )
    parser.add_argument( '-t', '--test', required=True, help = 'test sample ROOT file' )
    args = parser.parse_args()

    ## read TFiles, go to the particle directory and retrieve TH1D objects.
    # refhist = get_hists(path=path, refName=refName, testName=testName, pName=pName, var=var)
    # print refhist.Integral()
    
    particles = ["Tau", "Muon","Electron", "Jet", "Photon","MET"] 
    vars_all  = ["_n", "_et", "_eta", "_phi", "_lead_et", "_lead_eta", "_lead_phi"]
    vars_met  = ["_Et", "_Ex", "_Ey", "_SumEt"]
    outdir= "./plots"
    ref_file  = ROOT.TFile.Open(args.reference, 'READ')
    test_file = ROOT.TFile.Open(args.test, 'READ')
            
    for p in particles:
        if p=="MET":
            vars= vars_met
        else:
            vars= vars_all
        for v in vars:
            refhist  = ref_file.GetDirectory( p).Get( p+v)
            testhist = test_file.GetDirectory( p).Get( p+v)
            HistName = refhist.GetName()
            MakeComparisonPlot( refhist, testhist, HistName, outdir, doNorm = True, doRatio = True )
    ref_file.Close()
    test_file.Close()

    subprocess.call(["montage -tile 2x2 -geometry 1600  ./plots/*.png PlotBook.pdf"], shell=True)

if __name__ == "__main__":
    ROOT.gROOT.Macro("rootlogon.C")
    ROOT.gROOT.SetBatch()
    # # to get rid of Stats box on plots.
    # import ROOT
    # ROOT.gStyle.SetOptStat(0)
    # ROOT.gROOT.ForceStyle()
    main()
