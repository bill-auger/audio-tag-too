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

//[Headers] You can add your own extra header files here...

#include "../Constants/GuiConstants.h"

//[/Headers]

#include "Statusbar.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Statusbar::Statusbar ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    statusLLabel.reset (new Label (String(),
                                   String()));
    addAndMakeVisible (statusLLabel.get());
    statusLLabel->setExplicitFocusOrder (1);
    statusLLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    statusLLabel->setJustificationType (Justification::centred);
    statusLLabel->setEditable (false, false, false);
    statusLLabel->setColour (Label::backgroundColourId, Colour (0x00000000));
    statusLLabel->setColour (Label::textColourId, Colours::grey);
    statusLLabel->setColour (Label::outlineColourId, Colour (0x00000000));
    statusLLabel->setColour (TextEditor::textColourId, Colours::black);
    statusLLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    statusLLabel->setBounds (16, 12, 142, 16);

    statusCLabel.reset (new Label (String(),
                                   String()));
    addAndMakeVisible (statusCLabel.get());
    statusCLabel->setExplicitFocusOrder (2);
    statusCLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    statusCLabel->setJustificationType (Justification::centred);
    statusCLabel->setEditable (false, false, false);
    statusCLabel->setColour (Label::backgroundColourId, Colour (0x00000000));
    statusCLabel->setColour (Label::textColourId, Colours::grey);
    statusCLabel->setColour (Label::outlineColourId, Colour (0x00000000));
    statusCLabel->setColour (TextEditor::textColourId, Colours::black);
    statusCLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    statusRLabel.reset (new Label (String(),
                                   String()));
    addAndMakeVisible (statusRLabel.get());
    statusRLabel->setExplicitFocusOrder (3);
    statusRLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    statusRLabel->setJustificationType (Justification::centred);
    statusRLabel->setEditable (false, false, false);
    statusRLabel->setColour (Label::backgroundColourId, Colour (0x00000000));
    statusRLabel->setColour (Label::textColourId, Colours::grey);
    statusRLabel->setColour (Label::outlineColourId, Colour (0x00000000));
    statusRLabel->setColour (TextEditor::textColourId, Colours::black);
    statusRLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..

  this->statusLLabel->setColour(Label::textColourId , GUI::HEAD_COLOR  ) ; setStatusL(String::empty) ;
  this->statusCLabel->setColour(Label::textColourId , GUI::CURSOR_COLOR) ; setStatusC(String::empty) ;
  this->statusRLabel->setColour(Label::textColourId , GUI::TAIL_COLOR  ) ; setStatusR(String::empty) ;

    //[/Constructor]
}

Statusbar::~Statusbar()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    statusLLabel = nullptr;
    statusCLabel = nullptr;
    statusRLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Statusbar::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = 0.0f, y = 0.0f, width = static_cast<float> (getWidth() - 0), height = static_cast<float> (getHeight() - 0);
        Colour fillColour = Colour (0xff181818);
        Colour strokeColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 1.000f);
    }

    {
        float x = static_cast<float> ((getWidth() / 2) - ((getWidth() - 352) / 2)), y = 8.0f, width = static_cast<float> (getWidth() - 352), height = 24.0f;
        Colour fillColour = Colours::black;
        Colour strokeColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 1.000f);
    }

    {
        float x = static_cast<float> (getWidth() - 8 - 160), y = 8.0f, width = 160.0f, height = 24.0f;
        Colour fillColour = Colours::black;
        Colour strokeColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 1.000f);
    }

    {
        float x = 8.0f, y = 8.0f, width = 160.0f, height = 24.0f;
        Colour fillColour = Colours::black;
        Colour strokeColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 1.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Statusbar::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    statusCLabel->setBounds ((getWidth() / 2) - ((getWidth() - 370) / 2), 12, getWidth() - 370, 16);
    statusRLabel->setBounds (getWidth() - 16 - 142, 12, 142, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void Statusbar::setStatusL(String status_text , Colour text_color)
{
  this->statusLLabel ->setText(status_text , juce::dontSendNotification) ;
  this->statusLLabel->setColour(Label::textColourId , text_color) ;
}

void Statusbar::setStatusC(String status_text , Colour text_color)
{
  this->statusCLabel->setText(status_text , juce::dontSendNotification) ;
  this->statusCLabel->setColour(Label::textColourId , text_color) ;
}

void Statusbar::setStatusR(String status_text , Colour text_color)
{
  this->statusRLabel ->setText(status_text , juce::dontSendNotification) ;
  this->statusRLabel->setColour(Label::textColourId , text_color) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Statusbar" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1" initialHeight="1">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10.00000000000000000000" fill="solid: ff181818"
               hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <ROUNDRECT pos="0Cc 8 352M 24" cornerSize="10.00000000000000000000" fill="solid: ff000000"
               hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <ROUNDRECT pos="8Rr 8 160 24" cornerSize="10.00000000000000000000" fill="solid: ff000000"
               hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <ROUNDRECT pos="8 8 160 24" cornerSize="10.00000000000000000000" fill="solid: ff000000"
               hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <LABEL name="" id="2b89e84fd708c8e0" memberName="statusLLabel" virtualName=""
         explicitFocusOrder="1" pos="16 12 142 16" bkgCol="0" textCol="ff808080"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText=""
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default monospaced font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="4acd1cc773c3be28" memberName="statusCLabel" virtualName=""
         explicitFocusOrder="2" pos="-0.5Cc 12 370M 16" bkgCol="0" textCol="ff808080"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText=""
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default monospaced font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="d9ab2c99c74ba401" memberName="statusRLabel" virtualName=""
         explicitFocusOrder="3" pos="16Rr 12 142 16" bkgCol="0" textCol="ff808080"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText=""
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default monospaced font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
