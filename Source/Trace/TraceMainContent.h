/*\
|*|  AudioTagToo - Clip and stitch audio samples
|*|  Copyright 2018 bill-auger <https://github.com/bill-auger/audio-tag-too/issues>
|*|
|*|  This file is part of the AudioTagToo program.
|*|
|*|  AudioTagToo is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU General Public License version 3
|*|  as published by the Free Software Foundation.
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

  #define DEBUG_TRACE_NEW_MASTER_ITEM                                      \
    Trace::TraceGui("preparing new master item: [ " + master_label + " ]") ;

  #define DEBUG_TRACE_NEW_CLIP_ITEM                                                        \
    Trace::TraceGui("preparing new clip item: [ " + clip_label  + "," + file_label + "," + \
                                                    begin_label + "," + end_label  + " ]") ;

  #define DEBUG_TRACE_CREATE_MASTER_ITEM                                \
    String master_item_id = master_item->getItemIdentifierString() ;    \
    String master_id      = STRING(master_node.getType()) ;             \
    String root_id        = STRING(root_store.getType()) ;              \
    Trace::TraceGui(     "creating master item '" + master_item_id  +   \
                         "' for source '"         + master_id + "'" ) ; \
    Trace::TraceNoPrefix("at index "        + String(master_idx) +      \
                         " of root store '" + root_id + "'"      )      ;

  #define DEBUG_TRACE_CREATE_CLIP_ITEM                                           \
    String master_item_id      = master_item->getItemIdentifierString() ;        \
    String clip_item_id        = clip_item->getItemIdentifierString() ;          \
    String master_id           = STRING(master_node.getType()) ;                 \
    String root_id             = STRING(root_store.getType()) ;                  \
    String clip_id             = STRING(clip_node.getType()) ;                   \
    String existing_master_msg = (does_master_item_exist) ? "existing" : "new" ; \
    if (!does_master_item_exist)                                                 \
      Trace::TraceGui("creating master item '" + master_item_id     +            \
                      "' for source '"         + master_id          +            \
                      "' at index "            + String(master_idx) +            \
                      " of root store '"       + root_id + "'"      ) ;          \
    Trace::TraceGui(     "creating clip item '" + clip_item_id +                 \
                         "' for source '"       + clip_id + "'") ;               \
    Trace::TraceNoPrefix("at index "      + String(clip_idx) +                   \
                         " of "           + existing_master_msg +                \
                         " master item '" + master_item_id   +                   \
                         "' for source '" + master_id + "'"  ) ;                 \
    Trace::TraceNoPrefix("at index "        + String(master_idx) +               \
                         " of root store '" + root_id + "'"      )               ;

  #define DEBUG_TRACE_STORAGE_REDIRECTED                                               \
    int n_masters = root_store.getNumChildren() ; int n_clips = 0 ;                    \
    for (int master_n = 0 ; master_n < n_masters  ; ++master_n)                        \
      n_clips += root_store.getChild(master_n).getNumChildren() ;                      \
    Trace::TraceGui("storage source changed for '" + root_store.getType() + "' - ("  + \
                    String(n_masters) + ") masters (" + String(n_clips ) + ") clips" ) ;

  #define DEBUG_TRACE_STORAGE_CHILD_ADDED                                                 \
    String node_id        = STRING(new_node.getType()) ;                                  \
    String parent_id      = STRING(parent_node.getType()) ;                               \
    String grandparent_id = STRING(parent_node.getParent().getType()) ;                   \
    bool   is_master_node = is_master_clips_node || is_master_compilations_node ;         \
    bool   is_clip_node   = is_clip_clips_node   || is_clip_compilations_node ;           \
    String node_role_msg  = (is_master_node) ? "master " :                                \
                            (is_clip_node  ) ? "clip"    : "(unknown)" ;                  \
    String master_msg     = (is_clip_node  ) ? "master '" + String(parent_id) + "' of " : \
                                               String::empty ;                            \
    String root_msg       = (is_master_node) ? parent_id      :                           \
                            (is_clip_node  ) ? grandparent_id : "(unknown)" ;             \
    Trace::TraceGui("new storage node for " + node_role_msg + "'" + node_id +             \
                    "' added to "           + master_msg    + root_msg      )             ;

  #define DEBUG_TRACE_STORAGE_CHILD_REMOVED                                                      \
    String node_id        = STRING(deleted_node.getType()) ;                                     \
    String parent_id      = STRING(parent_node.getType()) ;                                      \
    String grandparent_id = STRING(parent_node.getParent().getType()) ;                          \
    String master_msg     = (is_clip_node) ? "master '"    + parent_id                   +       \
                                             "' at index " + String(master_idx) + " of " : "" ;  \
    String root_msg       = (is_master_node) ? parent_id      :                                  \
                            (is_clip_node  ) ? grandparent_id : "(unknown)" ;                    \
    String node_role_msg  = (is_master_node) ? "master " :                                       \
                            (is_clip_node  ) ? "clip"    : "(unknown)" ;                         \
    Trace::TraceGui("storage node for "     + node_role_msg    + "'"    + node_id              + \
                    "' deleted from index " + String(prev_idx) + " of " + master_msg + root_msg) ;

#else // DEBUG_TRACE

  #define DEBUG_TRACE_NEW_MASTER_ITEM       ;
  #define DEBUG_TRACE_NEW_CLIP_ITEM         ;
  #define DEBUG_TRACE_CREATE_MASTER_ITEM    ;
  #define DEBUG_TRACE_CREATE_CLIP_ITEM      ;
  #define DEBUG_TRACE_STORAGE_REDIRECTED    ;
  #define DEBUG_TRACE_STORAGE_CHILD_ADDED   ;
  #define DEBUG_TRACE_STORAGE_CHILD_REMOVED ;

#endif // DEBUG_TRACE
