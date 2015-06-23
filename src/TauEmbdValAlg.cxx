
// TauEmbdVal includes
#include "TauEmbdVal/TauEmbdValAlg.h"
#include "xAODJet/JetContainer.h"
#include "xAODTau/TauJetContainer.h"


TauEmbdValAlg::TauEmbdValAlg( const std::string& name, ISvcLocator* pSvcLocator ) : AthHistogramAlgorithm( name, pSvcLocator ){
  //declareProperty( "Property", m_nProperty ); //example property declaration

}

TauEmbdValAlg::~TauEmbdValAlg() {}


StatusCode TauEmbdValAlg::initialize() {
  //// Book TAUS histograms
  CHECK( book(TH1F("hist_tauPt", "Tau Pt (GeV)", 30, 0.0, 300.0)));
  CHECK (book(TH1F("hist_tauEta", "Tau Eta", 20, -10.0, 10.0)));
  CHECK (book(TH1F("hist_tauPhi", "Tau Phi", 200, -3.75, 3.75)));
  CHECK (book(TH1F("hist_tauM", "Tau M ", 30, 0.0, 200.0)));

    //// Book JETS histograms
  CHECK( book( TH1F("hist_nJets", "Number of jets", 10, 0.0, 10.0) ) );
  CHECK( book( TH1F("hist_nCombinedJets", "Number of jets with the type Combined", 10, 0.0, 10.0) ) );
  CHECK( book( TH1F("hist_jetPt", "Jet Pt (GeV)", 30, 0.0, 300.0) ) );

  ATH_MSG_INFO ("Booking HISTOGRAMS:: " << name() << "...");

  return StatusCode::SUCCESS;
}

StatusCode TauEmbdValAlg::execute() {

  // Retrieve the taus:
  const xAOD::TauJetContainer* taus = 0;
  CHECK( evtStore()->retrieve( taus, "TauJets" ) );
  //// for muon "Muons"

  // Loop over them:
  for( const auto* tau : *taus ) {
     hist("hist_tauPt")->Fill( (tau->pt())/1000);
     hist("hist_tauEta")->Fill( tau->eta());
     hist("hist_tauPhi")->Fill( tau->phi());
     hist("hist_tauM")->Fill( (tau->m())/1000);		   
 }

  //// retrive the jets
  const xAOD::JetContainer* jets = 0;
  CHECK (evtStore()->retrieve(jets,"AntiKt4LCTopoJets" ));
  int eventWeight = 1;

  ////Loop over them:
  for ( const auto*  jet : *jets ) {

    ATH_MSG_INFO( "  Selected jet: eta = " << jet->eta() );
    hist("hist_jetPt")->Fill( (jet->pt())/1000 , eventWeight );

  }
  hist("hist_nJets")->Fill( jets->size() , eventWeight );

  ATH_MSG_INFO ("Filling HISTOGRAMS'S DONE:: " << name() << "...");
  return StatusCode::SUCCESS;
}

StatusCode TauEmbdValAlg::finalize() {  
  ATH_MSG_DEBUG ("Executing " << name() << "...");

  return StatusCode::SUCCESS;
}


