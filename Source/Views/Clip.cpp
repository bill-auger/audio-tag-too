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
#include "../Constants/StorageConstants.h"
#include "../Controllers/AudioTagToo.h"

//[/Headers]

#include "Clip.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#define  itemLabel label
//[/MiscUserDefs]

//==============================================================================
Clip::Clip (String item_id , String label_text , ValueTree clip_store)
    : itemId(item_id) , labelText(label_text) ,
      masterStore(clip_store.getParent()) ,  clipStore(clip_store)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    label.reset (new Label ("new label",
                            TRANS("label text")));
    addAndMakeVisible (label.get());
    label->setFont (Font (24.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colours::white);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    loadButton.reset (new ImageButton (String()));
    addAndMakeVisible (loadButton.get());

    loadButton->setImages (false, true, false,
                           ImageCache::getFromMemory (BinaryData::mediaplaybackstart_png, BinaryData::mediaplaybackstart_pngSize), 1.000f, Colour (0x00000000),
                           Image(), 1.000f, Colour (0x00000000),
                           Image(), 1.000f, Colour (0x00000000));
    editButton.reset (new ImageButton (String()));
    addAndMakeVisible (editButton.get());

    editButton->setImages (false, true, false,
                           ImageCache::getFromMemory (BinaryData::accessoriestexteditor_png, BinaryData::accessoriestexteditor_pngSize), 1.000f, Colour (0x00000000),
                           Image(), 1.000f, Colour (0x00000000),
                           Image(), 1.000f, Colour (0x00000000));
    deleteButton.reset (new ImageButton (String()));
    addAndMakeVisible (deleteButton.get());

    deleteButton->setImages (false, true, false,
                             ImageCache::getFromMemory (BinaryData::processstop_png, BinaryData::processstop_pngSize), 1.000f, Colour (0x00000000),
                             Image(), 1.000f, Colour (0x00000000),
                             Image(), 1.000f, Colour (0x00000000));

    //[UserPreSize]
    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..

//   Label* item_label = new Label(this->item_id , this->label_text) ;
//   if (this->clipStore.hasProperty(STORE::LABEL_TEXT_KEY))
  if (this->clipStore.isValid())
  {
    Value stored_value = this->clipStore.getPropertyAsValue(STORE::LABEL_TEXT_KEY , nullptr) ;

  this->label->setText(label_text , juce::dontSendNotification) ;
  this->label->setFont(Font((float)(GUI::TREE_ITEM_H - 2) , Font::plain).withTypefaceStyle("Regular")) ;
    this->itemLabel->setEditable(true) ;
    this->itemLabel->getTextValue().referTo(stored_value) ;
    this->loadButton  ->addListener(this) ;
    this->editButton  ->addListener(this) ;
    this->deleteButton->addListener(this) ;
  }
  else
  {
    // ensure metadata leaf items are immutable
    removeChildComponent(this->loadButton  .get()) ;
    removeChildComponent(this->editButton  .get()) ;
    removeChildComponent(this->deleteButton.get()) ;
  }

    //[/Constructor]
}

Clip::~Clip()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label = nullptr;
    loadButton = nullptr;
    editButton = nullptr;
    deleteButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Clip::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Clip::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    label->setBounds (0, 0, getWidth() - 72, 24);
    loadButton->setBounds (((getWidth() - 24) + 0 - 24) + 0 - 24, 0, 24, 24);
    editButton->setBounds ((getWidth() - 24) + 0 - 24, 0, 24, 24);
    deleteButton->setBounds (getWidth() - 24, 0, 24, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void Clip::buttonClicked(Button* a_button)
{
  if      (a_button == this->loadButton  .get()) AudioTagToo::LoadClip(this->clipStore) ;
  else if (a_button == this->editButton  .get()) this->label->showEditor() ;
  else if (a_button == this->deleteButton.get()) this->masterStore.removeChild(this->clipStore , nullptr) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Clip" componentName="" parentClasses="public Component, private Button::Listener"
                 constructorParams="String item_id , String label_text , ValueTree clip_store"
                 variableInitialisers="clipStore(clip_store)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="1"
                 initialHeight="1">
  <BACKGROUND backgroundColour="ff323e44"/>
  <LABEL name="new label" id="53e00129390ce15c" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 0 -145M 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="label text" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="24.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <IMAGEBUTTON name="" id="8137f12729559747" memberName="loadButton" virtualName=""
               explicitFocusOrder="0" pos="0r 0 24 24" posRelativeX="c7460681b30100df"
               buttonText="" connectedEdges="0" needsCallback="0" radioGroupId="0"
               keepProportions="0" resourceNormal="BinaryData::mediaplaybackstart_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="1.00000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
  <IMAGEBUTTON name="" id="c7460681b30100df" memberName="editButton" virtualName=""
               explicitFocusOrder="0" pos="0r 0 24 24" posRelativeX="5519a8f967bbfc3e"
               buttonText="" connectedEdges="0" needsCallback="0" radioGroupId="0"
               keepProportions="0" resourceNormal="BinaryData::accessoriestexteditor_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="1.00000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
  <IMAGEBUTTON name="" id="5519a8f967bbfc3e" memberName="deleteButton" virtualName=""
               explicitFocusOrder="0" pos="-217Rr 0 24 24" buttonText="" connectedEdges="0"
               needsCallback="0" radioGroupId="0" keepProportions="0" resourceNormal="BinaryData::processstop_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="1.00000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
