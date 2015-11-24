#include "TauEmbdVal/BTagPlots.h"

using CLHEP::GeV;

namespace TauEmbd{

  BTagPlots::BTagPlots(PlotBase* pParent, std::string sDir, std::string sParticleType):PlotBase(pParent, sDir),
m_sParticleType(sParticleType)
{}	
  
void BTagPlots::initializePlots(){
  n  = Book1D("n", "Number of b jets from "+ m_sParticleType +"; n ;Events", 10, 0., 10);
}

  void BTagPlots::fill(const xAOD::BTagging* /*btag*/){
}

void BTagPlots::fill(unsigned int nbtag){
  n->Fill(nbtag);
}
}
