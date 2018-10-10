
#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"


/*\ NOTES:
|*|  the application data model is implemented in the JuceBoilerplateStore class
|*|      as JUCE ValueTrees with a JUCE binary file-out for persistence (STORAGE_FILENAME)
\*/

/*\ SCHEMA:
|*|
|*| // JuceBoilerplateStore->root
|*| STORAGE_ID:
|*| {
|*|   // config root
|*|   CONFIG_VERSION_ID: an_int
|*| }
\*/


#include "AppConstants.h"


/** the STORE class defines keys/value pairs and default value constants
        pertaining to the configuration/persistence model                */
class STORE
{
public:

  // sort and filter keys
  template<class ElementType>class IdComparator
  {
    public: static const int compareElements(const ValueTree& tree_a , const ValueTree& tree_b) ;
  } ;
  static const Identifier  FilterId           (String a_string , String retain_chars = APP::VALID_ID_CHARS) ;
  static const StringArray RootPersistentNodes() ;
//   static const StringArray RootNodes          () ;
  static const StringArray RootPersistentKeys () ;
  static const StringArray RootKeys           () ;

  // storage nodes
  static const Identifier STORAGE_ID ;
  static const Identifier DEVICE_XML_ID ;

  // root IDs
  static const Identifier CONFIG_VERSION_KEY ;

  // root defaults
  static const String STORAGE_DIRNAME ;
  static const String STORAGE_FILENAME ;
  static const String DEVICE_FILENAME ;
  static const int    CONFIG_VERSION ;
} ;
