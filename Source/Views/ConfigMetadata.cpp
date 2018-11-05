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
//[/Headers]

#include "ConfigMetadata.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConfigMetadata::ConfigMetadata (ValueTree clip_store)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    keyLabel.reset (new Label (String(),
                               TRANS("field name")));
    addAndMakeVisible (keyLabel.get());
    keyLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    keyLabel->setJustificationType (Justification::centredTop);
    keyLabel->setEditable (false, false, false);
    keyLabel->setColour (Label::textColourId, Colours::white);
    keyLabel->setColour (TextEditor::textColourId, Colours::black);
    keyLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    keySelect.reset (new ComboBox (String()));
    addAndMakeVisible (keySelect.get());
    keySelect->setExplicitFocusOrder (4);
    keySelect->setEditableText (true);
    keySelect->setJustificationType (Justification::centredLeft);
    keySelect->setTextWhenNothingSelected (TRANS("(select or enter a name)"));
    keySelect->setTextWhenNoChoicesAvailable (TRANS("(select or enter a name)"));
    keySelect->addListener (this);

    valueLabel.reset (new Label (String(),
                                 TRANS("field data")));
    addAndMakeVisible (valueLabel.get());
    valueLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    valueLabel->setJustificationType (Justification::centredTop);
    valueLabel->setEditable (false, false, false);
    valueLabel->setColour (Label::textColourId, Colours::white);
    valueLabel->setColour (TextEditor::textColourId, Colours::black);
    valueLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    valueText.reset (new TextEditor (String()));
    addAndMakeVisible (valueText.get());
    valueText->setExplicitFocusOrder (1);
    valueText->setMultiLine (false);
    valueText->setReturnKeyStartsNewLine (false);
    valueText->setReadOnly (false);
    valueText->setScrollbarsShown (false);
    valueText->setCaretVisible (true);
    valueText->setPopupMenuEnabled (false);
    valueText->setColour (TextEditor::textColourId, Colours::grey);
    valueText->setColour (TextEditor::backgroundColourId, Colours::black);
    valueText->setText (String());

    acceptButton.reset (new TextButton (String()));
    addAndMakeVisible (acceptButton.get());
    acceptButton->setExplicitFocusOrder (5);
    acceptButton->setButtonText (TRANS("Accept"));

    cancelButton.reset (new TextButton (String()));
    addAndMakeVisible (cancelButton.get());
    cancelButton->setExplicitFocusOrder (6);
    cancelButton->setButtonText (TRANS("cancel"));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (200, 200);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ConfigMetadata::~ConfigMetadata()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    keyLabel = nullptr;
    keySelect = nullptr;
    valueLabel = nullptr;
    valueText = nullptr;
    acceptButton = nullptr;
    cancelButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ConfigMetadata::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = 0.0f, y = 0.0f, width = static_cast<float> (getWidth() - 0), height = static_cast<float> (getHeight() - 0);
        Colour fillColour = Colour (0xff202020);
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

void ConfigMetadata::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    keyLabel->setBounds ((getWidth() / 2) - ((getWidth() - 16) / 2), 8, getWidth() - 16, 16);
    keySelect->setBounds ((getWidth() / 2) - ((getWidth() - 16) / 2), 8 + 16 - -8, getWidth() - 16, 16);
    valueLabel->setBounds ((getWidth() / 2) - ((getWidth() - 16) / 2), (8 + 16 - -8) + 16 - -16, getWidth() - 16, 16);
    valueText->setBounds ((getWidth() / 2) - ((getWidth() - 16) / 2), ((8 + 16 - -8) + 16 - -16) + 16 - -8, getWidth() - 16, getHeight() - 128);
    acceptButton->setBounds ((getWidth() / 2) + -4 - 64, getHeight() - 8 - 24, 64, 24);
    cancelButton->setBounds ((getWidth() / 2) + 4, getHeight() - 8 - 24, 64, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConfigMetadata::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == keySelect.get())
    {
        //[UserComboBoxCode_keySelect] -- add your combo box handling code here..
        //[/UserComboBoxCode_keySelect]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ConfigMetadata" componentName=""
                 parentClasses="public Component, public Button::Listener" constructorParams="ValueTree clip_store"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="200" initialHeight="200">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10.00000000000000000000" fill="solid: ff202020"
               hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <LABEL name="" id="eb57b2d805d2eff8" memberName="keyLabel" virtualName=""
         explicitFocusOrder="0" pos="0Cc 8 16M 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="field name" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="12"/>
  <COMBOBOX name="" id="7a9c3a4f62832f42" memberName="keySelect" virtualName=""
            explicitFocusOrder="4" pos="0Cc -8R 16M 16" posRelativeY="eb57b2d805d2eff8"
            editable="1" layout="33" items="" textWhenNonSelected="(select or enter a name)"
            textWhenNoItems="(select or enter a name)"/>
  <LABEL name="" id="9d36c2a259889270" memberName="valueLabel" virtualName=""
         explicitFocusOrder="0" pos="0Cc -16R 16M 16" posRelativeY="7a9c3a4f62832f42"
         textCol="ffffffff" edTextCol="ff000000" edBkgCol="0" labelText="field data"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="12"/>
  <TEXTEDITOR name="" id="f721d2f898b8b762" memberName="valueText" virtualName=""
              explicitFocusOrder="1" pos="0Cc -8R 16M 128M" posRelativeY="9d36c2a259889270"
              textcol="ff808080" bkgcol="ff000000" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="0" caret="1" popupmenu="0"/>
  <TEXTBUTTON name="" id="504a4ad212ccb744" memberName="acceptButton" virtualName=""
              explicitFocusOrder="5" pos="-4Cr 8Rr 64 24" buttonText="Accept"
              connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="" id="4ec3eac10517595b" memberName="cancelButton" virtualName=""
              explicitFocusOrder="6" pos="4C 8Rr 64 24" buttonText="cancel"
              connectedEdges="0" needsCallback="0" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
