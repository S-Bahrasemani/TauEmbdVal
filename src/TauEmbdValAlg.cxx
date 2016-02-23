
// TauEmbdVal includes
#include "TauEmbdVal/TauEmbdValAlg.h"

namespace TauEmbd{

// Constructor
////////////////
  TauEmbdVal::TauEmbdVal( const std::string& type, 
				  const std::string& name, 
				  const IInterface* parent ) : 
    ManagedMonitorToolBase( type, name, parent ),
    m_jetPlots(0, "Jet/", "Jet"),
    m_elecPlots(0, "Electron/", "Electron"),
    m_photonPlots(0, "Photon/", "Photon"),
    m_muonPlots(0, "Muon/", "Muon"),
    m_tauPlots(0, "Tau/", "Tau"),
    m_trkvtxPlots(0, "TrackAndVertex/"),
    m_metPlots(0, "MET/", "RefFinal"),
    m_btagPlots(0, "BTag/", "IP3D")
  {
    
    declareProperty( "JetContainerName", m_jetName = "AntiKt4EMTopoJets" );
    declareProperty( "ElectronContainerName", m_elecName = "ElectronCollection" ); 
    declareProperty( "PhotonContainerName", m_photonName = "PhotonCollection" ); 
    declareProperty( "MuonContainerName", m_muonName = "Muons" ); 
    declareProperty( "TauContainerName", m_tauName = "TauJets" );
    declareProperty( "TrackContainerName", m_trackName = "InDetTrackParticles" );  
    declareProperty( "VertexContainerName", m_vertexName = "PrimaryVertices" );  
    declareProperty( "METContainerName", m_metName = "MET_RefFinal" ); 
  }
  
  // Destructor
  ///////////////
  TauEmbdVal::~TauEmbdVal()
  {}
  
  // Athena algtool's Hooks
  ////////////////////////////
  StatusCode TauEmbdVal::initialize()
  {
    ATH_MSG_INFO ("Initializing " << name() << "...");    
    ATH_CHECK(ManagedMonitorToolBase::initialize());
    return StatusCode::SUCCESS;
  }
  
  StatusCode TauEmbdVal::book(PlotBase& plots)
  {
    plots.initialize();
    std::vector<HistData> hists = plots.retrieveBookedHistograms();
    
    for (auto& hist : hists){
      ATH_MSG_INFO ("Initializing " << hist.first << " " << hist.first->GetName() << " " << hist.second << "...");
      ATH_CHECK(regHist(hist.first,hist.second,all));
    }
    return StatusCode::SUCCESS;      
  }

  StatusCode TauEmbdVal::bookHistograms()
  {
      ATH_MSG_INFO ("Booking hists " << name() << "...");      

      ATH_CHECK(book(m_jetPlots));
      ATH_CHECK(book(m_btagPlots));
      ATH_CHECK(book(m_elecPlots));
      ATH_CHECK(book(m_photonPlots));
      ATH_CHECK(book(m_muonPlots));
      ATH_CHECK(book(m_tauPlots));
      ATH_CHECK(book(m_trkvtxPlots));
      ATH_CHECK(book(m_metPlots));
      
      return StatusCode::SUCCESS;      
 }
 
  StatusCode TauEmbdVal::fillHistograms()
  {
    ATH_MSG_INFO ("Filling hists " << name() << "...");
    
    // Jets
    int nbtag(0);
    m_jetPlots.initializeEvent();
    const xAOD::JetContainer* jets(0);
    ATH_CHECK(evtStore()->retrieve(jets, m_jetName));
    for (auto jet : *jets) 
      {
	if (!jet) 
	  {
	    ATH_MSG_ERROR ("Couldn't retrieve Jet");
	    return StatusCode::SUCCESS;
	  }
	m_jetPlots.fill(jet);
	const xAOD::BTagging* btag = jet->btagging();
	if (btag && btag->IP3D_loglikelihoodratio() > 1.2) ++nbtag;
      }
    m_jetPlots.fill();
    m_btagPlots.fill(nbtag);

    // Electrons
    m_elecPlots.initializeEvent();
    const xAOD::ElectronContainer* electrons(0);
    ATH_CHECK(evtStore()->retrieve(electrons, m_elecName));
    for (auto elec : *electrons) 
      {
	if (!elec) 
	  {
	    ATH_MSG_ERROR ("Couldn't retrieve Electron");
	    return StatusCode::SUCCESS;
	  }
	m_elecPlots.fill(elec);
      }
    
    m_elecPlots.fill();

    // Photons
    m_photonPlots.initializeEvent();
    const xAOD::PhotonContainer* photons(0);
    ATH_CHECK(evtStore()->retrieve(photons, m_photonName));
    for (auto photon : *photons)
      {
	if (!photon) 
	  {
	    ATH_MSG_ERROR ("Couldn't retrieve photon");
	    return StatusCode::SUCCESS;
	  }
	m_photonPlots.fill(photon);
      }
    m_photonPlots.fill();

    // Muons
    m_muonPlots.initializeEvent();
    const xAOD::MuonContainer* muons(0);
    ATH_CHECK(evtStore()->retrieve(muons, m_muonName));
    for (auto muon : *muons)
      {
	if (!muon) 
	  {
	    ATH_MSG_ERROR ("Couldn't retrieve Muon");
	    return StatusCode::SUCCESS;
	  }
	m_muonPlots.fill(muon);
      }
    m_muonPlots.fill();

    // Taus
    m_tauPlots.initializeEvent();
    const xAOD::TauJetContainer* taus(0);
    ATH_CHECK(evtStore()->retrieve(taus, m_tauName));
    for (auto tau : *taus) 
      {
	if (!tau) 
	  {
	    ATH_MSG_ERROR ("Couldn't retrieve tau");
	    return StatusCode::SUCCESS;
	  }
	m_tauPlots.fill(tau);
	
      }
    m_tauPlots.fill();

    // Tracks/Vertices
    const xAOD::TrackParticleContainer* trks(0);
    ATH_CHECK(evtStore()->retrieve(trks, m_trackName));

    const xAOD::VertexContainer* vtxs(0);
    ATH_CHECK(evtStore()->retrieve(vtxs, m_vertexName));
    for (auto vtx : *vtxs) m_trkvtxPlots.fill(vtx);

    const xAOD::EventInfo* event(0);
    ATH_CHECK(evtStore()->retrieve(event, "EventInfo"));

    m_trkvtxPlots.fill(trks->size(), vtxs->size(), event->averageInteractionsPerCrossing());

    const xAOD::MissingETContainer* mets (0);
    ATH_CHECK(evtStore()->retrieve(mets, m_metName));
    for (auto met : *mets) 

    // const xAOD::MissingET* met = (*met_container)["FinalClus"];
    if (!met) {
      ATH_MSG_ERROR ("Couldn't retrieve MET Final");
      return StatusCode::SUCCESS;
      m_metPlots.fill(met);
    }
    
    return StatusCode::SUCCESS;
  }
  
  StatusCode TauEmbdVal::procHistograms()
  {
    ATH_MSG_INFO ("Finalising hists " << name() << "...");
    return StatusCode::SUCCESS;
  }
  
  

}

// //  LocalWords:  str 
