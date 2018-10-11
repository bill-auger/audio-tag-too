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
  #define DEBUG_TRACE_SET_CONFIG              ;

#endif // DEBUG_TRACE
