#Wed Nov 25 11:36:00 2015"""Automatically generated. DO NOT EDIT please"""
from GaudiKernel.GaudiHandles import *
from GaudiKernel.Proxy.Configurable import *

class TauEmbd__TauEmbdVal( ConfigurableAlgTool ) :
  __slots__ = { 
    'MonitorService' : 'MonitorSvc', # str
    'OutputLevel' : 7, # int
    'AuditTools' : False, # bool
    'AuditInitialize' : False, # bool
    'AuditStart' : False, # bool
    'AuditStop' : False, # bool
    'AuditFinalize' : False, # bool
    'EvtStore' : ServiceHandle('StoreGateSvc'), # GaudiHandle
    'DetStore' : ServiceHandle('StoreGateSvc/DetectorStore'), # GaudiHandle
    'UserStore' : ServiceHandle('UserDataSvc/UserDataSvc'), # GaudiHandle
    'ProcessNEvents' : 0, # int
    'histoPathBase' : '', # str
    'PreScale' : 0, # int
    'TriggerChain' : '', # str
    'TriggerGroup' : '', # str
    'ManagerName' : 'AthenaMonManager', # str
    'TrigDecisionTool' : PublicToolHandle(''), # GaudiHandle
    'TriggerTranslatorTool' : PublicToolHandle(''), # GaudiHandle
    'FilterTools' : PublicToolHandleArray([]), # GaudiHandleArray
    'EnableLumi' : False, # bool
    'DetailLevel' : 1, # int
    'FileKey' : '', # str
    'DataType' : 'userDefined', # str
    'Environment' : 'noOutput', # str
    'JetContainerName' : 'AntiKt4EMTopoJets', # str
    'ElectronContainerName' : 'ElectronCollection', # str
    'PhotonContainerName' : 'PhotonCollection', # str
    'MuonContainerName' : 'Muons', # str
    'TauContainerName' : 'TauJets', # str
    'TrackContainerName' : 'InDetTrackParticles', # str
    'VertexContainerName' : 'PrimaryVertices', # str
    'METContainerName' : 'MET_RefFinal', # str
  }
  _propertyDocDct = { 
    'DetStore' : """ Handle to a StoreGateSvc/DetectorStore instance: it will be used to retrieve data during the course of the job """,
    'UserStore' : """ Handle to a UserDataSvc/UserDataSvc instance: it will be used to retrieve user data during the course of the job """,
    'EvtStore' : """ Handle to a StoreGateSvc instance: it will be used to retrieve data during the course of the job """,
  }
  def __init__(self, name = Configurable.DefaultName, **kwargs):
      super(TauEmbd__TauEmbdVal, self).__init__(name)
      for n,v in kwargs.items():
         setattr(self, n, v)
  def getDlls( self ):
      return 'TauEmbdVal'
  def getType( self ):
      return 'TauEmbd::TauEmbdVal'
  pass # class TauEmbd__TauEmbdVal
