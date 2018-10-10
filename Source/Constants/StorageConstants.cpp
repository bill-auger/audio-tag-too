
#include "StorageConstants.h"


// sort and filter keys
template<> const int STORE::IdComparator<ValueTree&>::compareElements(const ValueTree& tree_a , const ValueTree& tree_b)
{
  return tree_a.getType() < tree_b.getType().toString() ;
}
const Identifier STORE::FilterId(String a_string , String retain_chars)
{
  return a_string.retainCharacters(retain_chars)
                 .toLowerCase()
                 .replaceCharacters(APP::FILTER_CHARS , APP::REPLACE_CHARS) ;
}
#define ROOT_PERSISTENT_NODE_IDS String::empty
// #define ROOT_TRANSIENT_NODE_IDS  String::empty
#define ROOT_PERSISTENT_IDS      STRING(CONFIG_VERSION_KEY) + newLine + \
                                 String::empty
#define ROOT_TRANSIENT_IDS       String::empty
const StringArray STORE::RootPersistentNodes() { return StringArray::fromLines(ROOT_PERSISTENT_NODE_IDS           ) ; }
// const StringArray STORE::RootNodes()           { return StringArray::fromLines(ROOT_PERSISTENT_NODE_IDS + newLine +
//                                                                                ROOT_TRANSIENT_NODE_IDS            ) ; }
const StringArray STORE::RootPersistentKeys()  { return StringArray::fromLines(ROOT_PERSISTENT_IDS                ) ; }
const StringArray STORE::RootKeys()            { return StringArray::fromLines(ROOT_PERSISTENT_IDS      + newLine +
                                                                               ROOT_TRANSIENT_IDS                 ) ; }

// storage nodes
const Identifier STORE::STORAGE_ID    = "juce-boilerplate-config" ;
const Identifier STORE::DEVICE_XML_ID = "juce-boilerplate-device-config" ;

// root IDs
const Identifier STORE::CONFIG_VERSION_KEY = "config-version" ;

// root defaults
const int STORE::CONFIG_VERSION = 1 ;

// persistence
#if JUCE_WINDOWS
  #define STORAGE_FILENAME_PREFIX APP::APP_NAME
const String STORE::STORAGE_DIRNAME  = APP::APP_NAME + "\\" ;
#else // JUCE_WINDOWS
  #define STORAGE_FILENAME_PREFIX APP::APP_CMD
const String STORE::STORAGE_DIRNAME  = APP::APP_CMD + "/" ;
#endif // JUCE_WINDOWS
#ifdef STORAGE_IS_BINARY
const String STORE::STORAGE_FILENAME = STORAGE_FILENAME_PREFIX + ".bin" ;
#else // STORAGE_IS_BINARY
const String STORE::STORAGE_FILENAME = STORAGE_FILENAME_PREFIX + ".xml" ;
#endif // STORAGE_IS_BINARY
const String STORE::DEVICE_FILENAME  = STORAGE_FILENAME_PREFIX + "-device.xml" ;
const String STORE::PEAKS_FILENAME   = STORAGE_FILENAME_PREFIX + "-peaks.bin" ;
