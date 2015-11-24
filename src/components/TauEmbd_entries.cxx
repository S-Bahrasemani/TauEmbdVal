
#include "GaudiKernel/DeclareFactoryEntries.h"

#include "../TauEmbdVal/TauEmbdValAlg.h"

//DECLARE_ALGORITHM_FACTORY( TauEmbdValAlg )
DECLARE_NAMESPACE_TOOL_FACTORY (TauEmbd, TauEmbdVal)


//DECLARE_FACTORY_ENTRIES( TauEmbdVal )
DECLARE_FACTORY_ENTRIES(PhysValMonitoring) 
{
  //  DECLARE_ALGORITHM( TauEmbdValAlg );

  DECLARE_NAMESPACE_TOOL (TauEmbd, TauEmbdVal);
}
