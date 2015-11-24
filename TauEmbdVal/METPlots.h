#ifndef PHYSVALMONITORING_METPLOTS_H
#define PHYSVALMONITORING_METPLOTS_H

#include "TrkValHistUtils/PlotBase.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "xAODMissingET/MissingET.h"

namespace TauEmbd{
  class METPlots:public PlotBase {
  public:
    METPlots(PlotBase* pParent, std::string sDir, std::string sParticleType = "RefFinal");
    void fill(const xAOD::MissingET* met);
    
    // Reco only information
    std::string m_sParticleType;
    TH1* met_ex;
    TH1* met_ey;
    TH1* met_et;
    TH1* met_sumet;
    
  private:
    virtual void initializePlots();      
  };
  
}

#endif
