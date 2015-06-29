
// TauEmbdVal includes
#include "TauEmbdVal/TauEmbdValAlg.h"
#include "xAODJet/JetContainer.h"
#include "xAODTau/TauJetContainer.h"
#include "xAODMuon/MuonContainer.h"

//#include "xAODMissingET/MissingETContainer"

TauEmbdValAlg::TauEmbdValAlg( const std::string& name, ISvcLocator* pSvcLocator ) : AthHistogramAlgorithm( name, pSvcLocator ){
  //declareProperty( "Property", m_nProperty ); //example property declaration

  // add 

}



TauEmbdValAlg::~TauEmbdValAlg() {}
StatusCode TauEmbdValAlg::initialize() {
  //// Book TAUS histograms
  CHECK( book(TH1F("hist_tauPt", "Tau Pt (GeV)", 30, 0.0, 300.0)));
  CHECK (book(TH1F("hist_tauEta", "Tau Eta", 20, -10.0, 10.0)));
  CHECK (book(TH1F("hist_tauPhi", "Tau Phi", 200, -3.75, 3.75)));
  CHECK (book(TH1F("hist_tauM", "Tau M ", 30, 0.0, 200.0)));
  CHECK( book( TH1F("hist_nTaus", "Number of taus", 10, 0.0, 10.0) ) );
 
  //// book MUON histograms

  CHECK( book(TH1F("hist_muonPt", "Muon Pt (GeV)", 30, 0.0, 300.0)));
  CHECK (book(TH1F("hist_muonEta", "Muon Eta", 20, -10.0, 10.0)));
  CHECK (book(TH1F("hist_muonPhi", "Muon Phi", 200, -3.75, 3.75)));
  CHECK (book(TH1F("hist_muonM", "Muon M ", 30, 0.0, 200.0)));
  CHECK( book( TH1F("hist_nMuons", "Number of muons", 10, 0.0, 10.0) ) );
 

  //// Book JETS histograms
  CHECK( book(TH1F("hist_jetPt", "Jet Pt (GeV)", 30, 0.0, 300.0)));
  CHECK (book(TH1F("hist_jetEta", "Jet Eta", 20, -10.0, 10.0)));
  CHECK (book(TH1F("hist_jetPhi", "Jet Phi", 200, -3.75, 3.75)));
  CHECK (book(TH1F("hist_jetM", "Jet M ", 30, 0.0, 200.0)));
  CHECK( book( TH1F("hist_nJets", "Number of jets", 10, 0.0, 10.0) ) );

  ATH_MSG_INFO ("Booking HISTOGRAMS:: " << name() << "...");

  return StatusCode::SUCCESS;
}

StatusCode TauEmbdValAlg::execute() {
  // Retrieve the taus:
  const xAOD::TauJetContainer* taus = 0;
  CHECK( evtStore()->retrieve( taus, "TauJets" ) );

  // Loop over them:
  for( const auto* tau : *taus ) {
     hist("hist_tauPt")->Fill( (tau->pt())/1000);
     hist("hist_tauEta")->Fill( tau->eta());
     hist("hist_tauPhi")->Fill( tau->phi());
     hist("hist_tauM")->Fill( (tau->m())/1000);		   
 }
  hist("hist_nTaus")->Fill( taus->size());


  // Retrieve the muons:
  const xAOD::MuonContainer* muons = 0;
  CHECK( evtStore()->retrieve( muons, "Muons" ) );
  //// for muon "Muons"

  // Loop over them:
  for( const auto* muon : *muons ) {
     hist("hist_muonPt")->Fill( (muon->pt())/1000);
     hist("hist_muonEta")->Fill( muon->eta());
     hist("hist_muonPhi")->Fill( muon->phi());
     hist("hist_muonM")->Fill( (muon->m())/1000);		   
 }
  hist("hist_nMuons")->Fill( muons->size());

  //// retrive the jets
  const xAOD::JetContainer* jets = 0;
  CHECK (evtStore()->retrieve(jets,"AntiKt4LCTopoJets" ));

  ////Loop over them:
  for ( const auto*  jet : *jets ) {

     hist("hist_jetPt")->Fill( (jet->pt())/1000);
     hist("hist_jetEta")->Fill( jet->eta());
     hist("hist_jetPhi")->Fill( jet->phi());
     hist("hist_jetM")->Fill( (jet->m())/1000);		   
  }
  hist("hist_nJets")->Fill( jets->size());

  ATH_MSG_INFO ("Filling HISTOGRAMS'S DONE:: " << name() << "...");
  return StatusCode::SUCCESS;
}

StatusCode TauEmbdValAlg::finalize() {  

  ATH_MSG_DEBUG ("Executing " << name() << "...");
  return StatusCode::SUCCESS;
}


