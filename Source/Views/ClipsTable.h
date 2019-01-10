/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

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
class ClipsTable  : public Component
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

  std::unique_ptr<TreeViewItem> clipItems ;
  std::unique_ptr<TreeViewItem> compilationItems ;

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
