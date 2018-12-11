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

#include "../Constants/StorageConstants.h"

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
    keyLabel->setFont (Font (15.00f, Font::plain));
    keyLabel->setJustificationType (Justification::centredTop);
    keyLabel->setEditable (false, false, false);
    keyLabel->setColour (Label::textColourId, Colours::white);
    keyLabel->setColour (TextEditor::textColourId, Colours::black);
    keyLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    keyLabel->setBounds (8, 32, 128, 16);

    valueLabel.reset (new Label (String(),
                                 TRANS("field data")));
    addAndMakeVisible (valueLabel.get());
    valueLabel->setFont (Font (15.00f, Font::plain));
    valueLabel->setJustificationType (Justification::centredTop);
    valueLabel->setEditable (false, false, false);
    valueLabel->setColour (Label::textColourId, Colours::white);
    valueLabel->setColour (TextEditor::textColourId, Colours::black);
    valueLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    keySelect.reset (new ComboBox (String()));
    addAndMakeVisible (keySelect.get());
    keySelect->setExplicitFocusOrder (4);
    keySelect->setEditableText (true);
    keySelect->setJustificationType (Justification::centredLeft);
    keySelect->setTextWhenNothingSelected (TRANS("(select or enter a name)"));
    keySelect->setTextWhenNoChoicesAvailable (TRANS("(select or enter a name)"));
    keySelect->addListener (this);

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

    keySelect2.reset (new ComboBox (String()));
    addAndMakeVisible (keySelect2.get());
    keySelect2->setExplicitFocusOrder (4);
    keySelect2->setEditableText (true);
    keySelect2->setJustificationType (Justification::centredLeft);
    keySelect2->setTextWhenNothingSelected (TRANS("(select or enter a name)"));
    keySelect2->setTextWhenNoChoicesAvailable (TRANS("(select or enter a name)"));
    keySelect2->addListener (this);

    valueText2.reset (new TextEditor (String()));
    addAndMakeVisible (valueText2.get());
    valueText2->setExplicitFocusOrder (1);
    valueText2->setMultiLine (false);
    valueText2->setReturnKeyStartsNewLine (false);
    valueText2->setReadOnly (false);
    valueText2->setScrollbarsShown (false);
    valueText2->setCaretVisible (true);
    valueText2->setPopupMenuEnabled (false);
    valueText2->setColour (TextEditor::textColourId, Colours::grey);
    valueText2->setColour (TextEditor::backgroundColourId, Colours::black);
    valueText2->setText (String());

    keySelect3.reset (new ComboBox (String()));
    addAndMakeVisible (keySelect3.get());
    keySelect3->setExplicitFocusOrder (4);
    keySelect3->setEditableText (true);
    keySelect3->setJustificationType (Justification::centredLeft);
    keySelect3->setTextWhenNothingSelected (TRANS("(select or enter a name)"));
    keySelect3->setTextWhenNoChoicesAvailable (TRANS("(select or enter a name)"));
    keySelect3->addListener (this);

    valueText3.reset (new TextEditor (String()));
    addAndMakeVisible (valueText3.get());
    valueText3->setExplicitFocusOrder (1);
    valueText3->setMultiLine (false);
    valueText3->setReturnKeyStartsNewLine (false);
    valueText3->setReadOnly (false);
    valueText3->setScrollbarsShown (false);
    valueText3->setCaretVisible (true);
    valueText3->setPopupMenuEnabled (false);
    valueText3->setColour (TextEditor::textColourId, Colours::grey);
    valueText3->setColour (TextEditor::backgroundColourId, Colours::black);
    valueText3->setText (String());

    keySelect4.reset (new ComboBox (String()));
    addAndMakeVisible (keySelect4.get());
    keySelect4->setExplicitFocusOrder (4);
    keySelect4->setEditableText (true);
    keySelect4->setJustificationType (Justification::centredLeft);
    keySelect4->setTextWhenNothingSelected (TRANS("(select or enter a name)"));
    keySelect4->setTextWhenNoChoicesAvailable (TRANS("(select or enter a name)"));
    keySelect4->addListener (this);

    valueText4.reset (new TextEditor (String()));
    addAndMakeVisible (valueText4.get());
    valueText4->setExplicitFocusOrder (1);
    valueText4->setMultiLine (false);
    valueText4->setReturnKeyStartsNewLine (false);
    valueText4->setReadOnly (false);
    valueText4->setScrollbarsShown (false);
    valueText4->setCaretVisible (true);
    valueText4->setPopupMenuEnabled (false);
    valueText4->setColour (TextEditor::textColourId, Colours::grey);
    valueText4->setColour (TextEditor::backgroundColourId, Colours::black);
    valueText4->setText (String());

    keySelect5.reset (new ComboBox (String()));
    addAndMakeVisible (keySelect5.get());
    keySelect5->setExplicitFocusOrder (4);
    keySelect5->setEditableText (true);
    keySelect5->setJustificationType (Justification::centredLeft);
    keySelect5->setTextWhenNothingSelected (TRANS("(select or enter a name)"));
    keySelect5->setTextWhenNoChoicesAvailable (TRANS("(select or enter a name)"));
    keySelect5->addListener (this);

    valueText5.reset (new TextEditor (String()));
    addAndMakeVisible (valueText5.get());
    valueText5->setExplicitFocusOrder (1);
    valueText5->setMultiLine (false);
    valueText5->setReturnKeyStartsNewLine (false);
    valueText5->setReadOnly (false);
    valueText5->setScrollbarsShown (false);
    valueText5->setCaretVisible (true);
    valueText5->setPopupMenuEnabled (false);
    valueText5->setColour (TextEditor::textColourId, Colours::grey);
    valueText5->setColour (TextEditor::backgroundColourId, Colours::black);
    valueText5->setText (String());

    keySelect6.reset (new ComboBox (String()));
    addAndMakeVisible (keySelect6.get());
    keySelect6->setExplicitFocusOrder (4);
    keySelect6->setEditableText (true);
    keySelect6->setJustificationType (Justification::centredLeft);
    keySelect6->setTextWhenNothingSelected (TRANS("(select or enter a name)"));
    keySelect6->setTextWhenNoChoicesAvailable (TRANS("(select or enter a name)"));
    keySelect6->addListener (this);

    valueText6.reset (new TextEditor (String()));
    addAndMakeVisible (valueText6.get());
    valueText6->setExplicitFocusOrder (1);
    valueText6->setMultiLine (false);
    valueText6->setReturnKeyStartsNewLine (false);
    valueText6->setReadOnly (false);
    valueText6->setScrollbarsShown (false);
    valueText6->setCaretVisible (true);
    valueText6->setPopupMenuEnabled (false);
    valueText6->setColour (TextEditor::textColourId, Colours::grey);
    valueText6->setColour (TextEditor::backgroundColourId, Colours::black);
    valueText6->setText (String());

    keySelect7.reset (new ComboBox (String()));
    addAndMakeVisible (keySelect7.get());
    keySelect7->setExplicitFocusOrder (4);
    keySelect7->setEditableText (true);
    keySelect7->setJustificationType (Justification::centredLeft);
    keySelect7->setTextWhenNothingSelected (TRANS("(select or enter a name)"));
    keySelect7->setTextWhenNoChoicesAvailable (TRANS("(select or enter a name)"));
    keySelect7->addListener (this);

    valueText7.reset (new TextEditor (String()));
    addAndMakeVisible (valueText7.get());
    valueText7->setExplicitFocusOrder (1);
    valueText7->setMultiLine (false);
    valueText7->setReturnKeyStartsNewLine (false);
    valueText7->setReadOnly (false);
    valueText7->setScrollbarsShown (false);
    valueText7->setCaretVisible (true);
    valueText7->setPopupMenuEnabled (false);
    valueText7->setColour (TextEditor::textColourId, Colours::grey);
    valueText7->setColour (TextEditor::backgroundColourId, Colours::black);
    valueText7->setText (String());

    keySelect8.reset (new ComboBox (String()));
    addAndMakeVisible (keySelect8.get());
    keySelect8->setExplicitFocusOrder (4);
    keySelect8->setEditableText (true);
    keySelect8->setJustificationType (Justification::centredLeft);
    keySelect8->setTextWhenNothingSelected (TRANS("(select or enter a name)"));
    keySelect8->setTextWhenNoChoicesAvailable (TRANS("(select or enter a name)"));
    keySelect8->addListener (this);

    valueText8.reset (new TextEditor (String()));
    addAndMakeVisible (valueText8.get());
    valueText8->setExplicitFocusOrder (1);
    valueText8->setMultiLine (false);
    valueText8->setReturnKeyStartsNewLine (false);
    valueText8->setReadOnly (false);
    valueText8->setScrollbarsShown (false);
    valueText8->setCaretVisible (true);
    valueText8->setPopupMenuEnabled (false);
    valueText8->setColour (TextEditor::textColourId, Colours::grey);
    valueText8->setColour (TextEditor::backgroundColourId, Colours::black);
    valueText8->setText (String());

    acceptButton.reset (new TextButton (String()));
    addAndMakeVisible (acceptButton.get());
    acceptButton->setExplicitFocusOrder (5);
    acceptButton->setButtonText (TRANS("Accept"));

    cancelButton.reset (new TextButton (String()));
    addAndMakeVisible (cancelButton.get());
    cancelButton->setExplicitFocusOrder (6);
    cancelButton->setButtonText (TRANS("Cancel"));

    clipLabel.reset (new Label (String(),
                                TRANS("Metadata for: ")));
    addAndMakeVisible (clipLabel.get());
    clipLabel->setFont (Font (15.00f, Font::plain));
    clipLabel->setJustificationType (Justification::centred);
    clipLabel->setEditable (false, false, false);
    clipLabel->setColour (TextEditor::textColourId, Colours::black);
    clipLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 200);


    //[Constructor] You can add your own custom stuff here..

  String label_text = TRANS("Metadata for: ") + STRING(clip_store[STORE::LABEL_TEXT_KEY]) ;

  this->clipLabel->setText(label_text , juce::dontSendNotification) ;

    //[/Constructor]
}

ConfigMetadata::~ConfigMetadata()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    keyLabel = nullptr;
    valueLabel = nullptr;
    keySelect = nullptr;
    valueText = nullptr;
    keySelect2 = nullptr;
    valueText2 = nullptr;
    keySelect3 = nullptr;
    valueText3 = nullptr;
    keySelect4 = nullptr;
    valueText4 = nullptr;
    keySelect5 = nullptr;
    valueText5 = nullptr;
    keySelect6 = nullptr;
    valueText6 = nullptr;
    keySelect7 = nullptr;
    valueText7 = nullptr;
    keySelect8 = nullptr;
    valueText8 = nullptr;
    acceptButton = nullptr;
    cancelButton = nullptr;
    clipLabel = nullptr;


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

    valueLabel->setBounds (8 + 128 - -8, 32 + 0, getWidth() - 152, 16 - 0);
    keySelect->setBounds (8 + 0, 32 + 16 - -8, 128 - 0, 16);
    valueText->setBounds ((8 + 128 - -8) + 0, (32 + 16 - -8) + 0, getWidth() - 152, 16 - 0);
    keySelect2->setBounds ((8 + 0) + 0, (32 + 16 - -8) + 16 - -8, 128 - 0, 16);
    valueText2->setBounds ((8 + 128 - -8) + 0, ((32 + 16 - -8) + 16 - -8) + 0, getWidth() - 152, 16 - 0);
    keySelect3->setBounds (8 + 0, ((32 + 16 - -8) + 16 - -8) + 16 - -8, 128 - 0, 16);
    valueText3->setBounds ((8 + 128 - -8) + 0, (((32 + 16 - -8) + 16 - -8) + 16 - -8) + 0, getWidth() - 152, 16 - 0);
    keySelect4->setBounds (8 + 0, (((32 + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8, 128 - 0, 16);
    valueText4->setBounds ((8 + 128 - -8) + 0, ((((32 + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 0, getWidth() - 152, 16 - 0);
    keySelect5->setBounds (8 + 0, ((((32 + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8, 128 - 0, 16);
    valueText5->setBounds ((8 + 128 - -8) + 0, (((((32 + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 0, getWidth() - 152, 16 - 0);
    keySelect6->setBounds (8 + 0, (((((32 + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8, 128 - 0, 16);
    valueText6->setBounds ((8 + 128 - -8) + 0, ((((((32 + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 0, getWidth() - 152, 16 - 0);
    keySelect7->setBounds (8 + 0, ((((((32 + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8, 128 - 0, 16);
    valueText7->setBounds ((8 + 128 - -8) + 0, (((((((32 + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 0, getWidth() - 152, 16 - 0);
    keySelect8->setBounds (8 + 0, (((((((32 + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8, 128 - 0, 16);
    valueText8->setBounds ((8 + 128 - -8) + 0, ((((((((32 + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 16 - -8) + 0, getWidth() - 152, 16 - 0);
    acceptButton->setBounds ((getWidth() / 2) + -4 - 64, getHeight() - 8 - 24, 64, 24);
    cancelButton->setBounds ((getWidth() / 2) + 4, getHeight() - 8 - 24, 64, 24);
    clipLabel->setBounds (8, 8, getWidth() - 16, 16);
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
    else if (comboBoxThatHasChanged == keySelect2.get())
    {
        //[UserComboBoxCode_keySelect2] -- add your combo box handling code here..
        //[/UserComboBoxCode_keySelect2]
    }
    else if (comboBoxThatHasChanged == keySelect3.get())
    {
        //[UserComboBoxCode_keySelect3] -- add your combo box handling code here..
        //[/UserComboBoxCode_keySelect3]
    }
    else if (comboBoxThatHasChanged == keySelect4.get())
    {
        //[UserComboBoxCode_keySelect4] -- add your combo box handling code here..
        //[/UserComboBoxCode_keySelect4]
    }
    else if (comboBoxThatHasChanged == keySelect5.get())
    {
        //[UserComboBoxCode_keySelect5] -- add your combo box handling code here..
        //[/UserComboBoxCode_keySelect5]
    }
    else if (comboBoxThatHasChanged == keySelect6.get())
    {
        //[UserComboBoxCode_keySelect6] -- add your combo box handling code here..
        //[/UserComboBoxCode_keySelect6]
    }
    else if (comboBoxThatHasChanged == keySelect7.get())
    {
        //[UserComboBoxCode_keySelect7] -- add your combo box handling code here..
        //[/UserComboBoxCode_keySelect7]
    }
    else if (comboBoxThatHasChanged == keySelect8.get())
    {
        //[UserComboBoxCode_keySelect8] -- add your combo box handling code here..
        //[/UserComboBoxCode_keySelect8]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void ConfigMetadata::buttonClicked(Button* a_button)
{
  if      (a_button == this->acceptButton.get()) handleAcceptButton() ;
  else if (a_button == this->cancelButton.get()) ;
  else return ;

//   getParentComponent()->removeChild(this) ;
  setVisible(false) ;
}

bool ConfigMetadata::handleAcceptButton()
{
/*
// #define N_CONFIG_METADATA_ENTRIES 8
  StringArray keys ;

  // add new or update existing properties
  for (int kvp_n = 0 ; kvp_n < comboBoxes.size() ; ++kvp_n)
  {
    String key   = this->comboBoxes [kvp_n].value ;
    String value = this->textEditors[kvp_n].value

    if (key.isEmpty() || value.isEmpty()) continue ;

    keys.add(key) ;
    this->clipStore.setProperty(Identifier(key) , value , nullptr) ;
  }
  // prune deleted properties
  for (int key_n = 0 ; key_n < this->clipStore.getNumProperties() ; ++key_n)
  {
    Identifier key = this->clipStore.getPropertyName(key_n) ;

    if (!keys.contains(key) this->clipStore.removeProperty(key , nullptr) ;
  }

//     AudioTagToo::LoadClip(this->clipStore) ;
//     this->clipStore.getParent().removeChild(this->clipStore , nullptr) ;
*/
  return true ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ConfigMetadata" componentName=""
                 parentClasses="public Component, private Button::Listener" constructorParams="ValueTree clip_store"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="600" initialHeight="200">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10.00000000000000000000" fill="solid: ff202020"
               hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <LABEL name="" id="eb57b2d805d2eff8" memberName="keyLabel" virtualName=""
         explicitFocusOrder="0" pos="8 32 128 16" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="field name" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="12"/>
  <LABEL name="" id="9d36c2a259889270" memberName="valueLabel" virtualName=""
         explicitFocusOrder="0" pos="-8R 0 152M 0M" posRelativeX="eb57b2d805d2eff8"
         posRelativeY="eb57b2d805d2eff8" posRelativeH="eb57b2d805d2eff8"
         textCol="ffffffff" edTextCol="ff000000" edBkgCol="0" labelText="field data"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="12"/>
  <COMBOBOX name="" id="7a9c3a4f62832f42" memberName="keySelect" virtualName=""
            explicitFocusOrder="4" pos="0 -8R 0M 16" posRelativeX="eb57b2d805d2eff8"
            posRelativeY="eb57b2d805d2eff8" posRelativeW="eb57b2d805d2eff8"
            editable="1" layout="33" items="" textWhenNonSelected="(select or enter a name)"
            textWhenNoItems="(select or enter a name)"/>
  <TEXTEDITOR name="" id="f721d2f898b8b762" memberName="valueText" virtualName=""
              explicitFocusOrder="1" pos="0 0 152M 0M" posRelativeX="9d36c2a259889270"
              posRelativeY="7a9c3a4f62832f42" posRelativeH="7a9c3a4f62832f42"
              textcol="ff808080" bkgcol="ff000000" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="0" caret="1" popupmenu="0"/>
  <COMBOBOX name="" id="488fa700229fa8bd" memberName="keySelect2" virtualName=""
            explicitFocusOrder="4" pos="0 -8R 0M 16" posRelativeX="7a9c3a4f62832f42"
            posRelativeY="7a9c3a4f62832f42" posRelativeW="eb57b2d805d2eff8"
            editable="1" layout="33" items="" textWhenNonSelected="(select or enter a name)"
            textWhenNoItems="(select or enter a name)"/>
  <TEXTEDITOR name="" id="83fbbe2bd0fb8ae0" memberName="valueText2" virtualName=""
              explicitFocusOrder="1" pos="0 0 152M 0M" posRelativeX="9d36c2a259889270"
              posRelativeY="488fa700229fa8bd" posRelativeH="488fa700229fa8bd"
              textcol="ff808080" bkgcol="ff000000" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="0" caret="1" popupmenu="0"/>
  <COMBOBOX name="" id="df800c19695cf1b1" memberName="keySelect3" virtualName=""
            explicitFocusOrder="4" pos="0 -8R 0M 16" posRelativeX="eb57b2d805d2eff8"
            posRelativeY="488fa700229fa8bd" posRelativeW="eb57b2d805d2eff8"
            editable="1" layout="33" items="" textWhenNonSelected="(select or enter a name)"
            textWhenNoItems="(select or enter a name)"/>
  <TEXTEDITOR name="" id="381b299e3362357f" memberName="valueText3" virtualName=""
              explicitFocusOrder="1" pos="0 0 152M 0M" posRelativeX="9d36c2a259889270"
              posRelativeY="df800c19695cf1b1" posRelativeH="df800c19695cf1b1"
              textcol="ff808080" bkgcol="ff000000" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="0" caret="1" popupmenu="0"/>
  <COMBOBOX name="" id="7422c21053d72765" memberName="keySelect4" virtualName=""
            explicitFocusOrder="4" pos="0 -8R 0M 16" posRelativeX="eb57b2d805d2eff8"
            posRelativeY="df800c19695cf1b1" posRelativeW="eb57b2d805d2eff8"
            editable="1" layout="33" items="" textWhenNonSelected="(select or enter a name)"
            textWhenNoItems="(select or enter a name)"/>
  <TEXTEDITOR name="" id="b5b07810eecdf9ef" memberName="valueText4" virtualName=""
              explicitFocusOrder="1" pos="0 0 152M 0M" posRelativeX="9d36c2a259889270"
              posRelativeY="7422c21053d72765" posRelativeH="7422c21053d72765"
              textcol="ff808080" bkgcol="ff000000" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="0" caret="1" popupmenu="0"/>
  <COMBOBOX name="" id="fa40685be1a7ee3b" memberName="keySelect5" virtualName=""
            explicitFocusOrder="4" pos="0 -8R 0M 16" posRelativeX="eb57b2d805d2eff8"
            posRelativeY="7422c21053d72765" posRelativeW="eb57b2d805d2eff8"
            editable="1" layout="33" items="" textWhenNonSelected="(select or enter a name)"
            textWhenNoItems="(select or enter a name)"/>
  <TEXTEDITOR name="" id="f8df7c3b7a9abcf1" memberName="valueText5" virtualName=""
              explicitFocusOrder="1" pos="0 0 152M 0M" posRelativeX="9d36c2a259889270"
              posRelativeY="fa40685be1a7ee3b" posRelativeH="fa40685be1a7ee3b"
              textcol="ff808080" bkgcol="ff000000" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="0" caret="1" popupmenu="0"/>
  <COMBOBOX name="" id="e397d36e4f1a08b3" memberName="keySelect6" virtualName=""
            explicitFocusOrder="4" pos="0 -8R 0M 16" posRelativeX="eb57b2d805d2eff8"
            posRelativeY="fa40685be1a7ee3b" posRelativeW="eb57b2d805d2eff8"
            editable="1" layout="33" items="" textWhenNonSelected="(select or enter a name)"
            textWhenNoItems="(select or enter a name)"/>
  <TEXTEDITOR name="" id="315b2193bd1a56de" memberName="valueText6" virtualName=""
              explicitFocusOrder="1" pos="0 0 152M 0M" posRelativeX="9d36c2a259889270"
              posRelativeY="e397d36e4f1a08b3" posRelativeH="e397d36e4f1a08b3"
              textcol="ff808080" bkgcol="ff000000" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="0" caret="1" popupmenu="0"/>
  <COMBOBOX name="" id="fb4fbf72bc99bca9" memberName="keySelect7" virtualName=""
            explicitFocusOrder="4" pos="0 -8R 0M 16" posRelativeX="eb57b2d805d2eff8"
            posRelativeY="e397d36e4f1a08b3" posRelativeW="eb57b2d805d2eff8"
            editable="1" layout="33" items="" textWhenNonSelected="(select or enter a name)"
            textWhenNoItems="(select or enter a name)"/>
  <TEXTEDITOR name="" id="54f71216ef868a00" memberName="valueText7" virtualName=""
              explicitFocusOrder="1" pos="0 0 152M 0M" posRelativeX="9d36c2a259889270"
              posRelativeY="fb4fbf72bc99bca9" posRelativeH="fb4fbf72bc99bca9"
              textcol="ff808080" bkgcol="ff000000" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="0" caret="1" popupmenu="0"/>
  <COMBOBOX name="" id="77d91829427c5d9e" memberName="keySelect8" virtualName=""
            explicitFocusOrder="4" pos="0 -8R 0M 16" posRelativeX="eb57b2d805d2eff8"
            posRelativeY="fb4fbf72bc99bca9" posRelativeW="eb57b2d805d2eff8"
            editable="1" layout="33" items="" textWhenNonSelected="(select or enter a name)"
            textWhenNoItems="(select or enter a name)"/>
  <TEXTEDITOR name="" id="8c99d0a16203ad36" memberName="valueText8" virtualName=""
              explicitFocusOrder="1" pos="0 0 152M 0M" posRelativeX="9d36c2a259889270"
              posRelativeY="77d91829427c5d9e" posRelativeH="77d91829427c5d9e"
              textcol="ff808080" bkgcol="ff000000" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="0" caret="1" popupmenu="0"/>
  <TEXTBUTTON name="" id="504a4ad212ccb744" memberName="acceptButton" virtualName=""
              explicitFocusOrder="5" pos="-4Cr 8Rr 64 24" buttonText="Accept"
              connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="" id="4ec3eac10517595b" memberName="cancelButton" virtualName=""
              explicitFocusOrder="6" pos="4C 8Rr 64 24" buttonText="Cancel"
              connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <LABEL name="" id="22cabd5e80ab9659" memberName="clipLabel" virtualName=""
         explicitFocusOrder="0" pos="8 8 16M 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Metadata for: " editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
