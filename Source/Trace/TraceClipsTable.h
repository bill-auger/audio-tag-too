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

 /* ClipsTable */

  #define DEBUG_TRACE_INIT_GUI                                                              \
    if      (AudioTagToo::GetIsInitialized()) Trace::TraceGui("GUI already initialized") ;  \
    else if (should_initialize              ) Trace::TraceGui("GUI initialized") ;          \
    else                                      Trace::TraceError("failed to initialize GUI") ;

  #define DEBUG_TRACE_CREATE_ITEMS_TREE(clips_store)                                   \
    int n_masters = clips_store.getNumChildren() ; int n_clips = 0 ;                   \
    for (int master_n = 0 ; master_n < n_masters ; ++master_n)                         \
      n_clips += clips_store.getChild(master_n).getNumChildren() ;                     \
    Trace::TraceGui("creating tree items for '" + clips_store.getType()  + "' - ("   + \
                    String(n_masters) + ") masters (" + String(n_clips)  + ") clips" ) ;

  #define DEBUG_TRACE_NEW_MASTER_ITEM                                      \
    String item_id = master_item->getItemIdentifierString() ;              \
    Trace::TraceGui     ("created new master item '" + master_id  + "'") ; \
    Trace::TraceNoPrefix("itemId: '"                 + item_id    + "'") ; \
    Trace::TraceNoPrefix("data  : ("                 + label_text + "|)")  ;

  #define DEBUG_TRACE_NEW_CLIP_ITEM                                                             \
    String clip_item_id = clip_item  ->getItemIdentifierString() ;                              \
    Trace::TraceGui     ("created new clip item '" + clip_id                           + "'") ; \
    Trace::TraceNoPrefix("itemId: '" + clip_item_id                                    + "'") ; \
    Trace::TraceNoPrefix("data  : (" + clip_label_text     + "|n/a"                    + ")") ; \
    Trace::TraceNoPrefix("        (" + file_label_text     + "|" + file_value_text     + ")") ; \
    Trace::TraceNoPrefix("        (" + begin_label_text    + "|" + begin_value_text    + ")") ; \
    Trace::TraceNoPrefix("        (" + end_label_text      + "|" + end_value_text      + ")") ; \
    Trace::TraceNoPrefix("        (" + duration_label_text + "|" + duration_value_text + ")")   ;

  #define DEBUG_TRACE_NEW_LEAF_ITEM                                         \
    String item_id = leaf_item->getItemIdentifierString() ;                 \
    Trace::TraceGui     ("created new leaf item '"    + leaf_id    + "'") ; \
    Trace::TraceNoPrefix("itemId: '"                  + item_id    + "'") ; \
    Trace::TraceNoPrefix("data  : (" + key_text + "|" + value_text + ")")   ;

  #define DEBUG_TRACE_CREATE_MASTER_ITEM                               \
    String master_id = STRING(master_store.getType()) ;                \
    String root_id   = STRING(root_store  .getType()) ;                \
    String filename  = STRING(master_store[STORE::FILENAME_KEY]) ;     \
    String masteridx = String(root_store.indexOf(master_store)) ;      \
    Trace::TraceGui(     "creating master item '" + master_id + "'") ; \
    Trace::TraceNoPrefix("for source '"           + filename  + "'") ; \
    Trace::TraceNoPrefix("at index "              + masteridx +        \
                         " of root store '"       + root_id   + "'")   ;

  #define DEBUG_TRACE_CREATE_CLIP_ITEM                                               \
    String filename               = STRING(master_store[STORE::FILENAME_KEY]) ;      \
    String master_id              = STRING(master_store.getType()) ;                 \
    String root_id                = STRING(root_store  .getType()) ;                 \
    String clip_id                = STRING(clip_store  .getType()) ;                 \
    bool   does_master_item_exist = master_item != nullptr ;                         \
    String existing_master_msg    = (does_master_item_exist) ? "existing" : "new" ;  \
    if (does_master_item_exist)                                                      \
    { Trace::TraceGui     ("creating master item '" + filename            + "'") ;   \
      Trace::TraceNoPrefix("for source '"           + master_id           +          \
                           "' at index "            + String(master_idx)  +          \
                           " of root store '"       + root_id             + "'") ; } \
    Trace::TraceGui       ("creating clip item '"   + clip_id             + "'") ;   \
    Trace::TraceNoPrefix  ("at index "              + String(clip_idx)    +          \
                           " of "                   + existing_master_msg +          \
                           " master store '"        + master_id           + "'") ;   \
    Trace::TraceNoPrefix  ("at index "              + String(master_idx)  +          \
                           " of root store '"       + root_id + "'"       ) ;        \
    DEBUG_TRACE_DUMP_ITEMS_TREE(root_item , STRING(root_store.getType()))            ;

  #define DEBUG_TRACE_CREATE_LEAF_ITEM                                         \
    if (clip_item == nullptr)                                                  \
      Trace::TraceError("unable to find parent clip item '" + clip_item_id +   \
                        "' for new leaf item '" + leaf_id + "' (ignoring)" ) ; \
    else                                                                       \
    { Trace::TraceGui     ("creating leaf item '" + leaf_id + "'") ;           \
      Trace::TraceNoPrefix("for clip '"           + clip_id + "'") ;           \
      Trace::TraceNoPrefix("leaf '"               + key     + "'") ;           }

  #define DEBUG_TRACE_DESTROY_ITEM                                                              \
    String missing_item_msg = (deleted_item == nullptr) ? "deleted item"                :       \
                              (parent_item  == nullptr) ? "parent item of deleted item" :       \
                                                          String::empty                 ;       \
    if (missing_item_msg.isEmpty())                                                             \
      Trace::TraceGui("destroying view item '" + item_id + "'") ;                               \
    else                                                                                        \
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
    String select_id   = (a_combobox == key_select) ? "keySelect" : "(unhandled)" ;           \
    String option_idx  = String(key_select->getSelectedItemIndex()) ;                         \
    String option_id   = String(key_select->getSelectedId()) ;                                \
    String option_text = String(key_select->getText()) ;                                      \
    Trace::TraceEvent("ClipClipsTableView " + select_id + " selection changed: " +            \
                      " option[" + option_idx + "] '" + option_id + "::" + option_text + "'") ;

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

  #define DEBUG_TRACE_POPULATE_KEYSELECT                                                   \
    Trace::TraceGui("populating keySelect with (" + String(n_keys) + ") known properties") ;

  #define DEBUG_TRACE_HANDLE_COMBOBOX                                                   \
    String valid_key_msg   = "adding new property '"    + key_text + "' to store" ;     \
    String invalid_key_msg = "invalid property entry '" + key_text + "' - (ignoring)" ; \
    Trace::TraceGui((is_acceptable_key) ? valid_key_msg : invalid_key_msg)              ;

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

  #define DEBUG_TRACE_LEAFVIEW_ADD_METADATA                                                  \
    bool   has_orphaned_placeholder = this->clipStore.hasProperty(STORE::NEW_METADATA_KEY) ; \
    String clip_id                  = STRING(this->clipStore.getType()) ;                    \
    if (has_orphaned_placeholder)                                                            \
      Trace::TraceError ("replacing orphaned placeholder property") ;                        \
    Trace::TraceGui     ("adding placeholder property '" + STORE::NEW_METADATA_KEY + "'") ;  \
    Trace::TraceNoPrefix("to clip '"                     + clip_id                 + "'") ;  \
    Trace::TraceNoPrefix("via LeafClipsTableView '"      + this->itemId            + "'")    ;

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

  #define DEBUG_TRACE_INIT_GUI                  ;
  #define DEBUG_TRACE_CREATE_ITEMS_TREE(unused) ;
  #define DEBUG_TRACE_NEW_MASTER_ITEM           ;
  #define DEBUG_TRACE_NEW_CLIP_ITEM             ;
  #define DEBUG_TRACE_NEW_LEAF_ITEM             ;
  #define DEBUG_TRACE_CREATE_MASTER_ITEM        ;
  #define DEBUG_TRACE_CREATE_CLIP_ITEM          ;
  #define DEBUG_TRACE_CREATE_LEAF_ITEM          ;
  #define DEBUG_TRACE_DESTROY_ITEM              ;
  #define DEBUG_TRACE_MASTERCLIPSTABLEVIEW      ;
  #define DEBUG_TRACE_CLIPCLIPSTABLEVIEW        ;
  #define DEBUG_TRACE_LEAFCLIPSTABLEVIEW        ;
  #define DEBUG_TRACE_CLIPVIEW_BTN_CLICKED      ;
  #define DEBUG_TRACE_LEAFVIEW_BTN_CLICKED      ;
  #define DEBUG_TRACE_POPULATE_KEYSELECT        ;
  #define DEBUG_TRACE_HANDLE_COMBOBOX           ;
  #define DEBUG_TRACE_CLIPVIEW_SHOW_EDITOR      ;
  #define DEBUG_TRACE_LEAFVIEW_SHOW_EDITOR      ;
  #define DEBUG_TRACE_CLIPVIEW_REMOVE_CLIP      ;
  #define DEBUG_TRACE_LEAFVIEW_ADD_METADATA     ;
  #define DEBUG_TRACE_LEAFVIEW_RESET_METADATA   ;
  #define DEBUG_TRACE_MASTERCLIPSTABLEITEM      ;
  #define DEBUG_TRACE_CLIPCLIPSTABLEITEM        ;
  #define DEBUG_TRACE_LEAFCLIPSTABLEITEM        ;

#endif // DEBUG_TRACE
