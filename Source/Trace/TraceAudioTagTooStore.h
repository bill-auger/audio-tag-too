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

#include "Trace.h"


#if DEBUG_TRACE

/* persistence */

  #define DEBUG_TRACE_VERIFY_STORED_CONFIG                                                      \
    String not_found_msg = "stored config not found - restoring defaults" ;                     \
    String invalid_msg   = "stored config invalid - restoring defaults" ;                       \
    String corrupt_msg   = "stored config corrupt - pruning duplicated nodes" ;                 \
    String upgraded_msg  = "upgrading config version from v" + String(stored_version) +         \
                           " to v"                           + String(STORE::CONFIG_VERSION) ;  \
    String success_msg   = "stored config parsed successfully v" + String(stored_version) ;     \
    Trace::TraceStore("looking for stored config at " + this->storageFile.getFullPathName()) ;  \
    Trace::TraceStore((!was_storage_found  ) ? not_found_msg :                                  \
                      (!is_root_valid      ) ? invalid_msg   :                                  \
                      (!has_canonical_nodes) ? corrupt_msg   :                                  \
                      (!do_versions_match  ) ? upgraded_msg  : success_msg)                     ;

  #define DEBUG_TRACE_VERIFY_MISSING_NODE    \
    Trace::TraceMissingNode(store , node_id) ;

  #define DEBUG_TRACE_VERIFY_MISSING_PROPERTY                \
    Trace::TraceMissingProperty(store , key , default_value) ;

  #define DEBUG_TRACE_FILTER_ROGUE_KEY                                                     \
    if (!persistent_keys.contains(property_id))                                            \
      Trace::TraceStore("removing rogue property '" + String(property_id)                + \
                        "' from '"                  + STRING(parent_node.getType()) + "'") ;

  #define DEBUG_TRACE_FILTER_ROGUE_NODE                                                \
    if (!persistent_node_ids.contains(node_id))                                        \
      Trace::TraceStore("removing rogue node '" + String(node_id)                    + \
                        "' from '"              + STRING(parent_node.getType()) + "'") ;

  #define DEBUG_TRACE_SANITIZE_INT_PROPERTY                                                     \
    String relation = String(min_value) + " <= " + String(value) + " <= " + String(max_value) ; \
    String node_id = STRING(store.getType()) ; String property_id = STRING(key) ;               \
    if (value < min_value || value > max_value)                                                 \
      Trace::TraceStore("value (" + relation + ") out of range for '"  +                        \
                        node_id + "['" + property_id + "'] - removing" )                        ;

  #define DEBUG_TRACE_DUMP_STORE_ROOT DEBUG_TRACE_DUMP_STORE(this->root , "root")

  #define DEBUG_TRACE_DUMP_STORE_ALL \
    DEBUG_TRACE_DUMP_STORE_ROOT

  #define DEBUG_TRACE_STORE_CONFIG                                                        \
    String file_path = this->storageFile.getFullPathName() ;                              \
    if (!this->root.isValid()) Trace::TraceError("stored config invalid - not storing") ; \
    else                       Trace::TraceStore("storing config to " + file_path)        ;


/* maintenance */

  #define DEBUG_TRACE_LISTEN                                   \
    String state = (should_listen) ? "resumed" : "suspended" ; \
    Trace::TraceStore(state + " listening for model changes")  ;

  #define DEBUG_TRACE_CONFIG_TREE_CHANGED Trace::TraceTreeChanged(node , key) ;

  #define DEBUG_TRACE_SET_PROPERTY                                                                 \
    if (!node.isValid()) Trace::TraceError("request to set property on invalid tree - ignoring") ;

  // 'HAS_MAIN_CONTROLLER' switches can simply be removed if controller exists
  //                       or if such guards are not needed
  #ifdef HAS_MAIN_CONTROLLER
    #define MAIN_CONTROLLER_GUARD (AudioTagToo::IsInitialized && AudioTagToo::DisabledFeatures.contains(key))
  #else // HAS_MAIN_CONTROLLER
    #define MAIN_CONTROLLER_GUARD (true)
  #endif // HAS_MAIN_CONTROLLER
  #define DEBUG_TRACE_SET_CONFIG                                                           \
    ValueTree parent_node      = config_node.getParent() ;                                 \
    String    node_id          = STRING(config_node.getType()) ;                           \
    String    key_str          = STRING(key) ;                                             \
    bool      is_unknown_key   = !isKnownProperty(config_node , key) ;                     \
    bool      is_unknown_node  = config_node != this->root ;                               \
    String    invalid_tree_msg = "request to set property on invalid tree - ignoring" ;    \
    String    disabled_key_msg = "request to set disabled property - ignoring" ;           \
    String    change_msg       = ((!is_unknown_key) ? ""                               :   \
                                  (is_unknown_node) ? "unknown node '" + node_id + "'" :   \
                                                      "unknown key '"  + key_str + "'" ) + \
                                 ((!is_unknown_key) ? "" : " - (ignoring) "            ) + \
                                 Trace::TraceSetValue(config_node , key , value) ;         \
    if      (!config_node.isValid()) Trace::TraceError  (invalid_tree_msg) ;               \
    else if (MAIN_CONTROLLER_GUARD ) Trace::TraceError  (disabled_key_msg) ;               \
    else if (!is_unknown_key       ) Trace::TraceStoreVb(change_msg      ) ;               \
    else                             Trace::TraceError  (change_msg      )                 ;

#else // DEBUG_TRACE

  #define DEBUG_TRACE_VERIFY_STORED_CONFIG    ;
  #define DEBUG_TRACE_VERIFY_MISSING_NODE     ;
  #define DEBUG_TRACE_VERIFY_MISSING_PROPERTY ;
  #define DEBUG_TRACE_FILTER_ROGUE_KEY        ;
  #define DEBUG_TRACE_FILTER_ROGUE_NODE       ;
  #define DEBUG_TRACE_SANITIZE_INT_PROPERTY   ;
  #define DEBUG_TRACE_DUMP_STORE_ROOT         ;
  #define DEBUG_TRACE_DUMP_STORE_ALL          ;
  #define DEBUG_TRACE_STORE_CONFIG            ;
  #define DEBUG_TRACE_LISTEN                  ;
  #define DEBUG_TRACE_CONFIG_TREE_CHANGED     ;
  #define DEBUG_TRACE_SET_PROPERTY            ;
  #define DEBUG_TRACE_STORE_SET_VALUE         ;
  #define DEBUG_TRACE_GUI_SET_VALUE           ;

#endif // DEBUG_TRACE
