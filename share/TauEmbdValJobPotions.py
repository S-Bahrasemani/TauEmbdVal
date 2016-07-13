## JobOption for Tau-embedding validation 

# import argparse
# parser = argparse.ArgumentParser()
# parser.add_argument('-r', '--reffile' , default=filedir+"myDESD_ZMUMU.root")
# parser.add_argument('-t', '--testfile', default=filedir+"RerecoFile.root")
# args = parser.parse_args()

sampledir = "/afs/cern.ch/user/h/hbaluchb/WWork/TauEmbd/EmbdValSamples/"
refName = "user.dta.8193395.EXT0._000732.DAOD_EMBLHIM.pool.root" ## "myDESD_ZMUMU.root"
testName= "user.dta.8193395.EXT0._000733.DAOD_EMBLHIM.pool.root" ## "RerecoFile.root"
RefFile= sampledir + refName
TestFile= sampledir + testName
## imports (be careful as the class is in under TauEmbd scope)
from TauEmbdVal.TauEmbdValConf import TauEmbd__TauEmbdVal

## read xAOD or ESD files
import AthenaPoolCnvSvc.ReadAthenaPool
from AthenaCommon.AppMgr import ServiceMgr
from GaudiSvc.GaudiSvcConf import THistSvc
from AthenaCommon.AppMgr import ToolSvc
from glob import glob
svcMgr.EventSelector.InputCollections = [TestFile] 

# specify the number of events to be proccesed:
theApp.EvtMax = 1000

###### MET 
from METUtilities.METMakerConfig import getMETMakerAlg
metAlg = getMETMakerAlg('AntiKt4EMTopo',20e3)
metAlg.METName = 'MET_Reco_AntiKt4EMTopo'

metAlg_truth = getMETMakerAlg('Truth_AntiKt4EMTopo',20e3)
metAlg_truth.METSoftClName = 'SoftTruthAll'
metAlg_truth.METSoftTrkName = 'SoftTruthCharged'
metAlg_truth.METName = 'MET_Truth_AntiKt4EMTopo'

# add your algorithm to the sequencer
# fetch the  AthAlgSeq, one of the master sequences where all algs should be added to
algseq = CfgMgr.AthSequencer("AthAlgSeq")
algseq += metAlg
algseq += metAlg_truth

write_xAOD = True
if write_xAOD:
    from OutputStreamAthenaPool.MultipleStreamManager import MSMgr
    xaodStream = MSMgr.NewPoolRootStream( "StreamXAOD", "xAOD.METMaker.pool.root" )
    #
    xaodStream.AddItem('xAOD::MissingETContainer#MET_Reco_AntiKt4EMTopo')
    xaodStream.AddItem('xAOD::MissingETAuxContainer#MET_Reco_AntiKt4EMTopoAux.')
    #
    xaodStream.AddItem('xAOD::MissingETContainer#MET_Truth_AntiKt4EMTopo')
    xaodStream.AddItem('xAOD::MissingETAuxContainer#MET_Truth_AntiKt4EMTopoAux.')
    #
    xaodStream.AddItem('xAOD::MissingETContainer#MET_Truth')
    xaodStream.AddItem('xAOD::MissingETAuxContainer#MET_TruthAux.')
    #
    xaodStream.Print()


# instanciate your algorithm (python object which lives in genConf/../)
embdvalalg = TauEmbd__TauEmbdVal()
embdvalalg.OutputLevel = INFO

#embdvalalg.JetContainerName      = ""
embdvalalg.TauContainerName      = "TauJets"
embdvalalg.PhotonContainerName   = "Photons"
embdvalalg.ElectronContainerName = "Electrons"

# MET and Muon containers seem to be not ready for use !!
embdvalalg.MuonContainerName = "Muons"
embdvalalg.METContainerName  = "MET_Calo"


# MET_LocHadTopo
# MET_Track
# MET_Truth
# MET_Calo

ToolSvc += embdvalalg
               
# be careful the calss name should be passed in the following
# it's the one that has been used to register Histograms
monMan = CfgMgr.AthenaMonManager("TauEmbdVal")
monMan.AthenaMonTools += [ embdvalalg ]
algseq += monMan    

ServiceMgr += THistSvc()

# setup TTree registration Service
# save ROOT histograms and Tuple
from GaudiSvc.GaudiSvcConf import THistSvc
from AnalysisTools.AnalysisToolsConf import AANTupleStream

ServiceMgr.THistSvc.Output += ["TauEmbdVal DATAFILE='ValTestHists.root' OPT='RECREATE'"]
svcMgr.THistSvc.PrintAll = True
ServiceMgr.THistSvc.AuditFinalize = True

svcMgr.THistSvc.OutputLevel = INFO

