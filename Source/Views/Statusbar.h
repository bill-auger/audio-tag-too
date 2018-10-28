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
  Statusbar is the bottom statusbar GUI for the AudioTagToo application.
  It does nothing useful yet.
                                                                    //[/Comments]
*/
class Statusbar  : public Component
{
public:
    //==============================================================================
    Statusbar ();
    ~Statusbar();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  void setStatusL(String status_text , Colour text_color = GUI::TEXT_FG_COLOR) ;
  void setStatusC(String status_text , Colour text_color = GUI::TEXT_FG_COLOR) ;
  void setStatusR(String status_text , Colour text_color = GUI::TEXT_FG_COLOR) ;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> statusLLabel;
    std::unique_ptr<Label> statusCLabel;
    std::unique_ptr<Label> statusRLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Statusbar)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
