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

  /* helpers */

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


  /* ClipsTableItem */

  #define DEBUG_TRACE_NEW_MASTER_ITEM                                    \
    Trace::TraceGui("preparing new master item: '" + filename   + "'") ; \
    Trace::TraceNoPrefix("item_id : '"             + item_id    + "'") ; \
    Trace::TraceNoPrefix("data    : ("             + label_text + "|)")  ;

  #define DEBUG_TRACE_NEW_CLIP_ITEM                                                                    \
    Trace::TraceGui     ("preparing new clip item:") ;                                                 \
    Trace::TraceNoPrefix("item_id     : '" + item_id                 + "'") ;                         \
    Trace::TraceNoPrefix("file_id     : '" + file_id                  + "'") ;                         \
    Trace::TraceNoPrefix("begin_id    : '" + begin_id                 + "'") ;                         \
    Trace::TraceNoPrefix("end_id      : '" + end_id                   + "'") ;                         \
    Trace::TraceNoPrefix("duration_id : '" + duration_id              + "'") ;                         \
    Trace::TraceNoPrefix("data        : (" + label_text               + "|"                   + ")") ; \
    Trace::TraceNoPrefix("              (" + GUI::FILE_ITEM_LABEL     + "|" + file_text       + ")") ; \
    Trace::TraceNoPrefix("              (" + GUI::BEGIN_ITEM_LABEL    + "|" + begin_text      + ")") ; \
    Trace::TraceNoPrefix("              (" + GUI::END_ITEM_LABEL      + "|" + end_text        + ")") ; \
    Trace::TraceNoPrefix("              (" + GUI::DURATION_ITEM_LABEL + "|" + duration_text   + ")")   ;

  #define DEBUG_TRACE_CREATE_MASTER_ITEM                                        \
    String master_id = STRING(master_node.getType()) ;                          \
    String root_id   = STRING(root_store .getType()) ;                          \
    Trace::TraceGui(     "creating master item '" + item_id            + "'") ; \
    Trace::TraceNoPrefix("for source '"           + master_id          + "'") ; \
    Trace::TraceNoPrefix("at index "              + String(master_idx) +        \
                         " of root store '"       + root_id            + "'")   ;

  #define DEBUG_TRACE_CREATE_CLIP_ITEM                                               \
    String master_id           = STRING(master_node.getType()) ;                     \
    String root_id             = STRING(root_store .getType()) ;                     \
    String clip_id             = STRING(clip_node  .getType()) ;                     \
    String existing_master_msg = (does_master_item_exist) ? "existing" : "new" ;     \
    if (!does_master_item_exist)                                                     \
    { Trace::TraceGui     ("creating master item '" + master_item_id      + "'") ;   \
      Trace::TraceNoPrefix("for source '"           + master_id           +          \
                           "' at index "            + String(master_idx)  +          \
                           " of root store '"       + root_id             + "'") ; } \
    Trace::TraceGui       ("creating clip item '"   + clip_item_id        + "'") ;   \
    Trace::TraceNoPrefix  ("for source '"           + clip_id             + "'") ;   \
    Trace::TraceNoPrefix  ("at index "              + String(clip_idx)    +          \
                           " of "                   + existing_master_msg +          \
                           " master item '"         + master_item_id      + "'") ;   \
    Trace::TraceNoPrefix  ("for source '"           + master_id           + "'") ;   \
    Trace::TraceNoPrefix  ("at index "              + String(master_idx)  +          \
                           " of root store '"       + root_id + "'"       ) ;        \
    DEBUG_TRACE_DUMP_ITEMS_TREE(root_item , STRING(root_store.getType()))            ;

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
    String    master_msg            = "master '"    + parent_id_  +                       \
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


  /* ClipsTableItem subclasses */

  #define DEBUG_TRACE_MASTERCLIPSTABLEITEM                                     \
    Trace::TraceGui("configuring MasterClipsTableItem (" + label_text + "|n/a)") ;

  #define DEBUG_TRACE_CLIPCLIPSTABLEITEM                                       \
    Trace::TraceGui("configuring ClipClipsTableItem   (" + label_text + "|n/a)") ;

  #define DEBUG_TRACE_LEAFCLIPSTABLEITEM                                                   \
    Trace::TraceGui("configuring LeafClipsTableItem   (" + key_text   + "|" + value_text + \
                    ") " + ((is_standard_metadata) ? "immutable" : "mutable")            ) ;


  /* ClipItem */

  #define X___DEBUG_TRACE_CLIPITEM                                                                     \
    String item_role  = (is_root_item    ) ? "root_item"   :                                       \
                        (is_master_item  ) ? "master_item" :                                       \
                        (is_clip_item    ) ? "clip_item"   :                                       \
                        (this->isLeafItem) ? "leaf_item"   : "invalid_item" ;                      \
    String item_class = (this->itemClass == GUI::ROOT_ITEM   ) ? "MASTER_ITEM" :                   \
                        (this->itemClass == GUI::MASTER_ITEM ) ? "MASTER_ITEM" :                   \
                        (this->itemClass == GUI::CLIP_ITEM   ) ? "CLIP_ITEM"   :                   \
                        (this->itemClass == GUI::LEAF_ITEM   ) ? "LEAF_ITEM"   :                   \
                        (this->itemClass == GUI::INVALID_ITEM) ? "LEAF_ITEM"   : "!ERROR!" ;       \
    Trace::TraceGui     ("adding ClipItem to ClipsTable: " + item_role + "(" + item_class + ")") ; \
    Trace::TraceNoPrefix("storeId : '" + this->storeId + "'") ;                                    \
    Trace::TraceNoPrefix("data    : (" + this->keyText + "|" + this->valueText + ")")              ;

#else // DEBUG_TRACE

  #define DEBUG_TRACE_NEW_MASTER_ITEM       ;
  #define DEBUG_TRACE_NEW_CLIP_ITEM         ;
  #define DEBUG_TRACE_CREATE_MASTER_ITEM    ;
  #define DEBUG_TRACE_CREATE_CLIP_ITEM      ;
  #define DEBUG_TRACE_INIT_STORAGE(unused)  ;
  #define DEBUG_TRACE_STORAGE_CHILD_ADDED   ;
  #define DEBUG_TRACE_STORAGE_CHILD_REMOVED ;
  #define DEBUG_TRACE_MASTERCLIPSTABLEITEM  ;
  #define DEBUG_TRACE_CLIPCLIPSTABLEITEM    ;
  #define DEBUG_TRACE_LEAFCLIPSTABLEITEM    ;
  #define DEBUG_TRACE_CLIPITEM              ;

#endif // DEBUG_TRACE
