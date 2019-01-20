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
#define XML_HEADER                     String("<?xml version=\"1.0\"?>")
#define ROOT_PERSISTENT_NODE_IDS_ATTRS " " + STRING(STORAGE_ID     )    + "=\"\" " + \
                                       " " + STRING(CLIPS_ID       )    + "=\"\" " + \
                                       " " + STRING(COMPILATIONS_ID)    + "=\"\" "
#define ROOT_TRANSIENT_NODE_IDS_ATTRS  ""
#define ROOT_PERSISTENT_KEYS_ATTRS     " " + STRING(CONFIG_VERSION_KEY) + "=\"\" " + \
                                       " " + STRING(WINDOW_STATE_KEY  ) + "=\"\" "
#define ROOT_TRANSIENT_KEYS_ATTRS      ""
#define MASTER_KEYS_ATTRS              " " + STRING(FILENAME_KEY  )     + "=\"\" " + \
                                       " " + STRING(LABEL_TEXT_KEY)     + "=\"\" " + \
                                       " " + STRING(ITEM_ID_KEY     )   + "=\"\" "
#define CLIP_IMMUTABLE_KEYS_ATTRS      " " + STRING(FILENAME_KEY    )   + "=\"\" " + \
                                       " " + STRING(BEGIN_TIME_KEY  )   + "=\"\" " + \
                                       " " + STRING(END_TIME_KEY    )   + "=\"\" " + \
                                       " " + STRING(DURATION_KEY    )   + "=\"\" " + \
                                       " " + STRING(ITEM_ID_KEY     )   + "=\"\" "
#define CLIP_PERSISTENT_KEYS_ATTRS     " " + STRING(LABEL_TEXT_KEY  )   + "=\"\" "
#define CLIP_TRANSIENT_KEYS_ATTRS      " " + STRING(NEW_METADATA_KEY)   + "=\"\" "
// ASSERT: each N_* below tracks the number of XML attributes
//         in corresponding *_ATTRS defines above
#define N_ROOT_PERSISTENT_NODES 3
#define N_ROOT_TRANSIENT_NODES  0
#define N_ROOT_PERSISTENT_KEYS  2
#define N_ROOT_TRANSIENT_KEYS   0
#define N_MASTER_KEYS           3
#define N_CLIP_IMMUTABLE_KEYS   5
#define N_CLIP_MUTABLE_KEYS     1
#define N_CLIP_TRANSIENT_KEYS   1
// ASSERT: each N_* below is the sum of the counts above
//         for which the corresponding attribute sets constitute each merged set below
#define N_ROOT_NODES           (N_ROOT_PERSISTENT_NODES + N_ROOT_TRANSIENT_NODES)
#define N_ROOT_KEYS            (N_ROOT_PERSISTENT_KEYS  + N_ROOT_TRANSIENT_KEYS )
#define N_CLIP_PERSISTENT_KEYS (N_CLIP_IMMUTABLE_KEYS   + N_CLIP_MUTABLE_KEYS   )
#define ROOT_PERSISTENT_NODE_IDS_XML XML_HEADER + "<root-persistent-nodes-xml " + \
                                       String(ROOT_PERSISTENT_NODE_IDS_ATTRS)   + \
                                     "/></xml>"
#define ROOT_NODE_IDS_XML            XML_HEADER + "<root-nodes-xml "            + \
                                       String(ROOT_PERSISTENT_NODE_IDS_ATTRS)   + \
                                       String(ROOT_TRANSIENT_NODE_IDS_ATTRS)    + \
                                     "/></xml>"
#define ROOT_PERSISTENT_KEYS_XML     XML_HEADER + "<root-persistent-keys-xml "  + \
                                       String(ROOT_PERSISTENT_KEYS_ATTRS)       + \
                                     "/></xml>"
#define ROOT_KEYS_XML                XML_HEADER + "<root-keys-xml "             + \
                                       String(ROOT_PERSISTENT_KEYS_ATTRS)       + \
                                       String(ROOT_TRANSIENT_KEYS_ATTRS )       + \
                                     "/></xml>"
#define MASTER_KEYS_XML              XML_HEADER + "<master-keys-xml "           + \
                                       String(MASTER_KEYS_ATTRS)                + \
                                     "/></xml>"
#define CLIP_IMMUTABLE_KEYS_XML      XML_HEADER + "<clip-immutable-keys-xml "   + \
                                       String(CLIP_IMMUTABLE_KEYS_ATTRS)        + \
                                     "/></xml>"
#define CLIP_PERSISTENT_KEYS_XML     XML_HEADER + "<clip-persistent-keys-xml "  + \
                                       String(CLIP_IMMUTABLE_KEYS_ATTRS )       + \
                                       String(CLIP_PERSISTENT_KEYS_ATTRS)       + \
                                     "/></xml>"
#define CLIP_TRANSIENT_KEYS_XML      XML_HEADER + "<clip-transient-keys-xml "   + \
                                       String(CLIP_TRANSIENT_KEYS_ATTRS)        + \
                                     "/></xml>"
const bool STORE::Initialize()
{
  // load key sets
  RootPersistentNodeIds = NewNodeKeysDict(STORAGE_ID , String(ROOT_PERSISTENT_NODE_IDS_XML) ,
                                                       String(ROOT_PERSISTENT_KEYS_XML    ) ) ;
  RootNodeIds           = NewNodeKeysDict(STORAGE_ID , String(ROOT_NODE_IDS_XML           ) ,
                                                       String(ROOT_KEYS_XML               ) ) ;
  RootPersistentKeys    = NewNodeIdsSet  (RootPersistentNodeIds[STORAGE_ID].getArray()) ;
  RootKeys              = NewNodeIdsSet  (RootNodeIds          [STORAGE_ID].getArray()) ;
  MasterKeys            = NewKeysSet     (String(MASTER_KEYS_XML         )) ;
  ClipImmutableKeys     = NewKeysSet     (String(CLIP_IMMUTABLE_KEYS_XML )) ;
  ClipPersistentKeys    = NewKeysSet     (String(CLIP_PERSISTENT_KEYS_XML)) ;
  ClipTransientKeys     = NewKeysSet     (String(CLIP_TRANSIENT_KEYS_XML )) ;

  // validations
  bool is_valid = RootPersistentNodeIds.size() == N_ROOT_PERSISTENT_NODES &&
                  RootNodeIds          .size() == N_ROOT_NODES            &&
                  RootPersistentKeys   .size() == N_ROOT_PERSISTENT_KEYS  &&
                  RootKeys             .size() == N_ROOT_KEYS             &&
                  MasterKeys           .size() == N_MASTER_KEYS           &&
                  ClipImmutableKeys    .size() == N_CLIP_IMMUTABLE_KEYS   &&
                  ClipPersistentKeys   .size() == N_CLIP_PERSISTENT_KEYS  &&
                  ClipTransientKeys    .size() == N_CLIP_TRANSIENT_KEYS    ;

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

const NamedValueSet STORE::NewKeysSet(String metadata_ids_xml_str)
{
  XmlElement*   metedata_keys_xml = XmlDocument::parse(metadata_ids_xml_str) ;
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
const Identifier STORE::FILENAME_KEY     = "master-filename" ;
const Identifier STORE::BEGIN_TIME_KEY   = "begin-time" ;
const Identifier STORE::END_TIME_KEY     = "end-time" ;
const Identifier STORE::DURATION_KEY     = "duration" ;
const Identifier STORE::ITEM_ID_KEY      = "item-id" ;
const Identifier STORE::LABEL_TEXT_KEY   = "label-text" ;
const Identifier STORE::NEW_METADATA_KEY = "new-key" ;

// key sets/dicts
NamedValueSet STORE::RootPersistentNodeIds ; // Initialize()
NamedValueSet STORE::RootNodeIds ;           // Initialize()
NamedValueSet STORE::RootPersistentKeys ;    // Initialize()
NamedValueSet STORE::RootKeys ;              // Initialize()
NamedValueSet STORE::MasterKeys ;            // Initialize()
NamedValueSet STORE::ClipImmutableKeys ;     // Initialize()
NamedValueSet STORE::ClipPersistentKeys ;    // Initialize()
NamedValueSet STORE::ClipTransientKeys ;     // Initialize()

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
