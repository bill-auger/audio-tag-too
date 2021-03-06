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

//[Headers]     -- You can add your own extra header files here --

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Constants/GuiConstants.h"
#include "../Constants/StorageConstants.h"


class Clip ;

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  ClipsTable is the TreeViewItem container for the AudioTagToo application.
  It presents two side-by-side trees to allow drag and drop of clips into compilations.
                                                                    //[/Comments]
*/
class ClipsTable  : public Component,
public DragAndDropContainer,
                    public ValueTree::Listener
{
public:
    //==============================================================================
    ClipsTable ();
    ~ClipsTable();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  // setup
  void initialize(ValueTree& clips_store , ValueTree& compilations_store) ;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  ValueTree                     clipsStore ;
  ValueTree                     compilationsStore ;
  std::unique_ptr<TreeViewItem> clipItems ;
  std::unique_ptr<TreeViewItem> compilationItems ;

  // model helpers
  TreeViewItem* getViewItemFor  (ValueTree root_store) ;
  TreeViewItem* newMasterItem   (ValueTree master_node) ;
  TreeViewItem* newClipItem     (ValueTree clip_node) ;
  void          createMasterItem(ValueTree root_store , ValueTree master_node) ;
  void          createClipItem  (ValueTree root_store , ValueTree clip_node) ;
  void          createItemsTree (ValueTree root_store) ;

  // event handlers
  void valueTreeChildAdded       (ValueTree& parent_node , ValueTree& new_node)                    override ;
  void valueTreeChildRemoved     (ValueTree& parent_node , ValueTree& deleted_node , int prev_idx) override ;
  void valueTreeChildOrderChanged(ValueTree& parent_node , int        prev_idx     , int curr_idx) override ;

  // unhandled ValueTree::Listener events
  void valueTreeRedirected     (ValueTree&)                     override { }
  void valueTreePropertyChanged(ValueTree& , const Identifier&) override { }
  void valueTreeParentChanged  (ValueTree&)                     override { }


  class ClipsTreeView : public TreeView
  {
  public:

    ClipsTreeView(const String &component_name = String()) : is_drag_item_hovering(false) {}

    void paint(Graphics& g) override ;


  private:

    bool is_drag_item_hovering ;


    // DragAndDropTarget implementation
    bool isInterestedInDragSource(const DragAndDropTarget::SourceDetails& dragSourceDetails) override ;
    void itemDragEnter           (const DragAndDropTarget::SourceDetails& dragSourceDetails) override ;
    void itemDragMove            (const DragAndDropTarget::SourceDetails& dragSourceDetails) override ;
    void itemDragExit            (const DragAndDropTarget::SourceDetails& dragSourceDetails) override ;
    void itemDropped             (const DragAndDropTarget::SourceDetails& dragSourceDetails) override ;
  } ;


  class ClipItem : public TreeViewItem
  {
  public:

    ClipItem(String item_id , String label_text , ValueTree store = ValueTree::invalid) ;


  private:

    // TreeViewItem implementation
    String     getUniqueName       () const override ;
    bool       mightContainSubItems()       override ;
    int        getItemHeight       () const override ;
    Component* createItemComponent ()       override ;

    // TreeViewItem drag and drop implementation
    var  getDragSourceDescription()                                                                    override ;
    bool isInterestedInDragSource(const DragAndDropTarget::SourceDetails& dragSourceDetails          ) override ;
    void itemDropped             (const DragAndDropTarget::SourceDetails& dragSourceDetails , int idx) override ;


//   private:

    String                item_id ;
    String                label_text ;
    ValueTree             store ;
bool is_drag_item_hovering ;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ClipItem)
  } ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<GroupComponent> compilationsGroup;
    std::unique_ptr<GroupComponent> clipsGroup;
    std::unique_ptr<TreeView> clipsTreeview;
    std::unique_ptr<TreeView> compilationsTreeview;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ClipsTable)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
