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

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  ClipsTableItem is the TreeViewItem component for the AudioTagToo application.
  This is an abstract class with three implementations:
    MasterClipsTableItem, ClipClipsTableItem, and LeafClipsTableItem
                                                                    //[/Comments]
*/
class ClipsTableItem  : public Component,
                        protected Button::Listener,
                        protected Label::Listener
{
public:
    //==============================================================================
    ClipsTableItem (String item_id , String key_text , String value_text , ValueTree clip_store);
    ~ClipsTableItem();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

protected:

  String    itemId ;
  ValueTree clipStore ;


  // event handlers
  void buttonClicked   (Button* a_button) override ;
  void labelTextChanged(Label* a_label)   override ;

  // helpers
  virtual void showEditor(void) = 0 ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> keyLabel;
    std::unique_ptr<Label> valueLabel;
    std::unique_ptr<ImageButton> loadButton;
    std::unique_ptr<ImageButton> editButton;
    std::unique_ptr<ImageButton> deleteButton;
    std::unique_ptr<ImageButton> addMetadataButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ClipsTableItem)
};

//[EndFile] You can add extra defines here...

/**
                                                                    //[Comments]
  MasterClipsTableItem is a TreeViewItem component for the AudioTagToo application.
  It represents a source audio file from which clips are created.
  It is always a top-level (hidden) root item containing a MasterClipsTableItem or
  that top-level (visible) item containing any numbre of ClipClipsTableItems
  and their respective LeafClipsTableItems.
                                                                    //[/Comments]
*/
class MasterClipsTableItem : public ClipsTableItem
{
public:

    MasterClipsTableItem(String item_id , String key_text) ;


private:

  // helpers
  void showEditor(void) override ;
} ;


/**
                                                                    //[Comments]
  ClipClipsTableItem is a TreeViewItem component for the AudioTagToo application.
  It represents individual audio segment clip entries with buttons
  to load the clip into the GUI, edit it's friendly name label, add and edit metedata,
  and destroy the clip entry.
  It is always a child of a top-level (visible) MasterClipsTableItem item and contains
  LeafClipsTableItems for the associated metadata.
                                                                    //[/Comments]
*/
class ClipClipsTableItem : public ClipsTableItem
{
public:

    ClipClipsTableItem(String item_id , String key_text , ValueTree clip_store) ;


private:

  // helpers
  void showEditor(void) override ;
} ;


/**
                                                                    //[Comments]
  LeafClipsTableItem is a TreeViewItem component for the AudioTagToo application.
  It represents individual metadata entries with buttons
  to edit the metedata value label and destroy the metedata entry.
  This is currently the default ClipItem if the constructor arguments are mis-configured.
  It is always a bottom-level (visible) child item of a ClipClipsTableItem.
                                                                    //[/Comments]
*/
class LeafClipsTableItem : public ClipsTableItem
{
public:

    LeafClipsTableItem(String item_id , String key_text , String value_text) ;


private:

  // helpers
  void showEditor(void) override ;
} ;

//[/EndFile]
