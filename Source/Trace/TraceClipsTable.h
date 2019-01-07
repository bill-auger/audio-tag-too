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


  /* ClipsTable */

  #define DEBUG_TRACE_NEW_MASTER_ITEM                                    \
    Trace::TraceGui("prepared new master item: '" + filename   + "'") ;  \
    Trace::TraceNoPrefix("master_id: '"            + master_id  + "'") ; \
    Trace::TraceNoPrefix("data     : ("            + label_text + "|)")  ;

  #define DEBUG_TRACE_NEW_CLIP_ITEM                                                              \
    Trace::TraceGui     ("prepared new clip item:") ;                                            \
    Trace::TraceNoPrefix("clip_id: '" + clip_id             + "'") ;                             \
    Trace::TraceNoPrefix("data   : (" + clip_label_text     + "|n/a"                    + ")") ; \
    Trace::TraceNoPrefix("         (" + file_label_text     + "|" + file_value_text     + ")") ; \
    Trace::TraceNoPrefix("         (" + begin_label_text    + "|" + begin_value_text    + ")") ; \
    Trace::TraceNoPrefix("         (" + end_label_text      + "|" + end_value_text      + ")") ; \
    Trace::TraceNoPrefix("         (" + duration_label_text + "|" + duration_value_text + ")")   ;

  #define DEBUG_TRACE_NEW_LEAF_ITEM                                       \
    Trace::TraceGui("prepared new leaf item: '"     + key        + "'") ; \
    Trace::TraceNoPrefix("data: (" + key_text + "|" + value_text + ")")   ;

  #define DEBUG_TRACE_CREATE_MASTER_ITEM                                       \
    String item_id   = master_item->getItemIdentifierString() ;                \
    String master_id = STRING(master_store.getType()) ;                        \
    String root_id   = STRING(root_store  .getType()) ;                        \
    Trace::TraceGui(     "created master item '" + item_id            + "'") ; \
    Trace::TraceNoPrefix("for source '"          + master_id          + "'") ; \
    Trace::TraceNoPrefix("at index "             + String(master_idx) +        \
                         " of root store '"      + root_id            + "'")   ;

  #define DEBUG_TRACE_CREATE_CLIP_ITEM                                              \
    String master_item_id      = master_item->getItemIdentifierString() ;           \
    String clip_item_id        = clip_item  ->getItemIdentifierString() ;           \
    String master_id           = STRING(master_store.getType()) ;                   \
    String root_id             = STRING(root_store  .getType()) ;                   \
    String clip_id             = STRING(clip_store  .getType()) ;                   \
    String existing_master_msg = (does_master_item_exist) ? "existing" : "new" ;    \
    if (!does_master_item_exist)                                                    \
    { Trace::TraceGui     ("created master item '" + master_item_id      + "'") ;   \
      Trace::TraceNoPrefix("for source '"          + master_id           +          \
                           "' at index "           + String(master_idx)  +          \
                           " of root store '"      + root_id             + "'") ; } \
    Trace::TraceGui       ("created clip item '"   + clip_item_id        + "'") ;   \
    Trace::TraceNoPrefix  ("for source '"          + clip_id             + "'") ;   \
    Trace::TraceNoPrefix  ("at index "             + String(clip_idx)    +          \
                           " of "                  + existing_master_msg +          \
                           " master item '"        + master_item_id      + "'") ;   \
    Trace::TraceNoPrefix  ("for source '"          + master_id           + "'") ;   \
    Trace::TraceNoPrefix  ("at index "             + String(master_idx)  +          \
                           " of root store '"      + root_id + "'"       ) ;        \
    DEBUG_TRACE_DUMP_ITEMS_TREE(root_item , STRING(root_store.getType()))           ;

  #define DEBUG_TRACE_CREATE_LEAF_ITEM                                         \
    String item_id = leaf_item->getItemIdentifierString() ;                    \
    if (clip_item == nullptr)                                                  \
      Trace::TraceError("unable to find parent clip item '" + clip_item_id +   \
                        "' for new leaf item '" + item_id + "' (ignoring)" ) ; \
    else                                                                       \
    { Trace::TraceGui(       "created leaf item '" + item_id + "'") ;          \
      Trace::TraceNoPrefix(  "for clip '"          + clip_id + "'") ;          \
      Trace::TraceNoPrefix(  "leaf '"              + key     + "'") ;          }

  #define DEBUG_TRACE_INIT_STORAGE(clips_store)                                                     \
    int n_masters = clips_store.getNumChildren() ; int n_clips = 0 ;                   \
    for (int master_n = 0 ; master_n < n_masters ; ++master_n)                         \
      n_clips += clips_store.getChild(master_n).getNumChildren() ;                     \
    Trace::TraceGui("creating tree items for '" + clips_store.getType()  + "' - ("   + \
                    String(n_masters) + ") masters (" + String(n_clips)  + ") clips" ) ;

  #define DEBUG_TRACE_STORAGE_CHILD_DATA(a_node)                                          \
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
    DEBUG_TRACE_STORAGE_CHILD_DATA(new_node)                                              \
    Trace::TraceGui     ("new storage node for " + node_role    + "'" + node_id_ + "'") ; \
    Trace::TraceNoPrefix("added to "             + ancestry_msg                       )   ;

  #define DEBUG_TRACE_STORAGE_CHILD_REMOVED                                                     \
    DEBUG_TRACE_STORAGE_CHILD_DATA(deleted_node)                                                \
    String missing_item_msg = (deleted_item == nullptr) ? "deleted item"                :       \
                              (parent_item  == nullptr) ? "parent item of deleted item" :       \
                                                          String::empty                 ;       \
    Trace::TraceGui     ("storage node for "   + node_role        + "'"    + node_id_ + "'") ;  \
    Trace::TraceNoPrefix("deleted from index " + String(prev_idx) + " of " + ancestry_msg  ) ;  \
    if (!missing_item_msg.isEmpty())                                                            \
      Trace::TraceError("unable to find " + missing_item_msg + " '" + item_id + "' (ignoring)") ;


  /* ClipsTableView subclasses */

  #define DEBUG_TRACE_MASTERCLIPSTABLEVIEW                                                       \
    Trace::TraceGui     ("instantiating MasterClipsTableView for item '" + this->itemId + "'") ; \
    Trace::TraceNoPrefix("data: (" + label_text + "|n/a)")                                       ;

  #define DEBUG_TRACE_CLIPCLIPSTABLEVIEW                                                       \
    Trace::TraceGui     ("instantiating ClipClipsTableView for item '" + this->itemId + "'") ; \
    Trace::TraceNoPrefix("data: (" + label_text + "|n/a)")                                     ;

  #define DEBUG_TRACE_LEAFCLIPSTABLEVIEW                                                       \
    Trace::TraceGui     ("instantiating LeafClipsTableView for item '" + this->itemId + "'") ; \
    Trace::TraceNoPrefix("data: (" + key_text + "|" + value_text + ") "              +         \
                         String((is_new_key_dummy     ) ? "placeholder" :                      \
                                (is_immutable_metadata) ? "immutable"   : "mutable"))          ;

  #define DEBUG_TRACE_CLIPVIEW_COMBOBOX_CHANGED                                               \
    String select_id = (comboBoxThatHasChanged == key_select) ? "keySelect" : "(unhandled)" ; \
    Trace::TraceEvent("ClipClipsTableView " + select_id + " clicked")                         ;

  #define DEBUG_TRACE_CLIPVIEW_BTN_CLICKED                                         \
    String button_id = (a_button == load_btn  ) ? "loadButton"   :                 \
                       (a_button == edit_btn  ) ? "editButton"   :                 \
                       (a_button == delete_btn) ? "deleteButton" :                 \
                       (a_button == add_btn   ) ? "addButton"    : "(unhandled)" ; \
    Trace::TraceEvent("ClipClipsTableView " + button_id + " clicked")              ;

  #define DEBUG_TRACE_LEAFVIEW_BTN_CLICKED                                         \
    String button_id = (a_button == edit_btn  ) ? "editButton"   :                 \
                       (a_button == delete_btn) ? "deleteButton" : "(unhandled)" ; \
    Trace::TraceEvent("LeafClipsTableView " + button_id + " clicked")              ;

  #define DEBUG_TRACE_CLIPVIEW_SHOW_EDITOR                                     \
    String clip_id = STRING(this->clipStore.getType()) ;                       \
    Trace::TraceGui("showing editor for ClipClipsTableView '" + clip_id + "'") ;

  #define DEBUG_TRACE_LEAFVIEW_SHOW_EDITOR                                     \
    String clip_id = STRING(this->clipStore.getType()) ;                       \
    Trace::TraceGui("showing editor for ClipClipsTableView '" + clip_id   +    \
                    "' LeafClipsTableView                  '" + this->key + "'") ;

  #define DEBUG_TRACE_CLIPVIEW_REMOVE_CLIP                                  \
    String clip_id = STRING(this->clipStore.getType()) ;                    \
    Trace::TraceGui     ("destroying clip '"        + clip_id      + "'") ; \
    Trace::TraceNoPrefix("via ClipClipsTableView '" + this->itemId + "'")   ;

  #define DEBUG_TRACE_LEAFVIEW_ADD_METADATA                                                 \
    String clip_id = STRING(this->clipStore.getType()) ;                                    \
    if (has_orphaned_placeholder)                                                           \
      Trace::TraceError ("replacing orphaned placeholder property") ;                       \
    Trace::TraceGui     ("adding placeholder property '" + STORE::NEW_METADATA_KEY + "'") ; \
    Trace::TraceNoPrefix("to clip '"                     + clip_id                 + "'") ; \
    Trace::TraceNoPrefix("via LeafClipsTableView '"      + this->itemId            + "'")   ;

  #define DEBUG_TRACE_LEAFVIEW_RESET_METADATA                                          \
    String missing_item_msg = (this_item   == nullptr) ? "this item"                 : \
                              (parent_item == nullptr) ? "parent item of this item " : \
                                                         String::empty ;               \
    String clip_id = STRING(this->clipStore.getType()) ;                               \
    Trace::TraceGui     ("deleting property '"      + this->key    + "'") ;            \
    Trace::TraceNoPrefix("from clip '"              + clip_id      + "'") ;            \
    Trace::TraceNoPrefix("via LeafClipsTableView '" + this->itemId + "'") ;            \
    if (!missing_item_msg.isEmpty())                                                   \
      Trace::TraceError("unable to find " + missing_item_msg + " '" +                  \
                        this->itemId + "' (ignoring)"               )                  ;

  /* ClipsTableItem subclasses */

  #define DEBUG_TRACE_MASTERCLIPSTABLEITEM                                                 \
    bool   is_root_item = this->itemId == STRING(STORE::STORAGE_ID) ;                      \
    String item_class   = (is_root_item) ? "RootClipsTableItem" : "MasterClipsTableItem" ; \
    String data_l       = (is_root_item) ? "n/a" : this->labelTextL ;                      \
    String data_r       = "n/a" ;                                                          \
    Trace::TraceGui     ("adding "   + item_class            + " to ClipsTable:") ;        \
    Trace::TraceNoPrefix("itemId: '" + this->itemId          + "'") ;                      \
    Trace::TraceNoPrefix("data  : (" + data_l + "|" + data_r + ")")                        ;

  #define DEBUG_TRACE_CLIPCLIPSTABLEITEM                               \
    String data_l       = this->labelTextL ;                           \
    String data_r       = "n/a" ;                                      \
    Trace::TraceGui     ("adding ClipClipsTableItem to ClipsTable:") ; \
    Trace::TraceNoPrefix("itemId: '" + this->itemId          + "'") ;  \
    Trace::TraceNoPrefix("data  : (" + data_l + "|" + data_r + ")")    ;

  #define DEBUG_TRACE_LEAFCLIPSTABLEITEM                               \
    String data_l       = this->labelTextL ;                           \
    String data_r       = this->labelTextR ;                           \
    Trace::TraceGui     ("adding LeafClipsTableItem to ClipsTable:") ; \
    Trace::TraceNoPrefix("itemId: '" + this->itemId          + "'") ;  \
    Trace::TraceNoPrefix("key   : '" + this->key             + "'") ;  \
    Trace::TraceNoPrefix("data  : (" + data_l + "|" + data_r + ")")    ;

#else // DEBUG_TRACE

  #define DEBUG_TRACE_NEW_MASTER_ITEM         ;
  #define DEBUG_TRACE_NEW_CLIP_ITEM           ;
  #define DEBUG_TRACE_NEW_LEAF_ITEM           ;
  #define DEBUG_TRACE_CREATE_MASTER_ITEM      ;
  #define DEBUG_TRACE_CREATE_CLIP_ITEM        ;
  #define DEBUG_TRACE_CREATE_LEAF_ITEM        ;
  #define DEBUG_TRACE_INIT_STORAGE(unused)    ;
  #define DEBUG_TRACE_STORAGE_CHILD_ADDED     ;
  #define DEBUG_TRACE_STORAGE_CHILD_REMOVED   ;
  #define DEBUG_TRACE_MASTERCLIPSTABLEVIEW    ;
  #define DEBUG_TRACE_CLIPCLIPSTABLEVIEW      ;
  #define DEBUG_TRACE_LEAFCLIPSTABLEVIEW      ;
  #define DEBUG_TRACE_CLIPVIEW_BTN_CLICKED    ;
  #define DEBUG_TRACE_LEAFVIEW_BTN_CLICKED    ;
  #define DEBUG_TRACE_CLIPVIEW_SHOW_EDITOR    ;
  #define DEBUG_TRACE_LEAFVIEW_SHOW_EDITOR    ;
  #define DEBUG_TRACE_CLIPVIEW_REMOVE_CLIP    ;
  #define DEBUG_TRACE_LEAFVIEW_ADD_METADATA   ;
  #define DEBUG_TRACE_LEAFVIEW_RESET_METADATA ;
  #define DEBUG_TRACE_MASTERCLIPSTABLEITEM    ;
  #define DEBUG_TRACE_CLIPCLIPSTABLEITEM      ;
  #define DEBUG_TRACE_LEAFCLIPSTABLEITEM      ;

#endif // DEBUG_TRACE
