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
#define ROOT_TRANSIENT_NODE_IDS  String::empty
#define ROOT_PERSISTENT_IDS      STRING(CONFIG_VERSION_KEY) + newLine + \
                                 STRING(WINDOW_STATE_KEY  )
#define ROOT_TRANSIENT_IDS       String::empty
const StringArray STORE::RootPersistentNodes() { return StringArray::fromLines(ROOT_PERSISTENT_NODE_IDS           ) ; }
const StringArray STORE::RootNodes()           { return StringArray::fromLines(ROOT_PERSISTENT_NODE_IDS + newLine +
                                                                               ROOT_TRANSIENT_NODE_IDS            ) ; }
const StringArray STORE::RootPersistentKeys()  { return StringArray::fromLines(ROOT_PERSISTENT_IDS                ) ; }
const StringArray STORE::RootKeys()            { return StringArray::fromLines(ROOT_PERSISTENT_IDS      + newLine +
                                                                               ROOT_TRANSIENT_IDS                 ) ; }

// storage nodes
const Identifier STORE::STORAGE_ID    = "audio-tag-too-config" ;
const Identifier STORE::DEVICE_XML_ID = "audio-tag-too-device-config" ;

// root IDs
const Identifier STORE::CONFIG_VERSION_KEY = "config-version" ;
const Identifier STORE::WINDOW_STATE_KEY   = "window-state" ;

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
