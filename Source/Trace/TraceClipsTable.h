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
/*
  #define ANCESTOR_NODE_IDS StringArray::fromLines(parent_node.           .getName() + newLine + \
                                                   parent_node.getParent().getName()           ) ;

  #define isClipsNode       (parent_node) ANCESTOR_NODE_IDS  .contains(STORE::CLIPS_ID       )
  #define isCompilationsNode(parent_node) ANCESTOR_NODE_IDS  .contains(STORE::COMPILATIONS_ID)
  #define isMasterNode      (parent_node) STORE::CLIPS_STORES.contains(parent_node            .getName())
  #define isClipNode        (parent_node) STORE::CLIPS_STORES.contains(parent_node.getParent().getName())
*/

  #define isClipsNode(parent_node)                  \
    (parent_node             == this->clipsStore || \
     parent_node.getParent() == this->clipsStore    )

  #define isCompilationsNode(parent_node)                  \
    (parent_node             == this->compilationsStore || \
     parent_node.getParent() == this->compilationsStore    )

  #define isMasterNode(parent_node)            \
    (parent_node == this->clipsStore        || \
     parent_node == this->compilationsStore    )

  #define isClipNode(parent_node)                          \
    (parent_node.getParent() == this->clipsStore        || \
     parent_node.getParent() == this->compilationsStore    )



  #define DEBUG_TRACE_NEW_MASTER_ITEM                                     \
    Trace::TraceGui("preparing new master item: [ " + master_text + " ]") ;

  #define DEBUG_TRACE_NEW_CLIP_ITEM                                                         \
    Trace::TraceGui("preparing new clip item: [ " + clip_text     + "," + file_text + "," + \
                                                    begin_text    + "," + end_text  + "," + \
                                                    duration_text + " ]")                 ;

  #define DEBUG_TRACE_CREATE_MASTER_ITEM                                        \
    String master_id = STRING(master_node.getType()) ;                          \
    String root_id   = STRING(root_store .getType()) ;                          \
    Trace::TraceGui(     "creating master item '" + master_item_id     + "'") ; \
    Trace::TraceNoPrefix("for source '"           + master_id          + "'") ; \
    Trace::TraceNoPrefix("at index "              + String(master_idx) +        \
                         " of root store '"       + root_id            + "'")   ;

  #define DEBUG_TRACE_CREATE_CLIP_ITEM                                              \
    String master_id           = STRING(master_node.getType()) ;                    \
    String root_id             = STRING(root_store .getType()) ;                    \
    String clip_id             = STRING(clip_node  .getType()) ;                    \
    String existing_master_msg = (does_master_item_exist) ? "existing" : "new" ;    \
    if (!does_master_item_exist)                                                    \
    { Trace::TraceGui     ("creating master item '" + master_item_id     + "'") ;   \
      Trace::TraceNoPrefix("for source '"           + master_id          +          \
                           "' at index "            + String(master_idx) +          \
                           " of root store '"       + root_id            + "'") ; } \
    Trace::TraceGui(     "creating clip item '" + clip_item_id        + "'") ;      \
    Trace::TraceNoPrefix("for source '"         + clip_id             + "'") ;      \
    Trace::TraceNoPrefix("at index "            + String(clip_idx)    +             \
                         " of "                 + existing_master_msg +             \
                         " master item '"       + master_item_id      + "'") ;      \
    Trace::TraceNoPrefix("for source '"         + master_id           + "'") ;      \
    Trace::TraceNoPrefix("at index "        + String(master_idx) +                  \
                         " of root store '" + root_id + "'"      ) ;                \
    DEBUG_TRACE_DUMP_ITEMS_TREE(root_item , STRING(root_store.getType()))

  #define DEBUG_TRACE_INIT_STORAGE(clips_store)                                                     \
    int n_masters = clips_store.getNumChildren() ; int n_clips = 0 ;                   \
    for (int master_n = 0 ; master_n < n_clips ; ++master_n)                           \
      n_clips += clips_store.getChild(master_n).getNumChildren() ;                     \
    Trace::TraceGui("creating tree items for '" + clips_store.getType()  + "' - ("   + \
                    String(n_masters) + ") masters (" + String(n_clips)  + ") clips" ) ;

  #define DEBUG_TRACE_STORAGE_CHILD(a_node)                                               \
    String    node_id_              = STRING(a_node                 .getType()) ;         \
    String    parent_id_            = STRING(parent_node            .getType()) ;         \
    String    grandparent_id_       = STRING(parent_node.getParent().getType()) ;         \
    bool      is_master_node_       = isMasterNode      (parent_node) ;                   \
    bool      is_clip_node_         = isClipNode        (parent_node) ;                   \
    bool      is_clips_node_        = isClipsNode       (parent_node) ;                   \
    bool      is_compilations_node_ = isCompilationsNode(parent_node) ;                   \
    ValueTree root_store_           = (is_clips_node_       ) ? this->clipsStore        : \
                                      (is_compilations_node_) ? this->compilationsStore : \
                                                                ValueTree::invalid ;      \
    ValueTree master_node_          = (is_master_node_) ? a_node             :            \
                                      (is_clip_node_  ) ? a_node.getParent() :            \
                                                          ValueTree::invalid ;            \
    String    master_idx_           = String(root_store_.indexOf(master_node_)) ;         \
    String    node_role             = (is_master_node_) ? "master " :                     \
                                      (is_clip_node_  ) ? "clip"    : "(unknown)" ;       \
    String    master_msg            = "master '"    + parent_id_           +              \
                                      "' at index " + master_idx_ + " of " ;              \
    String    ancestry_msg          = ((is_clip_node_  ) ? master_msg : "")             + \
                                      ((is_master_node_) ? parent_id_      :              \
                                       (is_clip_node_  ) ? grandparent_id_ : "(unknown)") ;

  #define DEBUG_TRACE_STORAGE_CHILD_ADDED                                                 \
    DEBUG_TRACE_STORAGE_CHILD(new_node)                                                   \
    Trace::TraceGui     ("new storage node for " + node_role    + "'" + node_id_ + "'") ; \
    Trace::TraceNoPrefix("added to "             + ancestry_msg                       )   ;

  #define DEBUG_TRACE_STORAGE_CHILD_REMOVED                                                    \
    DEBUG_TRACE_STORAGE_CHILD(deleted_node)                                                    \
    Trace::TraceGui     ("storage node for "   + node_role        + "'"    + node_id_ + "'") ; \
    Trace::TraceNoPrefix("deleted from index " + String(prev_idx) + " of " + ancestry_msg  )   ;

  #define DEBUG_TRACE_CLIPITEM                                                                \
    String item_role  = (is_root_item    ) ? "root_item"   :                                  \
                        (is_master_item  ) ? "master_item" :                                  \
                        (is_clip_item    ) ? "clip_item"   :                                  \
                        (this->isLeafItem) ? "leaf_item"   : "invalid_item" ;                 \
    String item_class = (this->itemClass == GUI::MASTER_ITEM) ? "MASTER_ITEM" :               \
                        (this->itemClass == GUI::CLIP_ITEM  ) ? "CLIP_ITEM"   : "CLIP_ITEM" ; \
    Trace::TraceGui("adding " + item_role + "(" + item_class + ") ClipItem to ClipsTable (" + \
                    keyText + "|" + valueText + ")"                                         ) ;

#else // DEBUG_TRACE

  #define DEBUG_TRACE_NEW_MASTER_ITEM       ;
  #define DEBUG_TRACE_NEW_CLIP_ITEM         ;
  #define DEBUG_TRACE_CREATE_MASTER_ITEM    ;
  #define DEBUG_TRACE_CREATE_CLIP_ITEM      ;
  #define DEBUG_TRACE_INIT_STORAGE(unused)  ;
  #define DEBUG_TRACE_STORAGE_CHILD_ADDED   ;
  #define DEBUG_TRACE_STORAGE_CHILD_REMOVED ;
  #define DEBUG_TRACE_CLIPITEM              ;

#endif // DEBUG_TRACE
