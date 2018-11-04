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
  Clip is the TreeViewItem component for the AudioTagToo application.
  It represents individual audio segment clip entries with buttons
  to load the clip into the GUI, edit it's friendly name label, and destroy the clip entry.
                                                                    //[/Comments]
*/
class Clip  : public Component,
              private Button::Listener
{
public:
    //==============================================================================
    Clip (String item_id , String label_text , ValueTree clip_store = ValueTree::invalid);
    ~Clip();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  String    itemId ;
  String    labelText ;
  ValueTree masterStore ;
  ValueTree clipStore ;


  void buttonClicked(Button* a_button) ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> label;
    std::unique_ptr<ImageButton> loadButton;
    std::unique_ptr<ImageButton> editButton;
    std::unique_ptr<ImageButton> deleteButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Clip)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
