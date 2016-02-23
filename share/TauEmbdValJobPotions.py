## JobOption for Tau-embedding validation 

# import argparse
# parser = argparse.ArgumentParser()
# parser.add_argument('-r', '--reffile' , default=filedir+"myDESD_ZMUMU.root")
# parser.add_argument('-t', '--testfile', default=filedir+"RerecoFile.root")
# args = parser.parse_args()

sampledir = "/afs/cern.ch/user/h/hbaluchb/WWork/TauEmbd/EmbdValSamples/"
reffile= sampledir+"myDESD_ZMUMU.root"
testfile= sampledir+"RerecoFile.root"

## imports (be careful as the class is in under TauEmbd scope)
from TauEmbdVal.TauEmbdValConf import TauEmbd__TauEmbdVal

## read xAOD or ESD files
import AthenaPoolCnvSvc.ReadAthenaPool
svcMgr.EventSelector.InputCollections = [testfile]

## specify the number of events to be proccesed:
theApp.EvtMax = -1

## add your algorithm to the sequencer
# fetch the  AthAlgSeq, one of the master sequences where all algs should be added to
algseq = CfgMgr.AthSequencer("AthAlgSeq")

## instanciate your algorithm (python object which lives in genConf/../)
embdvalalg = TauEmbd__TauEmbdVal()
embdvalalg.OutputLevel = INFO

#embdvalalg.JetContainerName      = ""
embdvalalg.TauContainerName      = "TauJets"
embdvalalg.PhotonContainerName   = "Photons"
embdvalalg.ElectronContainerName = "Electrons"

## MET and Muon containers seem to be not ready for use !!
embdvalalg.MuonContainerName = "Muons"
embdvalalg.METContainerName  = "MET_Calo"

from AthenaCommon.AppMgr import ToolSvc
ToolSvc += embdvalalg

## be careful the calss name should be passed in the following
## it's the one that has been used to register Histograms
monMan = CfgMgr.AthenaMonManager("TauEmbdVal")
monMan.AthenaMonTools += [ embdvalalg ]
algseq += monMan    

from AthenaCommon.AppMgr import ServiceMgr
from GaudiSvc.GaudiSvcConf import THistSvc
ServiceMgr += THistSvc()

svcMgr.THistSvc.Output += ["TauEmbdVal DATAFILE='ValTestHists.root' OPT='RECREATE'"]
#svcMgr.THistSvc.PrintAll = True
svcMgr.THistSvc.OutputLevel = INFO

