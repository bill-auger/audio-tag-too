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

//[Headers]     -- You can add your own extra header files here --

#include "../../JuceLibraryCode/JuceHeader.h"

#include "../Constants/StorageConstants.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ClipsTable  : public Component,
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
  TreeViewItem* getViewItemFor  (ValueTree& root_store) ;
  TreeViewItem* newMasterItem   (ValueTree& master_node) ;
  TreeViewItem* newClipItem     (ValueTree& clip_node) ;
  TreeViewItem* newLeafItem     (ValueTree& clip_node , const Identifier& key) ;
  void          createMasterItem(ValueTree& root_store , ValueTree master_node) ;
  void          createClipItem  (ValueTree& root_store , ValueTree clip_node) ;
  void          createLeafItem  (ValueTree clip_node , const Identifier& key) ;
  void          createItemsTree (ValueTree& root_store) ;

  // event handlers
  void valueTreeChildAdded       (ValueTree& parent_node , ValueTree& new_node)                    override ;
  void valueTreeChildOrderChanged(ValueTree& parent_node , int        prev_idx     , int curr_idx) override ;
  void valueTreeChildRemoved     (ValueTree& parent_node , ValueTree& deleted_node , int prev_idx) override ;
  void valueTreePropertyChanged  (ValueTree& changed_node , const Identifier& key)                 override ;

  // unhandled ValueTree::Listener events
  void valueTreeParentChanged(ValueTree& /*reparented_node*/) override { }
  void valueTreeRedirected   (ValueTree& /*target_node*/) override { }

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
