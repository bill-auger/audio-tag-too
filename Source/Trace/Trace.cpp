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


#include "../Constants/AppConstants.h"
#include "../Constants/StorageConstants.h"
#include "Trace.h"


#ifdef DEBUG_TRACE

/* Trace class public class variables */

bool Trace::EventEnabled    = DEBUG_TRACE_EVENTS   ;
bool Trace::GuiEnabled      = DEBUG_TRACE_GUI      ;
bool Trace::GuiVbEnabled    = DEBUG_TRACE_GUI_VB   ;
bool Trace::MediaEnabled    = DEBUG_TRACE_MEDIA    ;
bool Trace::MediaVbEnabled  = DEBUG_TRACE_MEDIA_VB ;
bool Trace::StoreEnabled    = DEBUG_TRACE_STORE    ;
bool Trace::StoreVbEnabled  = DEBUG_TRACE_STORE_VB ;
bool Trace::StateEnabled    = DEBUG_TRACE_STATE    ;
bool Trace::WarningsEnabled = DEBUG_TRACE_WARNINGS ;
bool Trace::ErrorsEnabled   = DEBUG_TRACE_ERRORS   ;


/* Trace class public class methods */

void Trace::EnableTracing(bool should_enable)
{
#if DEBUG_TRACE || DEBUG_TRACE_VB
Trace::TraceState("debug tracing " + String((should_enable) ? "enabled" : "disabled")) ;
#endif // DEBUG_TRACE

  EventEnabled    = (DEBUG_TRACE_EVENTS  ) && should_enable ;
  GuiEnabled      = (DEBUG_TRACE_GUI     ) && should_enable ;
  GuiVbEnabled    = (DEBUG_TRACE_GUI_VB  ) && should_enable ;
  MediaEnabled    = (DEBUG_TRACE_MEDIA   ) && should_enable ;
  MediaVbEnabled  = (DEBUG_TRACE_MEDIA_VB) && should_enable ;
  StoreEnabled    = (DEBUG_TRACE_STORE   ) && should_enable ;
  StoreVbEnabled  = (DEBUG_TRACE_STORE_VB) && should_enable ;
  StateEnabled    = (DEBUG_TRACE_STATE   ) && should_enable ;
  WarningsEnabled = (DEBUG_TRACE_WARNINGS) && should_enable ;
  ErrorsEnabled   = (DEBUG_TRACE_ERRORS  ) && should_enable ;
}

void Trace::TraceEvent     (String msg) { if (EventEnabled   ) LOG(          "[EVENT]:   " + msg       ) ; }
void Trace::TraceGui       (String msg) { if (GuiEnabled     ) LOG(          "[GUI]:     " + msg       ) ; }
void Trace::TraceGuiVb     (String msg) { if (GuiVbEnabled   ) LOG(          "[GUI]:     " + msg       ) ; }
void Trace::TraceMedia     (String msg) { if (MediaEnabled   ) LOG(          "[MEDIA]:   " + msg       ) ; }
void Trace::TraceMediaVb   (String msg) { if (MediaVbEnabled ) LOG(          "[MEDIA]:   " + msg       ) ; }
void Trace::TraceStore     (String msg) { if (StoreEnabled   ) LOG(          "[STORE]:   " + msg       ) ; }
void Trace::TraceStoreVb   (String msg) { if (StoreVbEnabled ) LOG(          "[STORE]:   " + msg       ) ; }
void Trace::TraceNoPrefix  (String msg) {                      LOG(          "           " + msg       ) ; }
void Trace::TraceNoPrefixVb(String msg) { if (DEBUG_TRACE_VB ) LOG(          "           " + msg       ) ; }
void Trace::TraceState     (String msg) { if (StateEnabled   ) LOG(CGREEN  + "[STATE]:   " + msg + CEND) ; }
void Trace::TraceWarning   (String msg) { if (WarningsEnabled) LOG(CYELLOW + "[WARNING]: " + msg + CEND) ; }
void Trace::TraceError     (String msg) { if (ErrorsEnabled  ) LOG(CRED    + "[ERROR]:   " + msg + CEND) ; }
void Trace::TraceDebug     (String msg) {                      LOG(CYELLOW + "[DEBUG]:   " + msg + CEND) ; }

void Trace::TraceMissingNode(ValueTree store , Identifier node_id)
{
  if (!store.getChildWithName(node_id).isValid())
    Trace::TraceStore("missing node of '" + STRING(store.getType())      +
                      "' - adding '"      + STRING(node_id        ) + "'") ;
}

void Trace::TraceMissingProperty(ValueTree store , Identifier property_id , var default_value)
{
  if (!store.hasProperty(property_id))
  {
    Trace::TraceStore("missing property of '"       + STRING(store.getType())            +
                      "' - restoring default for '" + STRING(property_id    ) + "' => '" +
                                                      STRING(default_value  ) + "'"      ) ;
    DEBUG_TRACE_DUMP_STORE(store , "missing property ") ;
  }
}

void Trace::DumpStore(ValueTree store , String node_desc)
{
#if (DEBUG_DUMP_VERBOSITY >= 1)
  if (!store.isValid()) { Trace::TraceError("invalid node: " + node_desc) ; return ; }

  // terse enumeration
  String node_name    = STRING(store.getType()) ;
  int    n_properties =        store.getNumProperties() ;
  int    n_children   =        store.getNumChildren() ;

  String pad = "  " ;
  String dbg = "dumping node: " + node_desc            + " =>\n" + pad +
               "id => "         + node_name                            +
               " (properties: " + String(n_properties) + ")"           +
               " (children: "   + String(n_children)   + ")"           ;

  #if (DEBUG_DUMP_VERBOSITY >= 2)
  // full properties itemization
  for (int property_n = 0 ; property_n < n_properties ; ++property_n)
  {
    Identifier key          = store.getPropertyName(property_n) ;
    var        stored_value = store.getProperty(key , "n/a") ;
    dbg += "\n" + pad + "  key => "             + STRING(key)             +
           "\n" + pad + "    stored_value  => " + stored_value.toString() ;
  }
  #endif // DEBUG_DUMP_VERBOSITY

  Trace::TraceStore(dbg) ;

  // recurse over child nodes
  for (int child_n = 0 ; child_n < n_children ; ++child_n)
  {
    ValueTree child_node      = store.getChild(child_n) ;
    String    child_id        = STRING(child_node.getType()) ;
    String    child_node_desc = "'"     + node_name + "["  + String(child_n) +
                                "]] ('" + child_id  + "')"                   ;

    DumpStore(child_node , child_node_desc) ;
  }
#endif // DEBUG_DUMP_VERBOSITY
}

void Trace::DumpItemsTree(TreeViewItem* root_item , String tree_desc)
{
#if (DEBUG_DUMP_VERBOSITY >= 1)
  // terse enumeration
  String root_item_id = root_item->getUniqueName() ;
  int    n_items      = root_item->getNumSubItems() ;
  int    n_sub_items  = 0 ;

  for (int item_n = 0 ; item_n < n_items ; ++item_n)
    n_sub_items += root_item->getSubItem(item_n)->getNumSubItems() ;

  String pad = "  " ;
  String dbg = "dumping items tree: " + tree_desc           + " =>\n" + pad +
               "id => "               + root_item_id                        +
               " (items: "            + String(n_items)     + ")"           +
               " (sub-items: "        + String(n_sub_items) + ")"           ;

  Trace::TraceStore(dbg) ;

  #if (DEBUG_DUMP_VERBOSITY >= 2)
  // recurse over child nodes
  for (int item_n = 0 ; item_n < n_items ; ++item_n)
  {
    TreeViewItem* item      = root_item->getSubItem(item_n) ;
    String        item_id   = item->getUniqueName() ;
    String        item_desc = "'"     + root_item_id + "["  + String(item_n) +
                              "]] ('" + item_id      + "')"                  ;
    DumpItemsTree(item , item_desc) ;
  }
  #endif // DEBUG_DUMP_VERBOSITY
#endif // DEBUG_DUMP_VERBOSITY
}

void Trace::WriteNodeToXml(ValueTree node , String node_desc)
{
#if DEBUG_WRITE_XML
  XmlElement* xml         = node.createXml() ;
  File        storage_dir = APP::AppdataDir().getChildFile(STORE::STORAGE_DIRNAME) ;
  File        dump_file   = storage_dir      .getChildFile("store-dump-" + node_desc + ".xml") ;

  xml->writeToFile(dump_file , StringRef() , StringRef("UTF-8") , 0) ; delete xml ;
  Trace::TraceStore("marshalled storage node to file: '" + dump_file.getFullPathName() +
                    "' as XML per "                      + String(__FUNCTION__))       ;
#endif // DEBUG_WRITE_XML
}

String Trace::VarType(var a_var) // juce var dynamic datatypes
{
  return (a_var.isVoid()      ) ? "void"      :
         (a_var.isUndefined() ) ? "undefined" :
         (a_var.isInt()       ) ? "int"       :
         (a_var.isInt64()     ) ? "int64"     :
         (a_var.isBool()      ) ? "bool"      :
         (a_var.isDouble()    ) ? "double"    :
         (a_var.isString()    ) ? "string"    :
         (a_var.isObject()    ) ? "object"    :
         (a_var.isArray()     ) ? "array"     :
         (a_var.isBinaryData()) ? "binary"    :
         (a_var.isMethod()    ) ? "method"    :
                                  "unknown"   ;
}

void Trace::TraceTreeChanged(ValueTree& node , const Identifier& key)
{
  String parent_id = STRING(node.getParent().getType()) ;
  String node_id   = parent_id + ((parent_id.isEmpty()) ? "" : "::") + STRING(node.getType()) ;
  String var_type  = VarType(node[key]) ;
  String value     = STRING(node[key]).upToFirstOccurrenceOf("?" , true  , true) ;

  Trace::TraceEvent("value changed for tree " + node_id  + "['" + STRING(key)       +
                    "'] => ("                 + var_type + ")'" + value       + "'" ) ;
}

void Trace::TraceValueChanged(Value& a_value , String name)
{
  Trace::TraceEvent("value changed for '"   + name            + "' => (" +
                    VarType(a_value) + ")'" + STRING(a_value) + "'"      ) ;
}

String Trace::TraceSetValue(ValueTree node , const Identifier& key , var value)
{
  String prev_type  = Trace::VarType(node[key]) ;
  String next_type  = Trace::VarType(value    ) ;
  String node_id    = (node.isValid()) ? STRING(node.getType()) : String("NULL") ;
  String prev_val   = (node.isValid()) ? STRING(node[key]     ) : String("NULL") ;
  String next_val   = STRING(value) ;
  String key_str    = (key .isValid()) ? STRING(key           ) : String("NULL") ;
  String change_msg = "key "               + node_id   + "['"  + key_str  +
                      "'] changing from (" + prev_type + ")'"  + prev_val +
                      "' to ("             + next_type + ")'"  + next_val + "'" ;

  return (next_type != prev_type || next_val != prev_val) ? change_msg : String::empty ;
}

#endif // DEBUG_TRACE

