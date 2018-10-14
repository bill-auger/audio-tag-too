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


#pragma once


#include "../JuceLibraryCode/JuceHeader.h"


// enable debug/tracing features
#ifdef DEBUG
  #define DEBUG_TRACE 1
  #define DEBUG_TRACE_VB 0
#else // DEBUG
  #define DEBUG_TRACE 0
  #define DEBUG_TRACE_VB 0
#endif // DEBUG
#define DEBUG_TRACE_EVENTS   (DEBUG_TRACE    && 1)
#define DEBUG_TRACE_GUI      (DEBUG_TRACE    && 1)
#define DEBUG_TRACE_GUI_VB   (DEBUG_TRACE_VB && 0)
#define DEBUG_TRACE_MEDIA    (DEBUG_TRACE    && 1)
#define DEBUG_TRACE_MEDIA_VB (DEBUG_TRACE_VB && 0)
#define DEBUG_TRACE_STORE    (DEBUG_TRACE    && 1)
#define DEBUG_TRACE_STORE_VB (DEBUG_TRACE_VB && 1)
#define DEBUG_TRACE_STATE    (DEBUG_TRACE    && 1)
#define DEBUG_TRACE_WARNINGS (DEBUG_TRACE    && 0)
#define DEBUG_TRACE_ERRORS   (DEBUG_TRACE    && 1)
#define DEBUG_ANSI_COLORS    (DEBUG_TRACE    && 1)
#define DEBUG_PRIME_STORAGE  0
#define DEBUG_DUMP_VERBOSITY 0 /* 0 => none , 1 => nodes only , 2 => all properties */
#define DEBUG_WRITE_XML      0


#if DEBUG_ANSI_COLORS
  #define CGREEN  String("\033[1;32m")
  #define CYELLOW String("\033[1;33m")
  #define CRED    String("\033[0;31m")
  #define CBLUE   String("\033[1;34m")
  #define CEND    String("\033[0m"   )
#else // DEBUG_ANSI_COLORS
  #define CGREEN  String::empty
  #define CYELLOW String::empty
  #define CRED    String::empty
  #define CBLUE   String::empty
  #define CEND    String::empty
#endif // DEBUG_ANSI_COLORS

#define LOG(msg) Logger::outputDebugString(msg)

#ifdef DEBUG_TRACE

  #undef DBG
  #define DBG(msg) Trace::TraceDebug(msg)

  #define DEBUG_TRACE_DUMP_STORE(store , node_desc)                                                  \
  if (DEBUG_DUMP_VERBOSITY > 0) {                                                                    \
    Trace::TraceStore("dumping "       + String((DEBUG_DUMP_VERBOSITY == 1) ? "terse" : "verbose") + \
                      " storage per: " + String(__FUNCTION__) + "()") ;                              \
    Trace::DumpStore(store , node_desc) ;                                                            }

  #define DEBUG_TRACE_DUMP_ITEMS_TREE(root_item , tree_desc) \
  if (DEBUG_DUMP_VERBOSITY > 0) {                                                                       \
    Trace::TraceStore("dumping "          + String((DEBUG_DUMP_VERBOSITY == 1) ? "terse" : "verbose") + \
                      " tree items per: " + String(__FUNCTION__) + "()") ;                              \
    Trace::DumpItemsTree(root_item , tree_desc) ;                                                       }

  #define DEBUG_WRITE_STORE_XML(node , node_desc) Trace::WriteNodeToXml(node , node_desc) ;


class Trace
{
public:

  static void EnableTracing(bool should_enable) ;

  static void TraceEvent     (String msg) ;
  static void TraceGui       (String msg) ;
  static void TraceGuiVb     (String msg) ;
  static void TraceMedia     (String msg) ;
  static void TraceMediaVb   (String msg) ;
  static void TraceStore     (String msg) ;
  static void TraceStoreVb   (String msg) ;
  static void TraceNoPrefix  (String msg) ;
  static void TraceNoPrefixVb(String msg) ;
  static void TraceState     (String msg) ;
  static void TraceWarning   (String msg) ;
  static void TraceError     (String msg) ;
  static void TraceDebug     (String msg) ;

  static void TraceMissingNode    (ValueTree store , Identifier node_id) ;
  static void TraceMissingProperty(ValueTree store , Identifier property_id , var default_value) ;
  static void DumpStore           (ValueTree store , String node_desc) ;
  static void DumpItemsTree       (TreeViewItem* root_item , String tree_desc) ;
  static void WriteNodeToXml      (ValueTree node , String node_desc) ;

  static String VarType          (var a_var) ;
  static void   TraceTreeChanged (ValueTree& node , const Identifier& key) ;
  static void   TraceValueChanged(Value& a_value , String name) ;
  static String TraceSetValue    (ValueTree node , const Identifier& key , var value) ;


  static bool EventEnabled ;
  static bool GuiEnabled ;
  static bool GuiVbEnabled ;
  static bool MediaEnabled ;
  static bool MediaVbEnabled  ;
  static bool StoreEnabled ;
  static bool StoreVbEnabled ;
  static bool StateEnabled ;
  static bool WarningsEnabled ;
  static bool ErrorsEnabled ;
} ;

#else // DEBUG_TRACE

  #define DEBUG_TRACE_DUMP_STORE(store , node_desc)          ;
  #define DEBUG_TRACE_DUMP_ITEMS_TREE(root_item , tree_desc) ;
  #define DEBUG_WRITE_STORE_XML(node , node_desc)            ;

#endif // DEBUG_TRACE
