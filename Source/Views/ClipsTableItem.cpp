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
#include "../Trace/Trace.h"

//[/Headers]

#include "ClipsTableItem.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ClipsTableItem::ClipsTableItem (String item_id , String key_text , String value_text , ValueTree clip_store)
    : itemId(item_id) , clipStore(clip_store)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    keyLabel.reset (new Label (String(),
                               TRANS("key :")));
    addAndMakeVisible (keyLabel.get());
    keyLabel->setFont (Font (24.00f, Font::plain));
    keyLabel->setJustificationType (Justification::centredLeft);
    keyLabel->setEditable (false, false, false);
    keyLabel->setColour (Label::textColourId, Colours::white);
    keyLabel->setColour (TextEditor::textColourId, Colours::black);
    keyLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    keyLabel->setBounds (0, 0, 128, 24);

    valueLabel.reset (new Label (String(),
                                 TRANS("value")));
    addAndMakeVisible (valueLabel.get());
    valueLabel->setFont (Font (24.00f, Font::plain));
    valueLabel->setJustificationType (Justification::centredLeft);
    valueLabel->setEditable (false, false, false);
    valueLabel->setColour (Label::textColourId, Colours::white);
    valueLabel->setColour (TextEditor::textColourId, Colours::black);
    valueLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

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
    addMetadataButton.reset (new ImageButton (String()));
    addAndMakeVisible (addMetadataButton.get());

    addMetadataButton->setImages (false, true, false,
                                  ImageCache::getFromMemory (BinaryData::processstop_png, BinaryData::processstop_pngSize), 1.000f, Colour (0x00000000),
                                  Image(), 1.000f, Colour (0x00000000),
                                  Image(), 1.000f, Colour (0x00000000));

    //[UserPreSize]
    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..

  this->keyLabel  ->setText(key_text   , juce::dontSendNotification) ;
  this->valueLabel->setText(value_text , juce::dontSendNotification) ;
  this->keyLabel  ->setFont(Font((float)(GUI::TREE_ITEM_H - 2) , Font::plain).withTypefaceStyle("Regular")) ;
  this->valueLabel->setFont(Font((float)(GUI::TREE_ITEM_H - 2) , Font::plain).withTypefaceStyle("Regular")) ;
//   GUI::ConfigureTextEditor(keyLabel  ->getTextEditor()       , text_listener      ,
//                            GUI::MAX_KEY_TEXTEDITOR_N_CHARS   , APP::VALID_ID_CHARS) ;
//   GUI::ConfigureTextEditor(valueLabel->getTextEditor()       , nullptr            ,
//                            GUI::MAX_VALUE_TEXTEDITOR_N_CHARS , APP::ALPHANEMERIC) ;

    //[/Constructor]
}

ClipsTableItem::~ClipsTableItem()
{
    //[Destructor_pre]. You can add your own custom destruction code here..

    this->loadButton       ->removeListener(this) ;
    this->editButton       ->removeListener(this) ;
    this->deleteButton     ->removeListener(this) ;
    this->addMetadataButton->removeListener(this) ;

    //[/Destructor_pre]

    keyLabel = nullptr;
    valueLabel = nullptr;
    loadButton = nullptr;
    editButton = nullptr;
    deleteButton = nullptr;
    addMetadataButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ClipsTableItem::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ClipsTableItem::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    valueLabel->setBounds (128, 0, getWidth() - 128, 24);
    loadButton->setBounds (((getWidth() - -1336 - 24) + 0 - 24) + 0 - 24, 0, 24, 24);
    editButton->setBounds ((getWidth() - -1336 - 24) + 0 - 24, 0, 24, 24);
    deleteButton->setBounds (getWidth() - -1336 - 24, 0, 24, 24);
    addMetadataButton->setBounds (getWidth() - -1336 - 24, 0, 24, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void ClipsTableItem::buttonClicked(Button* a_button) // clip nodes
{
  Button* load_btn     = this->loadButton       .get() ;
  Button* edit_btn     = this->editButton       .get() ;
  Button* delete_btn   = this->deleteButton     .get() ;
  Button* metadata_btn = this->addMetadataButton.get() ;

  if      (a_button == load_btn    ) AudioTagToo::LoadClip(this->clipStore) ;
  else if (a_button == edit_btn    ) showEditor() ;
  else if (a_button == delete_btn  ) this->clipStore.getParent().removeChild(this->clipStore , nullptr) ;
  else if (a_button == metadata_btn) this->clipStore.setProperty(STORE::NEW_KEY_KEY , String::empty , nullptr) ;
}

void ClipsTableItem::labelTextChanged(Label* a_label) // metadata leaf nodes
{
DBG("ClipsTableItem::labelTextChanged() a_label='" + a_label->getText() + "'") ;
DBG("ClipsTableItem::labelTextChanged() isValidIdentifier('ok')=" + String((Identifier::isValidIdentifier(String("ok"))) ? "true" : "false")) ;
DBG("ClipsTableItem::labelTextChanged() isValidIdentifier('')=" + String((Identifier::isValidIdentifier(String::empty)) ? "true" : "false")) ;
DBG("ClipsTableItem::labelTextChanged() isValidIdentifier(key)=" + String((Identifier::isValidIdentifier(this->keyLabel->getText())) ? "true" : "false")) ;

  Identifier key            = this->keyLabel  ->getText() ;
  var        value          = this->valueLabel->getText() ;
  bool       is_valid_key   = Identifier::isValidIdentifier(STRING(key)) ;
  bool       is_valid_value = !STRING(value).isEmpty() ;

  if (is_valid_key && is_valid_value && key != STORE::NEW_KEY_KEY)
  {
//     if (this->clipStore.hasProperty(key))
    this->clipStore.removeProperty(this->itemId , nullptr) ;
    this->clipStore.setProperty(key , String::empty , nullptr) ;
    this->clipStore.removeProperty(STORE::NEW_KEY_KEY , nullptr) ;
  }
}

MasterClipsTableItem::MasterClipsTableItem(String item_id , String key_text) :
  ClipsTableItem(item_id , key_text , String::empty , ValueTree::invalid)
{
Trace::TraceGui("configuring MasterClipsTableItem '" + key_text + "|" + value_text) ;

  // ensure master items are immutable
  removeChildComponent(this->valueLabel       .get()) ;
  removeChildComponent(this->loadButton       .get()) ;
  removeChildComponent(this->editButton       .get()) ;
  removeChildComponent(this->deleteButton     .get()) ;
  removeChildComponent(this->addMetadataButton.get()) ;
}

ClipClipsTableItem::ClipClipsTableItem(String item_id , String key_text , ValueTree clip_store) :
  ClipsTableItem(item_id , key_text , String::empty , clip_store)
{
Trace::TraceGui("configuring ClipClipsTableItem '" + key_text + "|" + value_text) ;

  if (this->clipStore.isValid())
  {
    Value label_storage = this->clipStore.getPropertyAsValue(STORE::LABEL_TEXT_KEY , nullptr) ;

    removeChildComponent(this->valueLabel.get()) ;

    this->keyLabel->getTextValue().referTo(label_storage) ;
    this->keyLabel               ->addListener(this) ;
    this->loadButton             ->addListener(this) ;
    this->editButton             ->addListener(this) ;
    this->deleteButton           ->addListener(this) ;
    this->addMetadataButton      ->addListener(this) ;
  }
}

LeafClipsTableItem::LeafClipsTableItem(String item_id , String key_text , String value_text) :
  ClipsTableItem(item_id , key_text , value_text , ValueTree::invalid)
{
Trace::TraceGui("configuring LeafClipsTableItem '" + key_text + "|" + value_text) ;

    Identifier key           = Identifier(this->keyLabel->getText()) ;
    Value      label_storage = this->clipStore.getPropertyAsValue(key , nullptr) ;

    this->keyLabel                 ->addListener(this) ;
    this->valueLabel->getTextValue().referTo(label_storage) ;

if (key == STORE::NEW_KEY_KEY) showEditor() ;

    // ensure basic metadata leaf items are immutable
bool is_basic_metadata = true ;
    if (is_basic_metadata)
    {
      removeChildComponent(this->editButton       .get()) ;
      removeChildComponent(this->deleteButton     .get()) ;
    }
    removeChildComponent(  this->loadButton       .get()) ;
    removeChildComponent(  this->addMetadataButton.get()) ;
}

void MasterClipsTableItem::showEditor()
{
DBG("MasterClipsTableItem::showEditor() keyLabel="   + this->keyLabel->getComponentID()  +
                                      " valueLabel=" + this->valueLabel->getComponentID()) ;
/*
  TextEditor* editor ;

  if ((editor = static_cast<TextEditor*>(findChildWithID("fred"  ))) != nullptr ||
      (editor = static_cast<TextEditor*>(findChildWithID("barney"))) != nullptr  )
  {
    editor->showEditor() ;
    editor->setTextToShowWhenEmpty(GUI::NEW_KEY_TEXT   , GUI::TEXT_DISABLED_COLOR) ;
    editor->setTextToShowWhenEmpty(GUI::NEW_VALUE_TEXT , GUI::TEXT_DISABLED_COLOR) ;
  }
*/
}

void ClipClipsTableItem::showEditor()
{
DBG("ClipClipsTableItem::showEditor() keyLabel="   + this->keyLabel->getComponentID()  +
                                    " valueLabel=" + this->valueLabel->getComponentID()) ;
}

void LeafClipsTableItem::showEditor()
{
DBG("LeafClipsTableItem::showEditor() keyLabel="   + this->keyLabel->getComponentID()  +
                                    " valueLabel=" + this->valueLabel->getComponentID()) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ClipsTableItem" componentName=""
                 parentClasses="public Component, protected Button::Listener, protected Label::Listener"
                 constructorParams="String item_id , String key_text , String value_text , ValueTree clip_store"
                 variableInitialisers="itemId(item_id) , clipStore(clip_store)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1" initialHeight="1">
  <BACKGROUND backgroundColour="ff323e44"/>
  <LABEL name="" id="53e00129390ce15c" memberName="keyLabel" virtualName=""
         explicitFocusOrder="0" pos="0 0 128 24" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="key :" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="24.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="33"/>
  <LABEL name="" id="634a9112ae594fd7" memberName="valueLabel" virtualName=""
         explicitFocusOrder="0" pos="128 0 128M 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="value" editableSingleClick="0"
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
               explicitFocusOrder="0" pos="-1336Rr 0 24 24" buttonText="" connectedEdges="0"
               needsCallback="0" radioGroupId="0" keepProportions="0" resourceNormal="BinaryData::processstop_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="1.00000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
  <IMAGEBUTTON name="" id="1d6dab7d33774e55" memberName="addMetadataButton"
               virtualName="" explicitFocusOrder="0" pos="-1336Rr 0 24 24" buttonText=""
               connectedEdges="0" needsCallback="0" radioGroupId="0" keepProportions="0"
               resourceNormal="BinaryData::processstop_png" opacityNormal="1.00000000000000000000"
               colourNormal="0" resourceOver="" opacityOver="1.00000000000000000000"
               colourOver="0" resourceDown="" opacityDown="1.00000000000000000000"
               colourDown="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
