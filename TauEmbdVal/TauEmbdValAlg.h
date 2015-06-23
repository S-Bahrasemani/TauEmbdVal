#ifndef TAUEMBDVAL_TAUEMBDVALALG_H
#define TAUEMBDVAL_TAUEMBDVALALG_H 1


#include "AthenaBaseComps/AthHistogramAlgorithm.h"
#include "GaudiKernel/ToolHandle.h" //included under assumption you'll want to use some tools! Remove if you don't!



class TauEmbdValAlg: public ::AthHistogramAlgorithm { 
 public: 
  TauEmbdValAlg( const std::string& name, ISvcLocator* pSvcLocator );
  virtual ~TauEmbdValAlg(); 

  virtual StatusCode  initialize();
  virtual StatusCode  execute();
  virtual StatusCode  finalize();
    
 private: 

}; 

#endif //> !TAUEMBDVAL_TAUEMBDVALALG_H
