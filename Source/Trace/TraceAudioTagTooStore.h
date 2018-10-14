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

  #define DEBUG_PRIME_CLIPS_STORAGE if (DEBUG_PRIME_STORAGE)              \
    createClip(String("/path/to/dummy_audio_file") , 0.123456 , 6.543210) ;

  #define DEBUG_TRACE_SET_PROPERTY                                                                 \
    if (!node.isValid()) Trace::TraceError("request to set property on invalid tree - ignoring") ;

  #define DEBUG_TRACE_SET_CONFIG                                                     \
    String node_id            = STRING(config_node.getType()) ;                      \
    String key_str            = STRING(key) ;                                        \
    bool   is_not_config_node = config_node != this->root ;                          \
    bool   is_not_config_key  = !isKnownProperty(this->root , key) ;                 \
    String change_msg         = Trace::TraceSetValue(config_node , key , value) ;    \
    String node_error_msg     = "non-config node '"  + node_id + "' - (ignoring) " ; \
    String key_error_msg      = "unknown key '"      + key_str + "' - (ignoring) " ; \
    if      (is_not_config_node) Trace::TraceError  (node_error_msg + change_msg) ;  \
    else if (is_not_config_key ) Trace::TraceError  (key_error_msg  + change_msg) ;  \
    else                         Trace::TraceStoreVb(                 change_msg)    ;

  #define DEBUG_TRACE_CREATE_CLIP                                                        \
    String master_msg = "master: '" + master_id + "'" ; StringArray warnings ;           \
    if (!does_file_exist ) warnings.add("file not found: " + audio_filename) ;           \
    if (!is_valid_length ) warnings.add("invalid clip length: " + String(end_time  ) +   \
                                        " - " +                   String(begin_time) ) ; \
    if (is_duplicate_clip) warnings.add("duplicate clip exists: " + clip_id) ;           \
    if (is_id_collision  ) warnings.add("ID collision creating " + master_msg) ;         \
    if (!warnings.isEmpty())                                                             \
      for (String warning : warnings) Trace::TraceWarning(warning    + " - ignoring") ;  \
    else { if (is_new_master)         Trace::TraceStore  ("created " + master_msg) ;     \
           Trace::TraceStore ("creating clip: '" + clip_id + "'") ;                      \
           Trace::TraceNoPrefix("derived from " + master_msg) ;                          \
           Trace::TraceNoPrefixVb("audio_filename=" + audio_filename     +               \
                                  " begin_time="    + String(begin_time) +               \
                                  " end_time="      + String(end_time  ) ) ;             }

  #define DEBUG_TRACE_VERIFY_STORED_CONFIG                                                     \
    String not_found_msg = "stored config not found - restoring defaults" ;                    \
    String invalid_msg   = "stored config invalid - restoring defaults" ;                      \
    String corrupt_msg   = "stored config corrupt - pruning duplicated nodes" ;                \
    String upgraded_msg  = "upgrading config version from v" + String(stored_version) +        \
                           " to v"                           + String(STORE::CONFIG_VERSION) ; \
    String success_msg   = "stored config parsed successfully v" + String(stored_version) ;    \
    int    n_masters     = this->clips.getNumChildren() ;                                      \
    int    n_clips       = 0 ; for (int master_n = 0 ; master_n < n_masters ; ++master_n)      \
           n_clips      += this->clips.getChild(master_n).getNumChildren() ;                   \
    Trace::TraceStore("looking for stored config at " + this->storageFile.getFullPathName()) ; \
    Trace::TraceStore((!was_storage_found  ) ? not_found_msg :                                 \
                      (!is_root_valid      ) ? invalid_msg   :                                 \
                      (!has_canonical_nodes) ? corrupt_msg   :                                 \
                      (!do_versions_match  ) ? upgraded_msg  : success_msg) ;                  \
    Trace::TraceStore(String(n_clips  ) + " clips declared from " +                            \
                      String(n_masters) + " master sources"       )                            ;

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

  #define DEBUG_TRACE_LISTEN                                   \
    String state = (should_listen) ? "resumed" : "suspended" ; \
    Trace::TraceStore(state + " listening for model changes")  ;

  #define DEBUG_TRACE_CONFIG_TREE_CHANGED Trace::TraceTreeChanged(node , key) ;

  #define DEBUG_TRACE_DEVICE_STATE_CHANGED                                                           \
    Trace::TraceState("audio device state changed: " + String((is_device_ready) ? "ready" : "idle")) ;

#else // DEBUG_TRACE

  #define DEBUG_PRIME_CLIPS_STORAGE           ;
  #define DEBUG_TRACE_SET_PROPERTY            ;
  #define DEBUG_TRACE_SET_CONFIG              ;
  #define DEBUG_TRACE_CREATE_CLIP             ;
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
  #define DEBUG_TRACE_DEVICE_STATE_CHANGED    ;

#endif // DEBUG_TRACE
