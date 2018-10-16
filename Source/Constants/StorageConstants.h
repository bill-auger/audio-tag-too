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


#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"


/*\ NOTES:
|*|  the application data model is implemented in the AudioTagTooStore class
|*|      as JUCE ValueTrees with a JUCE binary file-out for persistence (STORAGE_FILENAME)
\*/

/*\ SCHEMA:
|*|
|*| // AudioTagTooStore->root
|*| STORAGE_ID:
|*| {
|*|   // config root
|*|   CONFIG_VERSION_KEY : an_int                                       ,
|*|   CLIPS_ID           : [ a-clip-id:        a_clip_node        , ... ] // clip-id nodes as below
|*|   COMPILATIONS_ID    : [ a-compilation-id: a_compilation_node , ... ] // compilation-id nodes as below
|*| }
|*|
|*| // AudioTagTooStore->clips items
|*| clip-id:
|*| {
|*|   FILENAME_KEY   : a_string , // master audio file from which this clip was derived
|*|   BEGIN_TIME_KEY : a_double , // beginning time offset relative to the master audio file
|*|   END_TIME_KEY   : a_double   // ending time offset relative to the master audio file
|*| }
|*|
|*| // AudioTagTooStore->compilations items
|*| compilation-id:
|*| {
|*|   // TODO: (ordered list of clip-id nodes)
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
  static const Identifier CLIPS_ID ;
  static const Identifier COMPILATIONS_ID ;

  // root IDs
  static const Identifier CONFIG_VERSION_KEY ;

  // clips/compilations IDs
  static const Identifier FILENAME_KEY ;
  static const Identifier BEGIN_TIME_KEY ;
  static const Identifier END_TIME_KEY ;
  static const Identifier ITEM_ID_KEY ;

  // root defaults
  static const String STORAGE_DIRNAME ;
  static const String STORAGE_FILENAME ;
  static const String DEVICE_FILENAME ;
  static const int    CONFIG_VERSION ;
} ;
