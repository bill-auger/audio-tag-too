/*\
|*|  AudioTagToo - Clip and stitch audio samples
|*|  Copyright 2018 bill-auger <https://github.com/bill-auger/audio-tag-too/issues>
|*|
|*|  This file is part of the AudioTagToo program.
|*|
|*|  AudioTagToo is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU General Public License as published by
|*|  the Free Software Foundation, either version 3 of the License, or
|*|  (at your option) any later version.
|*|
|*|  AudioTagToo is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU General Public License for more details.
|*|
|*|  You should have received a copy of the GNU General Public License
|*|  along with AudioTagToo.  If not, see <http://www.gnu.org/licenses/>.
\*/


#include "StorageConstants.h"
#include "../Trace/TraceConstants.h"


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
// #define ROOT_PERSISTENT_NODE_IDS STORE::CLIPS_ID            + newLine + \
//                                  STORE::COMPILATIONS_ID
// #define ROOT_TRANSIENT_NODE_IDS  String::empty
// #define ROOT_PERSISTENT_KEYS     STRING(CONFIG_VERSION_KEY) + newLine + \
//                                  STRING(WINDOW_STATE_KEY  )
// #define ROOT_TRANSIENT_KEYS      String::empty
#define XML_HEADER                     String("<?xml version=\"1.0\"?>")
#define ROOT_PERSISTENT_NODE_IDS_ATTRS " " + STRING(STORAGE_ID     )    + "=\"\" " + \
                                       " " + STRING(CLIPS_ID       )    + "=\"\" " + \
                                       " " + STRING(COMPILATIONS_ID)    + "=\"\" "
#define ROOT_TRANSIENT_NODE_IDS_ATTRS  ""
#define ROOT_PERSISTENT_KEYS_ATTRS     " " + STRING(CONFIG_VERSION_KEY) + "=\"\" " + \
                                       " " + STRING(WINDOW_STATE_KEY  ) + "=\"\" "
#define ROOT_TRANSIENT_KEYS_ATTRS      ""
#define METADATA_KEYS_ATTRS            " " + STRING(FILENAME_KEY  )     + "=\"\" " + \
                                       " " + STRING(BEGIN_TIME_KEY)     + "=\"\" " + \
                                       " " + STRING(END_TIME_KEY  )     + "=\"\" " + \
                                       " " + STRING(DURATION_KEY  )     + "=\"\" "
// (ASSERT: each N_* below matches N XML attributes in corresponding *_ATTRS defines above)
#define N_ROOT_PERSISTENT_NODES 3
#define N_ROOT_NODES            3
#define N_ROOT_PERSISTENT_KEYS  2
#define N_ROOT_KEYS             2
#define N_METADATA_KEYS         4
#define ROOT_PERSISTENT_NODE_IDS_XML   XML_HEADER + "<root-persistent-nodes-xml " + \
                                         String(ROOT_PERSISTENT_NODE_IDS_ATTRS)   + \
                                       "/></xml>"
#define ROOT_NODE_IDS_XML              XML_HEADER + "<root-nodes-xml "            + \
                                         String(ROOT_PERSISTENT_NODE_IDS_ATTRS)   + \
                                         String(ROOT_TRANSIENT_NODE_IDS_ATTRS)    + \
                                       "/></xml>"
#define ROOT_PERSISTENT_KEYS_XML       XML_HEADER + "<root-persistent-keys-xml "  + \
                                         String(ROOT_PERSISTENT_KEYS_ATTRS)       + \
                                       "/></xml>"
#define ROOT_KEYS_XML                  XML_HEADER + "<root-keys-xml "             + \
                                         String(ROOT_PERSISTENT_KEYS_ATTRS)       + \
                                         String(ROOT_TRANSIENT_KEYS_ATTRS )       + \
                                       "/></xml>"
#define METADATA_KEYS_XML              XML_HEADER + "<metadata-keys-xml "         + \
                                         String(METADATA_KEYS_ATTRS)              + \
                                       "/></xml>"
const bool STORE::Initialize()
{
  RootPersistentNodes = NewNodeKeysDict(STORAGE_ID , String(ROOT_PERSISTENT_NODE_IDS_XML) ,
                                                     String(ROOT_PERSISTENT_KEYS_XML    ) ) ;
  RootNodes           = NewNodeKeysDict(STORAGE_ID , String(ROOT_NODE_IDS_XML           ) ,
                                                     String(ROOT_KEYS_XML               ) ) ;
  RootPersistentKeys  = NewNodeIdsSet(RootPersistentNodes[STORAGE_ID].getArray()) ;
  RootKeys            = NewNodeIdsSet(RootNodes          [STORAGE_ID].getArray()) ;
  MetadataKeys        = NewMetadataKeysSet() ;

  // validations
  bool is_valid = RootPersistentNodes.size() == N_ROOT_PERSISTENT_NODES &&
                  RootNodes          .size() == N_ROOT_NODES            &&
                  RootPersistentKeys .size() == N_ROOT_PERSISTENT_KEYS  &&
                  RootKeys           .size() == N_ROOT_KEYS             &&
                  MetadataKeys       .size() == N_METADATA_KEYS          ;

DEBUG_TRACE_STORAGE_INIT

  return is_valid ;
}

const NamedValueSet STORE::NewNodeKeysDict(Identifier parent_node_id , String node_ids_xml_str ,
                                                                       String keys_xml_str     )
{
  XmlElement*   nodes_xml  = XmlDocument::parse(node_ids_xml_str) ;
  XmlElement*   keys_xml   = XmlDocument::parse(keys_xml_str    ) ;
  NamedValueSet nodes_dict = NamedValueSet() ;
  NamedValueSet keys_set  = NamedValueSet() ;
  Array<var> keys_array ;

  nodes_dict.setFromXmlAttributes(*nodes_xml) ; delete nodes_xml ;
  keys_set  .setFromXmlAttributes(*keys_xml ) ; delete keys_xml ;

  for (int key_n = 0 ; key_n < keys_set.size() ; ++key_n)
    keys_array.add(var(STRING(keys_set.getName(key_n)))) ;
  nodes_dict.set(parent_node_id , var(keys_array)) ;

  return nodes_dict ;
}

const NamedValueSet STORE::NewNodeIdsSet(Array<var>* keys)
{
  NamedValueSet keys_set ;

  for (int key_n = 0 ; key_n < keys->size() ; ++key_n)
    keys_set.set(Identifier(STRING(keys->getUnchecked(key_n))) , var::null) ;

  return keys_set ;
}

const NamedValueSet STORE::NewMetadataKeysSet()
{
  XmlElement*   metedata_keys_xml = XmlDocument::parse(String(METADATA_KEYS_XML)) ;
  NamedValueSet metedata_keys_set = NamedValueSet() ;

  metedata_keys_set.setFromXmlAttributes(*metedata_keys_xml) ;

  delete metedata_keys_xml ;

  return metedata_keys_set ;
}


// storage nodes
const Identifier STORE::STORAGE_ID      = "audio-tag-too-config" ;
const Identifier STORE::DEVICE_XML_ID   = "audio-tag-too-device-config" ;
const Identifier STORE::CLIPS_ID        = "clips" ;
const Identifier STORE::COMPILATIONS_ID = "compilations" ;

// root keys
const Identifier STORE::CONFIG_VERSION_KEY = "config-version" ;
const Identifier STORE::WINDOW_STATE_KEY   = "window-state" ;

// clips/compilations keys
const Identifier STORE::ITEM_ID_KEY    = "item-id" ;
const Identifier STORE::LABEL_TEXT_KEY = "label-text" ;
const Identifier STORE::FILENAME_KEY   = "master-filename" ;
const Identifier STORE::BEGIN_TIME_KEY = "begin-time" ;
const Identifier STORE::END_TIME_KEY   = "end-time" ;
const Identifier STORE::DURATION_KEY   = "duration" ;
const Identifier STORE::NEW_KEY_KEY    = "new-key" ;

// key sets/dicts
NamedValueSet STORE::RootPersistentNodes ; // Initialize()
NamedValueSet STORE::RootNodes ;           // Initialize()
NamedValueSet STORE::RootPersistentKeys ;  // Initialize()
NamedValueSet STORE::RootKeys ;            // Initialize()
NamedValueSet STORE::MetadataKeys ;        // Initialize()

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
