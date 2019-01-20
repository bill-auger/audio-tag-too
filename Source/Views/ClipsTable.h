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
  ClipsTable is the TreeViewItem container for the AudioTagToo application.
  It presents two side-by-side trees to allow drag and drop of clips into compilations.
                                                                    //[/Comments]
*/
class ClipsTable  : public Component            ,
                    public DragAndDropContainer
{
public:
    //==============================================================================
    ClipsTable ();
    ~ClipsTable();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

friend class MainContent ;


  // setup
  bool initialize(ValueTree& clips_store , ValueTree& compilations_store) ;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  // model/view helpers
  TreeViewItem* getViewItemFor  (const Identifier& root_store_id) ;
  void          storeItemId     (ValueTree a_store , TreeViewItem* an_item) ;
  TreeViewItem* newMasterItem   (ValueTree& master_store) ;
  TreeViewItem* newClipItem     (ValueTree& clip_store) ;
  TreeViewItem* newLeafItem     (const String&     leaf_id                        ,
                                 const String&     key_text                       ,
                                 const String&     value_text                     ,
                                 const Identifier& key                            ,
                                 ValueTree         clip_store = ValueTree::invalid) ;
  void          createMasterItem(ValueTree& root_store , ValueTree master_store) ;
  void          createClipItem  (ValueTree& root_store , ValueTree clip_store) ;
  void          createLeafItem  (ValueTree& clip_store , const Identifier& key) ;
  void          createItemsTree (ValueTree& root_store) ;
  void          destroyItem     (const String& item_id) ;


  std::unique_ptr<TreeViewItem> clipItems ;
  std::unique_ptr<TreeViewItem> compilationItems ;

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
