#include "TauEmbdVal/KinematicsPlots.h"

using CLHEP::GeV;

namespace TauEmbd{
  KinematicsPlots::KinematicsPlots(PlotBase* pParent, std::string sDir, std::string sParticleType):PlotBase(pParent, sDir), 
										  m_sParticleType(sParticleType)
{}	
  
void KinematicsPlots::initializePlots(){
  lead = nullptr;
  npart = 0;
  
  n  = Book1D("n", "Number of "+ m_sParticleType +"; n ;Events", 30, 0., 30);
    
  et  = Book1D("et", "E_{T} of "+ m_sParticleType +"; E_{T} (GeV) ;Events", 30, 0., 300);
  eta = Book1D("eta", "#eta of " + m_sParticleType +";#eta; Events ",  20,-10.,10.);
  phi = Book1D("phi", "#varphi of " + m_sParticleType +";#varphi;Events ",10 ,-4,4);
    
  lead_et  = Book1D("lead_et", "E_{T} of lead "+ m_sParticleType +"; E_{T} (GeV) ;Events", 30, 0., 300);
  lead_eta = Book1D("lead_eta", "#eta of lead " + m_sParticleType +";#eta; Events ", 20,-10.,10.);
  lead_phi = Book1D("lead_phi", "#varphi of lead " + m_sParticleType +";#varphi;Events ",10 ,-4,4);
    }
  
  void KinematicsPlots::fill(const xAOD::IParticle* part){

  et->Fill(part->pt()/GeV);
  eta->Fill(part->eta());
  phi->Fill(part->phi());

  if (lead == nullptr) lead = part;

  if (part->pt() > lead->pt()) {
     lead = part;
   }

  ++npart;  
}

void KinematicsPlots::fill(){
  n->Fill(npart);

  if (lead != nullptr) {
    lead_et->Fill(lead->pt()/GeV);
    lead_eta->Fill(lead->eta());
    lead_phi->Fill(lead->phi());
  }

  lead = nullptr;

}

void KinematicsPlots::initializeEvent() {
  lead = nullptr;
  npart = 0;

}

}

