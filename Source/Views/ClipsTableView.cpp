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
ClipsTableView::ClipsTableView (TreeView* treeview , const String& item_id)
    : parentTreeview(treeview) , itemId(item_id)
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

    labelL->setBounds (0, 0, 168, 24);

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

    keySelect.reset (new ComboBox (String()));
    addAndMakeVisible (keySelect.get());
    keySelect->setEditableText (true);
    keySelect->setJustificationType (Justification::centredLeft);
    keySelect->setTextWhenNothingSelected (TRANS("(Select or type property name)"));
    keySelect->setTextWhenNoChoicesAvailable (String());


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..

  setComponentID(this->itemId) ;
  this->addButton->setComponentID(this->itemId + "/" + GUI::METADATA_BTN_ID) ;

  Image add_btn_normal_img  = ImageCache::getFromMemory(BinaryData::listadd_png , BinaryData::listadd_pngSize) ;
  Image add_btn_hover_img   = ImageCache::getFromMemory(BinaryData::listadd_png , BinaryData::listadd_pngSize) ;
  Image add_btn_pressed_img = ImageCache::getFromMemory(BinaryData::listadd_png , BinaryData::listadd_pngSize) ;

  this->addButton->setImages(false , true , false ,
                             add_btn_normal_img  , 1.000f , Colour(0x00000000) ,
                             add_btn_hover_img   , 1.000f , Colour(0x00000000) ,
                             add_btn_pressed_img , 1.000f , Colour(0x00000000) ) ;

  this->keySelect->setVisible(false) ;

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

    labelR->setBounds (0 + 168, 0 + 0, getWidth() - 128, 24);
    loadButton->setBounds ((((getWidth() - 24) + 0 - 24) + 0 - 24) + 0 - 24, 0 + 0, 24, 24);
    editButton->setBounds (((getWidth() - 24) + 0 - 24) + 0 - 24, 0 + 0, 24, 24);
    deleteButton->setBounds ((getWidth() - 24) + 0 - 24, 0 + 0, 24, 24);
    addButton->setBounds (getWidth() - 24, 0 + 0, 24, 24);
    keySelect->setBounds (0 + 0, 0 + 0, 168 - 0, 24 - 0);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}


//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* ClipsTableView subclasses */

MasterClipsTableView::MasterClipsTableView(TreeView*     treeview   , const String& item_id ,
                                           const String& label_text                         ) :
                                           ClipsTableView(treeview  , item_id)
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

ClipClipsTableView::ClipClipsTableView(TreeView*     treeview   , const String& item_id   ,
                                       const String& label_text , ValueTree     clip_store) :
                                       ClipsTableView(treeview  , item_id)                ,
                                                                  clipStore(clip_store)

{
DEBUG_TRACE_CLIPCLIPSTABLEVIEW

  Value label_l_value = this->labelL->getTextValue() ;
  Value label_storage = this->clipStore.getPropertyAsValue(STORE::LABEL_TEXT_KEY    , nullptr) ;

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

LeafClipsTableView::LeafClipsTableView(TreeView*         treeview     , const String& item_id    ,
                                       const String&     key_text     , const String& value_text ,
                                       const Identifier& key_         , ValueTree     clip_store ) :
                                       ClipsTableView(treeview        , item_id)                 ,
                                       key(key_)                      , clipStore(clip_store)
{
  bool   is_immutable_metadata = STORE::ClipImmutableKeys.contains(STRING(this->key)) ;
  bool   is_new_key_dummy      = this->key == STORE::NEW_METADATA_KEY ;
  Value  label_storage         = this->clipStore.getPropertyAsValue(this->key , nullptr) ;
  Value& label_r_value         = this->labelR  ->getTextValue() ;

DEBUG_TRACE_LEAFCLIPSTABLEVIEW

  /* configuration */

  if (!is_immutable_metadata)
  {
    // enable data change callbacks
//     this->labelL->addListener(this) ;
    if (!is_new_key_dummy)
    {
      label_r_value      .referTo    (label_storage       ) ;
      this->editButton  ->addListener(this) ;
    }
    else
      this->keySelect   ->addListener(this) ;
    this->deleteButton  ->addListener(this) ;
  }


  /* presentation */

  if (!is_new_key_dummy)
  {
//   GUI::ConfigureTextEditor(labelR  ->getTextEditor()       , text_listener      ,
//                            GUI::MAX_KEY_TEXTEDITOR_N_CHARS   , APP::VALID_ID_CHARS) ;
//   GUI::ConfigureTextEditor(labelL->getTextEditor()       , nullptr            ,
//                            GUI::MAX_VALUE_TEXTEDITOR_N_CHARS , APP::ALPHANEMERIC) ;

    this->labelL->setFont(Font((float)(GUI::TREE_ITEM_H - 2) , Font::plain).withTypefaceStyle("Regular")) ;
    this->labelR->setFont(Font((float)(GUI::TREE_ITEM_H - 2) , Font::plain).withTypefaceStyle("Regular")) ;
    this->labelL->setText(key_text + ":" , juce::dontSendNotification) ;
    this->labelR->setText(value_text     , juce::dontSendNotification) ;
  }

  if (!is_immutable_metadata)
  {
    this->editButton  ->setTooltip(GUI::EDIT_BTN_HOVERTEXT  ) ;
    this->deleteButton->setTooltip(GUI::DELETE_BTN_HOVERTEXT) ;

    if (is_new_key_dummy)
    {
      // enable new key entry/selection
      populateKeySelect() ;
      int    n_key_options          = this->keySelect->getNumItems() ;
      String default_keyselect_text = (n_key_options > 0) ? GUI::NEW_KEY_TEXT       :
                                                            GUI::NEW_FIRST_KEY_TEXT ;

      this->keySelect->setTextWhenNoChoicesAvailable(GUI::NEW_FIRST_KEY_TEXT) ;
      this->keySelect->setTextWhenNothingSelected   (default_keyselect_text) ;
      this->keySelect->setSelectedItemIndex(-1 , juce::dontSendNotification) ;
      this->keySelect->setVisible(true) ;
    }
  }

  if (is_immutable_metadata)
  {
    // ensure basic metadata leaf items are immutable
    removeChildComponent(this->editButton  .get()) ;
    removeChildComponent(this->deleteButton.get()) ;
  }
  else if (is_new_key_dummy)
  {
    removeChildComponent(this->labelR      .get()) ;
    removeChildComponent(this->editButton  .get()) ;
  }
  removeChildComponent  (this->loadButton  .get()) ;
  removeChildComponent  (this->addButton   .get()) ;
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


/* ClipsTableView subclass event handlers */

// void ClipClipsTableView::paint(Graphics& g)
// {
//   ((ClipsTableView*)this)->paint(g) ;
//   if (this->isDragItemHovering) { g.setColour(Colours::red) ; g.drawRect(getLocalBounds() , 3) ; }
// }

void LeafClipsTableView::parentHierarchyChanged()
{
  if (!isShowing()) return ;

  bool is_new_key_dummy      = this->key == STORE::NEW_METADATA_KEY ;
  bool is_immutable_metadata = STORE::ClipImmutableKeys.contains(STRING(this->key)) ;

DEBUG_TRACE_LEAFVIEW_HIERARCHY_CHANGED

  if (is_new_key_dummy)
  {
//     this->keySelect->showPopup () ;
//     this->keySelect->showEditor() ;
  }
  else if (!is_immutable_metadata && this->labelR->getText().isEmpty()) showEditor() ;
}

void LeafClipsTableView::comboBoxChanged(ComboBox* a_combobox)
{
  ComboBox* key_select = keySelect.get() ;

DEBUG_TRACE_LEAFVIEW_COMBOBOX_CHANGED

    if (a_combobox == keySelect.get()) handleComboBox(key_select->getText()) ;
}

void ClipClipsTableView::buttonClicked(Button* a_button)
{
  Button* load_btn   = this->loadButton  .get() ;
  Button* edit_btn   = this->editButton  .get() ;
  Button* delete_btn = this->deleteButton.get() ;
  Button* add_btn    = this->addButton   .get() ;

DEBUG_TRACE_CLIPVIEW_BTN_CLICKED

  if      (a_button == load_btn  ) AudioTagToo::LoadClip(this->clipStore) ;
  else if (a_button == edit_btn  ) showEditor() ;
  else if (a_button == delete_btn) removeClip() ;
  else if (a_button == add_btn   ) addMetadata() ;
}

void LeafClipsTableView::buttonClicked(Button* a_button)
{
  Button* edit_btn   = this->editButton  .get() ;
  Button* delete_btn = this->deleteButton.get() ;

DEBUG_TRACE_LEAFVIEW_BTN_CLICKED

  if      (a_button == edit_btn  ) showEditor() ;
  else if (a_button == delete_btn) resetMetadata() ;
}

// void ClipClipsTableView::mouseDown(const MouseEvent& evt)
// {
// DBG("ClipClipsTableView::mouseDown()") ;
// }
//
// void ClipClipsTableView::mouseDrag(const MouseEvent& evt)
// {
// DBG("ClipClipsTableView::mouseDrag()") ;
// }
//
// void ClipClipsTableView::mouseUp(const MouseEvent& evt)
// {
// DBG("ClipClipsTableView::mouseUp()") ;
// }


/* ClipsTableView subclass helpers */

void ClipClipsTableView::addMetadata()
{
  TreeViewItem* this_item = this->parentTreeview->findItemFromIdentifierString(this->itemId) ;

DEBUG_TRACE_LEAFVIEW_ADD_METADATA

  // present dummy LeafClipsTableItem for new key definition
  this->clipStore.removeProperty(STORE::NEW_METADATA_KEY ,                   nullptr) ;
  this->clipStore.setProperty(STORE::NEW_METADATA_KEY , var(String::empty) , nullptr) ;
  AudioTagToo::CreateMetadata(this->clipStore , STORE::NEW_METADATA_KEY) ;

  if (this_item != nullptr) this_item->setOpen(true) ;
  this->addButton->setEnabled(false) ;
}

void LeafClipsTableView::resetMetadata()
{
  bool          is_new_key_dummy = this->key == STORE::NEW_METADATA_KEY ;
  String        clip_item_id     = STRING(this->clipStore[STORE::ITEM_ID_KEY]) ;
  String        add_btn_id       = clip_item_id + "/" + GUI::METADATA_BTN_ID ;
  Component*    clip_view        = getParentComponent()->findChildWithID(clip_item_id) ;
  Component*    add_btn          = clip_view           ->findChildWithID(add_btn_id) ;
  Value&        label_r_value    = this->labelR->getTextValue() ;
  TreeViewItem* this_item        = this->parentTreeview->findItemFromIdentifierString(this->itemId) ;
  TreeViewItem* parent_item      = this_item->getParentItem() ;
  int           this_idx         = this_item->getIndexInParent() ;

DEBUG_TRACE_LEAFVIEW_RESET_METADATA

  if (is_new_key_dummy) add_btn->setEnabled(true) ;

  // destroy stored data
  label_r_value.referTo(Value()) ;
  this->clipStore.removeProperty(this->key , nullptr) ;

  // delete this view and host item
  if (parent_item != nullptr) parent_item->removeSubItem(this_idx) ;
}

void LeafClipsTableView::populateKeySelect()
{
  int           n_properties = this->clipStore.getNumProperties() ;
  NamedValueSet keys         = AudioTagToo::GetMetadataKeys() ;
  StringArray   key_options ;

  // filter immutable keys
  for (int property_n = 0 ; property_n < n_properties ; ++property_n)
  {
    Identifier key = this->clipStore.getPropertyName(property_n) ;

    keys.remove(key) ;
  }

  int n_keys = keys.size() ;

  // populate options array
  for (int key_n = 0 ; key_n < n_keys ; ++key_n)
  {
    Identifier key = keys.getName(key_n) ;

    key_options.add(STRING(key)) ;
  }

DEBUG_TRACE_POPULATE_KEYSELECT

  this->keySelect->clear() ;
  this->keySelect->addItemList(key_options , 1) ;
}

void LeafClipsTableView::handleComboBox(const String& key_string)
{
  Identifier new_key          = Identifier(key_string) ;
  bool       should_store_key = isAcceptableUserKey(key_string) ;

DEBUG_TRACE_HANDLE_COMBOBOX

  if (should_store_key)
  {
    // instantiate replacement LeafClipsTableItem
    this->clipStore.setProperty(new_key , var(String::empty) , nullptr) ;
    AudioTagToo::CreateMetadata(this->clipStore , new_key) ;

    // destroy this dummy LeafClipsTableItem
    resetMetadata() ;
  }
  else
  {
    this->keySelect->setColour(ComboBox::backgroundColourId , GUI::TEXT_INVALID_COLOR    ) ;
    this->keySelect->setColour(ComboBox::outlineColourId    , GUI::COMBOBOX_INVALID_COLOR) ;
  }
}

bool LeafClipsTableView::isAcceptableUserKey(const String& key_string)
{
  Identifier key               = Identifier(key_string) ;
  bool       is_valid_key      = Identifier::isValidIdentifier(key_string) ;
  bool       is_acceptable_key = is_valid_key && !STORE::ClipPersistentKeys.contains(key) &&
                                                 !STORE::ClipTransientKeys .contains(key)  ;

  return is_acceptable_key ;
}

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

  this->labelR->showEditor() ;

  TextEditor* editor_r = this->labelR->getCurrentTextEditor() ;

  editor_r->setTextToShowWhenEmpty(GUI::NEW_VALUE_TEXT , GUI::TEXT_DISABLED_COLOR) ;
}

void ClipClipsTableView::removeClip()
{
DEBUG_TRACE_CLIPVIEW_REMOVE_CLIP

  this->clipStore.getParent().removeChild(this->clipStore , nullptr) ;
}


/* ClipsTableItem */

ClipsTableItem::ClipsTableItem(const String& item_id , const String& label_text_l , const String& label_text_r) :
                               itemId(item_id)       , labelTextL(label_text_l)   , labelTextR(label_text_r)    { }

String ClipsTableItem::getUniqueName() const { return this->itemId ; }

int ClipsTableItem::getItemHeight() const { return GUI::TREE_ITEM_H ; }


/* ClipsTableItem subclasses */

MasterClipsTableItem::MasterClipsTableItem(const String& item_id  , const String& label_text) :
                                           ClipsTableItem(item_id , label_text)
{
DEBUG_TRACE_MASTERCLIPSTABLEITEM
}

ClipClipsTableItem::ClipClipsTableItem(const String& item_id  , const String& label_text , ValueTree clip_store) :
                                       ClipsTableItem(item_id , label_text)              , clipStore(clip_store)
{
DEBUG_TRACE_CLIPCLIPSTABLEITEM
}

LeafClipsTableItem::LeafClipsTableItem(const String&     item_id , const String& key_text   , const String& value_text ,
                                       const Identifier& key_    , ValueTree     clip_store                            ) :
                                       ClipsTableItem(item_id    , key_text                 , value_text)              ,
                                       key(key_)                 , clipStore(clip_store)
{
DEBUG_TRACE_LEAFCLIPSTABLEITEM
}


/* ClipsTableItem subclass TreeViewItem implementation */

bool MasterClipsTableItem::mightContainSubItems() { return true ; }

bool ClipClipsTableItem::mightContainSubItems() { return true ; }

bool LeafClipsTableItem::mightContainSubItems() { return false ; }

Component* MasterClipsTableItem::createItemComponent()
{
  // instantiate library-managed, transient GUI component
  return new MasterClipsTableView(getOwnerView() , getItemIdentifierString() , this->labelTextL) ;
}

Component* ClipClipsTableItem::createItemComponent()
{
  // instantiate library-managed, transient GUI component
  return new ClipClipsTableView(getOwnerView()   , getItemIdentifierString() ,
                                this->labelTextL , this->clipStore           ) ;
}

Component* LeafClipsTableItem::createItemComponent()
{
  // instantiate library-managed, transient GUI component
  return new LeafClipsTableView(getOwnerView()    , getItemIdentifierString() ,
                                this->labelTextL  , this->labelTextR          ,
                                this->key         , this->clipStore           ) ;
}


/* ClipsTableItem subclass DragAndDropTarget implementation */

bool MasterClipsTableItem::isInterestedInDragSource(const DragAndDropTarget::SourceDetails& dragSourceDetails)
{
DBG("MasterClipsTableItem::isInterestedInDragSource() dragSourceDetails=" + STRING(dragSourceDetails.description) +
    " is_interested=" + String(dragSourceDetails.description.equalsWithSameType(GUI::CLIP_ITEM_DRAG_ID) ? "true" : "false") ) ;

//   return true ;
  return dragSourceDetails.description.equalsWithSameType(GUI::CLIP_ITEM_DRAG_ID) ;
}

void MasterClipsTableItem::itemDragEnter(const DragAndDropTarget::SourceDetails& dragSourceDetails)
{
DBG("MasterClipsTableItem::itemDragEnter") ;

  this->isDragItemHovering = true ; //repaint() ;
}

void MasterClipsTableItem::itemDragMove(const DragAndDropTarget::SourceDetails& dragSourceDetails)
{
DBG("MasterClipsTableItem::itemDragMove") ;
}

void MasterClipsTableItem::itemDragExit(const DragAndDropTarget::SourceDetails& dragSourceDetails)
{
  this->isDragItemHovering = false ; //repaint() ;
}

void MasterClipsTableItem::itemDropped(const DragAndDropTarget::SourceDetails& dragSourceDetails)
{
DBG("MasterClipsTableItem::itemDropped() dragSourceDetails=" + STRING(dragSourceDetails.description)) ;

  this->isDragItemHovering = false ; //repaint() ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ClipsTableView" componentName=""
                 parentClasses="public Component" constructorParams="TreeView* treeview , const String&amp; item_id"
                 variableInitialisers="parentTreeview(treeview) , itemId(item_id)"
                 snapPixels="4" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1" initialHeight="1">
  <BACKGROUND backgroundColour="ff323e44"/>
  <LABEL name="" id="53e00129390ce15c" memberName="labelL" virtualName=""
         explicitFocusOrder="0" pos="0 0 168 24" textCol="ffffffff" edTextCol="ff000000"
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
               explicitFocusOrder="0" pos="0r 0 24 24" posRelativeX="75e098fccc4e97e"
               posRelativeY="53e00129390ce15c" buttonText="" connectedEdges="0"
               needsCallback="0" radioGroupId="0" keepProportions="0" resourceNormal="BinaryData::processstop_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="1.00000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
  <GENERICCOMPONENT name="" id="75e098fccc4e97e" memberName="addButton" virtualName=""
                    explicitFocusOrder="0" pos="0Rr 0 24 24" posRelativeY="53e00129390ce15c"
                    class="ValueControlledButton" params="item_id"/>
  <COMBOBOX name="" id="e14bf58725f7ec5a" memberName="keySelect" virtualName=""
            explicitFocusOrder="0" pos="0 0 0M 0M" posRelativeX="53e00129390ce15c"
            posRelativeY="53e00129390ce15c" posRelativeW="53e00129390ce15c"
            posRelativeH="53e00129390ce15c" editable="1" layout="33" items=""
            textWhenNonSelected="(Select or type property name)" textWhenNoItems=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
