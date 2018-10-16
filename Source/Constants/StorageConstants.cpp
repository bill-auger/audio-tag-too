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
const Identifier STORE::STORAGE_ID      = "audio-tag-too-config" ;
const Identifier STORE::DEVICE_XML_ID   = "audio-tag-too-device-config" ;
const Identifier STORE::CLIPS_ID        = "clips" ;
const Identifier STORE::COMPILATIONS_ID = "compilations" ;

// root IDs
const Identifier STORE::CONFIG_VERSION_KEY = "config-version" ;

// clips/compilations IDs
const Identifier STORE::FILENAME_KEY   = "master-filename";
const Identifier STORE::BEGIN_TIME_KEY = "begin-time" ;
const Identifier STORE::END_TIME_KEY   = "end-time" ;
const Identifier STORE::ITEM_ID_KEY    = "item_id" ;

// root defaults
const int STORE::CONFIG_VERSION = 1 ;

// meta
#if JUCE_LINUX
const String STORE::STORAGE_DIRNAME  = APP::APP_CMD + "/" ;
  #ifdef STORAGE_IS_BINARY
const String STORE::STORAGE_FILENAME = APP::APP_CMD + ".bin" ;
  #else // STORAGE_IS_BINARY
const String STORE::STORAGE_FILENAME = APP::APP_CMD + ".xml" ;
  #endif // STORAGE_IS_BINARY
const String STORE::DEVICE_FILENAME  = APP::APP_CMD + "-device.xml" ;
#endif // JUCE_LINUX
#if JUCE_WINDOWS
const String STORE::STORAGE_DIRNAME  = APP::APP_NAME + "\\" ;
  #ifdef STORAGE_IS_BINARY
const String STORE::STORAGE_FILENAME = APP::APP_NAME + ".bin" ;
  #else // STORAGE_IS_BINARY
const String STORE::STORAGE_FILENAME = APP::APP_NAME + ".xml" ;
  #endif // STORAGE_IS_BINARY
const String STORE::DEVICE_FILENAME  = APP::APP_NAME + "-device.xml" ;
#endif // JUCE_WINDOWS
