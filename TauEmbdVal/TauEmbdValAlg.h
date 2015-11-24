#ifndef PHYSVALMONITORING_TAUEMBDVALALG_H
#define PHYSVALMONITORING_TAUEMBDVALALG_H 1

// STL includes
#include <string>
#include <vector>

// FrameWork includes
#include "AthenaBaseComps/AthCheckMacros.h"
#include "GaudiKernel/ServiceHandle.h"
#include "GaudiKernel/IToolSvc.h"
#include "xAODJet/JetContainer.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODEgamma/PhotonContainer.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODTau/TauJetContainer.h"
#include "xAODMissingET/MissingET.h"
#include "xAODMissingET/MissingETContainer.h"
#include "xAODTracking/TrackParticle.h"
#include "xAODTracking/Vertex.h"
#include "xAODEventInfo/EventInfo.h"
#include "xAODBTagging/BTagging.h"
#include "RecEvent/RecoTimingObj.h"
 
// Local includes
#include "AthenaMonitoring/ManagedMonitorToolBase.h"
#include "KinematicsPlots.h"
#include "TrkAndVtxPlots.h"
#include "METPlots.h"
#include "BTagPlots.h"

// Root includes
#include "TH1.h"

// Forward declaration
namespace TauEmbd {
  class TauEmbdVal
    : public ManagedMonitorToolBase
  { 
    /////////////////////////////////////////////////////////////////// 
    // Public methods: 
    /////////////////////////////////////////////////////////////////// 
  public: 
    
    // Copy constructor: 
    
    /// Constructor with parameters: 
    TauEmbdVal( const std::string& type,
		  const std::string& name, 
		  const IInterface* parent );

    /// Destructor: 
    virtual ~TauEmbdVal(); 
    
    // Athena algtool's Hooks
    virtual StatusCode initialize();
    virtual StatusCode bookHistograms();
    virtual StatusCode fillHistograms();
    virtual StatusCode procHistograms();
    
  private: 
    
    /// Default constructor: 
    TauEmbdVal();
    
    // Containers
    std::string m_jetName;
    std::string m_elecName; 
    std::string m_photonName; 
    std::string m_muonName; 
    std::string m_tauName; 
    std::string m_metName; 
    std::string m_trackName; 
    std::string m_vertexName; 

    std::vector<std::string> m_timingNames = {"EVNTtoHITS", "HITStoRDO", "RAWtoESD", "ESDtoAOD"};

  // Hists
    TauEmbd::KinematicsPlots m_jetPlots;
    TauEmbd::KinematicsPlots m_elecPlots;
    TauEmbd::KinematicsPlots m_photonPlots;
    TauEmbd::KinematicsPlots m_muonPlots;
    TauEmbd::KinematicsPlots m_tauPlots;
    TauEmbd::TrkAndVtxPlots m_trkvtxPlots;
    TauEmbd::METPlots m_metPlots;
    TauEmbd::BTagPlots m_btagPlots;

    std::vector<TH1*> m_timingPlots;

    StatusCode book(PlotBase& plots);
    StatusCode getTiming(std::string name, float& recoTime);
    
  }; 

// I/O operators
//////////////////////
  
/////////////////////////////////////////////////////////////////// 
// Inline methods: 
/////////////////////////////////////////////////////////////////// 
}

#endif //> !PHYSVALMONITORING_TAUEMBDVALALG_H
