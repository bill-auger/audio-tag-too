
#include "Seeds.h"
#include "../Constants/StorageConstants.h"


/* Seeds public class methods */

ValueTree Seeds::DefaultStore()
{
  ValueTree default_store = ValueTree(STORE::STORAGE_ID) ;

  default_store.setProperty(STORE::CONFIG_VERSION_KEY , STORE::CONFIG_VERSION , nullptr) ;

  return default_store ;
}
