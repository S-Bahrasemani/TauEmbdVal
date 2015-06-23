
## JobOptions for Tau embedding validation :

## imports 
import AthenaPoolCnvSvc.ReadAthenaPool
from TauEmbdVal.TauEmbdValConf import TauEmbdValAlg

svcMgr.EventSelector.InputCollections = ["/cluster/warehouse/sbahrase/Samples/AOD_reco_gg_H_100_test.pool.root.1"]

## specify the number of events to be proccesed:
theApp.EvtMax = 100

## add your algorithm to the sequencer
# fetch the  AthAlgSeq, one of the master sequences where all algs should be added to
algseq = CfgMgr.AthSequencer("AthAlgSeq")

## instanciate your algorithm (python object which lives in genConf/../)
embdvalalg = TauEmbdValAlg("taualg")

## Define your output file name and stream name
rootStreamName = "TauEmbdValHistoStream"
rootFileName   = "TauEmbdValHists.root"
embdvalalg.RootStreamName   = rootStreamName
embdvalalg.RootDirName      = "/Hists"

## Add your algorithm to the athena algorithm sequencer object; BE CAREFUL IT'S PYTHON OBJECT ! JUST USE ASSIGNING
algseq += embdvalalg

## Define your output root file using MultipleStreamManager
# ====================================================================
from OutputStreamAthenaPool.MultipleStreamManager import MSMgr
TauEmbdValHistoStream = MSMgr.NewRootStream( rootStreamName, rootFileName )



