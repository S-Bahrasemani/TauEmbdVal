## JobOptions for Tau embedding validation :
## imports (be careful as the class is in under TauEmbd scope)
from TauEmbdVal.TauEmbdValConf import TauEmbd__TauEmbdVal

## read xAOD or ESD files
import AthenaPoolCnvSvc.ReadAthenaPool
svcMgr.EventSelector.InputCollections = ["/home/sbahrase/WorkDesk/SAMPLES/xAODs/MC15/HTauTau/TrainingSamples/GGH/mc15_13TeV.341224.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_ggH120_tautauIncl.merge.AOD.e4044_s2608_r6765_r6282/AOD.05774880._000002.pool.root.1"]

## specify the number of events to be proccesed:
theApp.EvtMax = 100

## add your algorithm to the sequencer
# fetch the  AthAlgSeq, one of the master sequences where all algs should be added to
algseq = CfgMgr.AthSequencer("AthAlgSeq")

## instanciate your algorithm (python object which lives in genConf/../)
embdvalalg = TauEmbd__TauEmbdVal()
embdvalalg.OutputLevel = INFO

embdvalalg.TauContainerName = "TauJets"
embdvalalg.PhotonContainerName = "Photons"
embdvalalg.ElectronContainerName = "Electrons"

## MET and Muon containers seem to be not ready for use !!
embdvalalg.MuonContainerName = "Muons"
embdvalalg.METContainerName = "MET_Calo"

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

svcMgr.THistSvc.Output += ["TauEmbdVal DATAFILE='Test01.root' OPT='RECREATE'"]
#svcMgr.THistSvc.PrintAll = True
svcMgr.THistSvc.OutputLevel = INFO
