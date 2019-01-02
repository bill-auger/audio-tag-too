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


//[Headers] You can add your own extra header files here...

#include "../Constants/GuiConstants.h"
#include "../Constants/StorageConstants.h"
#include "../Controllers/AudioTagToo.h"
#include "../Trace/TraceClipsTable.h"

//[/Headers]

#include "ClipsTableView.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ClipsTableView::ClipsTableView ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    labelL.reset (new Label (String(),
                             TRANS("key :")));
    addAndMakeVisible (labelL.get());
    labelL->setFont (Font (24.00f, Font::plain));
    labelL->setJustificationType (Justification::centredLeft);
    labelL->setEditable (false, false, false);
    labelL->setColour (Label::textColourId, Colours::white);
    labelL->setColour (TextEditor::textColourId, Colours::black);
    labelL->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    labelL->setBounds (0, 0, 128, 24);

    labelR.reset (new Label (String(),
                             TRANS("value")));
    addAndMakeVisible (labelR.get());
    labelR->setFont (Font (24.00f, Font::plain));
    labelR->setJustificationType (Justification::centredLeft);
    labelR->setEditable (false, false, false);
    labelR->setColour (Label::textColourId, Colours::white);
    labelR->setColour (TextEditor::textColourId, Colours::black);
    labelR->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

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
    addButton.reset (new ImageButton (String()));
    addAndMakeVisible (addButton.get());

    addButton->setImages (false, true, false,
                          ImageCache::getFromMemory (BinaryData::listadd_png, BinaryData::listadd_pngSize), 1.000f, Colour (0x00000000),
                          Image(), 1.000f, Colour (0x00000000),
                          Image(), 1.000f, Colour (0x00000000));
    keySelect.reset (new ComboBox (String()));
    addAndMakeVisible (keySelect.get());
    keySelect->setEditableText (true);
    keySelect->setJustificationType (Justification::centredLeft);
    keySelect->setTextWhenNothingSelected (String());
    keySelect->setTextWhenNoChoicesAvailable (String());
    keySelect->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..

  this->keySelect->setTextWhenNothingSelected(GUI::NEW_KEY_TEXT) ;

    //[/Constructor]
}

ClipsTableView::~ClipsTableView()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    labelL = nullptr;
    labelR = nullptr;
    loadButton = nullptr;
    editButton = nullptr;
    deleteButton = nullptr;
    addButton = nullptr;
    keySelect = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ClipsTableView::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ClipsTableView::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    labelR->setBounds (0 + 128, 0 + 0, getWidth() - 128, 24);
    loadButton->setBounds ((((getWidth() - 24) + 0 - 24) + 0 - 24) + 0 - 24, 0 + 0, 24, 24);
    editButton->setBounds (((getWidth() - 24) + 0 - 24) + 0 - 24, 0 + 0, 24, 24);
    deleteButton->setBounds ((getWidth() - 24) + 0 - 24, 0 + 0, 24, 24);
    addButton->setBounds (getWidth() - 24, 0 + 0, 24, 24);
    keySelect->setBounds (0 + 0, 0 + 0, 128 - 0, 24 - 0);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ClipsTableView::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
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

/* ClipsTableView subclasses */

MasterClipsTableView::MasterClipsTableView(String label_text)
{
DEBUG_TRACE_MASTERCLIPSTABLEVIEW

  this->labelL->setText(label_text , juce::dontSendNotification) ;
  this->labelL->setFont(Font((float)(GUI::TREE_ITEM_H - 2) , Font::plain).withTypefaceStyle("Regular")) ;

  // ensure master items are immutable
  removeChildComponent(this->labelR      .get()) ;
  removeChildComponent(this->loadButton  .get()) ;
  removeChildComponent(this->editButton  .get()) ;
  removeChildComponent(this->deleteButton.get()) ;
  removeChildComponent(this->addButton   .get()) ;
}

ClipClipsTableView::ClipClipsTableView(String label_text , ValueTree store_) :
                                                           store(store_)
{
DEBUG_TRACE_CLIPCLIPSTABLEVIEW

  Value label_l_value = this->labelL->getTextValue() ;
  Value label_storage = this->store.getPropertyAsValue(STORE::LABEL_TEXT_KEY , nullptr) ;

//   GUI::ConfigureTextEditor(labelL  ->getTextEditor()       , text_listener      ,
//                            GUI::MAX_CLIPNAME_TEXTEDITOR_N_CHARS   , APP::VALID_ID_CHARS) ;
  this->labelL      ->setText(label_text , juce::dontSendNotification) ;
  this->labelL      ->setFont(Font((float)(GUI::TREE_ITEM_H - 2) , Font::plain).withTypefaceStyle("Regular")) ;
  this->loadButton  ->setTooltip(GUI::LOAD_BTN_HOVERTEXT    ) ;
  this->editButton  ->setTooltip(GUI::EDIT_BTN_HOVERTEXT    ) ;
  this->deleteButton->setTooltip(GUI::DELETE_BTN_HOVERTEXT  ) ;
  this->addButton   ->setTooltip(GUI::METADATA_BTN_HOVERTEXT) ;

  removeChildComponent(this->labelR.get()) ;

  // enable data change callbacks
  label_l_value      .referTo(label_storage) ;
  this->loadButton  ->addListener(this) ;
  this->editButton  ->addListener(this) ;
  this->deleteButton->addListener(this) ;
  this->addButton   ->addListener(this) ;
}

LeafClipsTableView::LeafClipsTableView(String key_text , String value_text ,
                                       Identifier key_ , ValueTree store_  ) :
                                       key(key_)       , store(store_)
{
  Value label_r_value        = this->labelR->getTextValue() ;
  Value label_storage        = this->store.getPropertyAsValue(this->key , nullptr) ;
  bool  is_standard_metadata = STORE::MetadataKeys().contains(STRING(this->key)) &&
                               !this->store.isValid() ;

DEBUG_TRACE_LEAFCLIPSTABLEVIEW

if (key == STORE::NEW_KEY_KEY) showEditor() ;

//   GUI::ConfigureTextEditor(labelR  ->getTextEditor()       , text_listener      ,
//                            GUI::MAX_KEY_TEXTEDITOR_N_CHARS   , APP::VALID_ID_CHARS) ;
//   GUI::ConfigureTextEditor(labelL->getTextEditor()       , nullptr            ,
//                            GUI::MAX_VALUE_TEXTEDITOR_N_CHARS , APP::ALPHANEMERIC) ;
  this->labelL->setText(key_text + ":" , juce::dontSendNotification) ;
  this->labelR->setText(value_text     , juce::dontSendNotification) ;
  this->labelL->setFont(Font((float)(GUI::TREE_ITEM_H - 2) , Font::plain).withTypefaceStyle("Regular")) ;
  this->labelR->setFont(Font((float)(GUI::TREE_ITEM_H - 2) , Font::plain).withTypefaceStyle("Regular")) ;

  if (!is_standard_metadata)
  {
    this->editButton  ->setTooltip(GUI::EDIT_BTN_HOVERTEXT  ) ;
    this->deleteButton->setTooltip(GUI::DELETE_BTN_HOVERTEXT) ;

    // enable data change callbacks
//     this->labelL->addListener(this) ;
    label_r_value.referTo(label_storage) ;
  }
  else
  {
    // enable data change callbacks
    this->editButton  ->addListener(this) ;
    this->deleteButton->addListener(this) ;

    // ensure basic metadata leaf items are immutable
    removeChildComponent(this->editButton  .get()) ;
    removeChildComponent(this->deleteButton.get()) ;
  }
  removeChildComponent(  this->loadButton  .get()) ;
  removeChildComponent(  this->addButton   .get()) ;
}

ClipClipsTableView::~ClipClipsTableView()
{
  this->loadButton  ->removeListener(this) ;
  this->editButton  ->removeListener(this) ;
  this->deleteButton->removeListener(this) ;
  this->addButton   ->removeListener(this) ;
}

LeafClipsTableView::~LeafClipsTableView()
{
  this->editButton  ->removeListener(this) ;
  this->deleteButton->removeListener(this) ;
}

void ClipClipsTableView::buttonClicked(Button* a_button)
{
  Button* load_btn   = this->loadButton  .get() ;
  Button* edit_btn   = this->editButton  .get() ;
  Button* delete_btn = this->deleteButton.get() ;
  Button* add_btn    = this->addButton   .get() ;

DEBUG_TRACE_CLIPVIEW_BTN_CLICKED

  if      (a_button == load_btn  ) AudioTagToo::LoadClip(this->store) ;
  else if (a_button == edit_btn  ) showEditor() ;
  else if (a_button == delete_btn) removeClip() ;
  else if (a_button == add_btn   ) setMetadata() ;
}

void LeafClipsTableView::buttonClicked(Button* a_button)
{
  Button* edit_btn   = this->editButton  .get() ;
  Button* delete_btn = this->deleteButton.get() ;

DEBUG_TRACE_LEAFVIEW_BTN_CLICKED

  if      (a_button == edit_btn  ) showEditor() ;
  else if (a_button == delete_btn) resetMetadata() ;
}
/*
void LeafClipsTableView::labelTextChanged(Label* a_label) // metadata leaf nodes
{
DBG("LeafClipsTableView::labelTextChanged() a_label='" + a_label->getText() + "'") ;
DBG("LeafClipsTableView::labelTextChanged() isValidIdentifier('ok')=" + String((Identifier::isValidIdentifier(String("ok"))) ? "true" : "false")) ;
DBG("LeafClipsTableView::labelTextChanged() isValidIdentifier('')=" + String((Identifier::isValidIdentifier(String::empty)) ? "true" : "false")) ;
DBG("LeafClipsTableView::labelTextChanged() isValidIdentifier(key)=" + String((Identifier::isValidIdentifier(this->labelR->getText())) ? "true" : "false")) ;

  String     key_text       = this->labelL->getText() ;
  String     value_text     = this->labelR->getText() ;
  Identifier new_key        = Identifier(key_text) ;
  bool       is_valid_key   = Identifier::isValidIdentifier(key_text) ;
  bool       is_valid_value = !value_text.isEmpty() ;

  if (is_valid_key && is_valid_value && new_key != STORE::NEW_KEY_KEY)
  {
    // trigger destruction of this parent LeafClipsTableItem
//     if (this->store.hasProperty(key))
    this->store.removeProperty(this->key , nullptr) ;
    this->store.removeProperty(STORE::NEW_KEY_KEY , nullptr) ;

    // trigger instantiation of replacement LeafClipsTableItem
    this->store.setProperty(new_key , String::empty , nullptr) ;
  }
}
*/
void ClipClipsTableView::showEditor()
{
DEBUG_TRACE_CLIPVIEW_SHOW_EDITOR

  this->labelL->showEditor() ;

  TextEditor* editor_l = this->labelL->getCurrentTextEditor() ;

  editor_l->setTextToShowWhenEmpty(GUI::NEW_CLIPNAME_TEXT , GUI::TEXT_DISABLED_COLOR) ;
}

void LeafClipsTableView::showEditor()
{
DEBUG_TRACE_LEAFVIEW_SHOW_EDITOR

//   this->labelL->showEditor() ;
  this->labelR->showEditor() ;

//   TextEditor* editor_l = this->labelL->getCurrentTextEditor() ;
  TextEditor* editor_r = this->labelR->getCurrentTextEditor() ;

//   editor_l->setTextToShowWhenEmpty(GUI::NEW_KEY_TEXT   , GUI::TEXT_DISABLED_COLOR) ;
  editor_r->setTextToShowWhenEmpty(GUI::NEW_VALUE_TEXT , GUI::TEXT_DISABLED_COLOR) ;
}

void ClipClipsTableView::removeClip()
{
DEBUG_TRACE_CLIPVIEW_REMOVE_CLIP

  this->store.getParent().removeChild(this->store , nullptr) ;
}

void ClipClipsTableView::setMetadata()
{
DEBUG_TRACE_LEAFVIEW_SET_METADATA

  this->store.setProperty(STORE::NEW_KEY_KEY , String::empty , nullptr) ;
}

void LeafClipsTableView::resetMetadata()
{
DEBUG_TRACE_LEAFVIEW_RESET_METADATA

  this->store.removeProperty(this->key , nullptr) ;
}


/* ClipsTableItem */

ClipsTableItem::ClipsTableItem(String item_id  , String label_text_l      , String label_text_r) :
                               itemId(item_id) , labelTextL(label_text_l) , labelTextR(label_text_r) { }

String ClipsTableItem::getUniqueName() const { return this->itemId ; }

int ClipsTableItem::getItemHeight() const { return GUI::TREE_ITEM_H ; }

ClipsTableView* ClipsTableItem::setId(ClipsTableView* new_view)
{
  new_view->setComponentID(this->itemId) ;

  return new_view ;
}


/* ClipsTableItem subclasses */

MasterClipsTableItem::MasterClipsTableItem(String item_id , String label_text) :
  ClipsTableItem(item_id , label_text)
{
DEBUG_TRACE_MASTERCLIPSTABLEITEM
}

ClipClipsTableItem::ClipClipsTableItem(String item_id , String label_text , ValueTree store) :
  ClipsTableItem(item_id , label_text) , store(store)
{
DEBUG_TRACE_CLIPCLIPSTABLEITEM
}

LeafClipsTableItem::LeafClipsTableItem(String     item_id , String     key_text , String value_text ,
                                       Identifier key_    , ValueTree  store_                       ) :
  ClipsTableItem(item_id , key_text , value_text) , key(key_) , store(store_)
{
DEBUG_TRACE_LEAFCLIPSTABLEITEM
}

bool MasterClipsTableItem::mightContainSubItems() { return TRUE ; }
bool ClipClipsTableItem::mightContainSubItems() { return TRUE ; }
bool LeafClipsTableItem::mightContainSubItems() { return FALSE ; }

Component* MasterClipsTableItem::createItemComponent()
{
  // instantiate library-managed, transient GUI component
  return setId(new MasterClipsTableView(this->labelTextL)) ;
}

Component* ClipClipsTableItem::createItemComponent()
{
  // instantiate library-managed, transient GUI component
  return setId(new ClipClipsTableView(this->labelTextL , this->store)) ;
}

Component* LeafClipsTableItem::createItemComponent()
{
  // instantiate library-managed, transient GUI component
  return setId(new LeafClipsTableView(this->labelTextL , this->labelTextR , this->key , this->store)) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ClipsTableView" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1" initialHeight="1">
  <BACKGROUND backgroundColour="ff323e44"/>
  <LABEL name="" id="53e00129390ce15c" memberName="labelL" virtualName=""
         explicitFocusOrder="0" pos="0 0 128 24" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="key :" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="24.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="33"/>
  <LABEL name="" id="634a9112ae594fd7" memberName="labelR" virtualName=""
         explicitFocusOrder="0" pos="0R 0 128M 24" posRelativeX="53e00129390ce15c"
         posRelativeY="53e00129390ce15c" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="value" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="24.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="33"/>
  <IMAGEBUTTON name="" id="8137f12729559747" memberName="loadButton" virtualName=""
               explicitFocusOrder="0" pos="0r 0 24 24" posRelativeX="c7460681b30100df"
               posRelativeY="53e00129390ce15c" buttonText="" connectedEdges="0"
               needsCallback="0" radioGroupId="0" keepProportions="0" resourceNormal="BinaryData::mediaplaybackstart_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="1.00000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
  <IMAGEBUTTON name="" id="c7460681b30100df" memberName="editButton" virtualName=""
               explicitFocusOrder="0" pos="0r 0 24 24" posRelativeX="5519a8f967bbfc3e"
               posRelativeY="53e00129390ce15c" buttonText="" connectedEdges="0"
               needsCallback="0" radioGroupId="0" keepProportions="0" resourceNormal="BinaryData::accessoriestexteditor_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="1.00000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
  <IMAGEBUTTON name="" id="5519a8f967bbfc3e" memberName="deleteButton" virtualName=""
               explicitFocusOrder="0" pos="0r 0 24 24" posRelativeX="1d6dab7d33774e55"
               posRelativeY="53e00129390ce15c" buttonText="" connectedEdges="0"
               needsCallback="0" radioGroupId="0" keepProportions="0" resourceNormal="BinaryData::processstop_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="1.00000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
  <IMAGEBUTTON name="" id="1d6dab7d33774e55" memberName="addButton" virtualName=""
               explicitFocusOrder="0" pos="0Rr 0 24 24" posRelativeY="53e00129390ce15c"
               buttonText="" connectedEdges="0" needsCallback="0" radioGroupId="0"
               keepProportions="0" resourceNormal="BinaryData::listadd_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="1.00000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
  <COMBOBOX name="" id="e14bf58725f7ec5a" memberName="keySelect" virtualName=""
            explicitFocusOrder="0" pos="0 0 0M 0M" posRelativeX="53e00129390ce15c"
            posRelativeY="53e00129390ce15c" posRelativeW="53e00129390ce15c"
            posRelativeH="53e00129390ce15c" editable="1" layout="33" items=""
            textWhenNonSelected="" textWhenNoItems=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
