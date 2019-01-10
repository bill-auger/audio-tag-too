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

#include "ClipsTableView.h"
#include "../Controllers/AudioTagToo.h"
#include "../Trace/TraceClipsTable.h"

//[/Headers]

#include "ClipsTable.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ClipsTable::ClipsTable ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    compilationsGroup.reset (new GroupComponent (String(),
                                                 TRANS("Compilations")));
    addAndMakeVisible (compilationsGroup.get());
    compilationsGroup->setTextLabelPosition (Justification::centred);
    compilationsGroup->setColour (GroupComponent::outlineColourId, Colours::white);

    clipsGroup.reset (new GroupComponent (String(),
                                          TRANS("Clips")));
    addAndMakeVisible (clipsGroup.get());
    clipsGroup->setTextLabelPosition (Justification::centred);
    clipsGroup->setColour (GroupComponent::outlineColourId, Colours::white);

    clipsTreeview.reset (new TreeView (String()));
    addAndMakeVisible (clipsTreeview.get());
    clipsTreeview->setRootItemVisible (false);

    compilationsTreeview.reset (new TreeView (String()));
    addAndMakeVisible (compilationsTreeview.get());
    compilationsTreeview->setRootItemVisible (false);


    //[UserPreSize]

  this->clipItems       .reset(new RootClipsTableItem(STRING(STORE::CLIPS_ID       ))) ;
  this->compilationItems.reset(new RootClipsTableItem(STRING(STORE::COMPILATIONS_ID))) ;

    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..

  this->clipsTreeview       ->setRootItem(this->clipItems       .get()) ;
  this->compilationsTreeview->setRootItem(this->compilationItems.get()) ;

    //[/Constructor]
}

ClipsTable::~ClipsTable()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    compilationsGroup = nullptr;
    clipsGroup = nullptr;
    clipsTreeview = nullptr;
    compilationsTreeview = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ClipsTable::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ClipsTable::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    compilationsGroup->setBounds (proportionOfWidth (0.5006f), 0, proportionOfWidth (0.5006f), getHeight() - 0);
    clipsGroup->setBounds (0, 0, proportionOfWidth (0.5006f), getHeight() - 0);
    clipsTreeview->setBounds (0 + 16, 0 + 16, proportionOfWidth (0.5006f) - 32, (getHeight() - 0) - 32);
    compilationsTreeview->setBounds (proportionOfWidth (0.5006f) + 16, 0 + 16, proportionOfWidth (0.5006f) - 32, (getHeight() - 0) - 32);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* ClipsTable public instance methods */

/* setup */

bool ClipsTable::initialize(ValueTree& clips_store , ValueTree& compilations_store)
{
  bool should_initialize = !AudioTagToo::GetIsInitialized() && clips_store       .isValid() &&
                                                               compilations_store.isValid()  ;

  if (should_initialize)
  {
    createItemsTree(clips_store       ) ;
    createItemsTree(compilations_store) ;
  }

DEBUG_TRACE_INIT_GUI

  return should_initialize ;
}

void ClipsTable::createItemsTree(ValueTree& root_store)
{
DEBUG_TRACE_CREATE_ITEMS_TREE(root_store)

  for (int master_n = 0 ; master_n < root_store.getNumChildren() ; ++master_n)
    createMasterItem(root_store , root_store.getChild(master_n)) ;
}


/* ClipsTable private instance methods */

/* model/view helpers */

TreeViewItem* ClipsTable::getViewItemFor(const Identifier& root_store_id)
{
  return (root_store_id == STORE::CLIPS_ID       ) ? this->clipItems       .get() :
         (root_store_id == STORE::COMPILATIONS_ID) ? this->compilationItems.get() : nullptr ;
}

void ClipsTable::storeItemId(ValueTree a_store , TreeViewItem* an_item)
{
  String item_id = an_item->getItemIdentifierString() ;

  a_store.setProperty(STORE::ITEM_ID_KEY , var(item_id) , nullptr) ;
}

TreeViewItem* ClipsTable::newMasterItem(ValueTree& master_store)
{
  String        master_id   = STRING(master_store.getType()) ;
  String        filename    = STRING(master_store[STORE::FILENAME_KEY  ]) ; // unused
  String        label_text  = STRING(master_store[STORE::LABEL_TEXT_KEY]) ;
  TreeViewItem* master_item = new MasterClipsTableItem(master_id , label_text) ;

DEBUG_TRACE_NEW_MASTER_ITEM

  return master_item ;
}

TreeViewItem* ClipsTable::newClipItem(ValueTree& clip_store)
{
  String        clip_id             = STRING(clip_store.getType()) ;
  String        file_id             = STRING(STORE::FILENAME_KEY  ) ;
  String        begin_id            = STRING(STORE::BEGIN_TIME_KEY) ;
  String        end_id              = STRING(STORE::END_TIME_KEY  ) ;
  String        duration_id         = STRING(STORE::DURATION_KEY  ) ;
  String        file_label_text     = GUI::FILE_ITEM_LABEL ;
  String        begin_label_text    = GUI::BEGIN_ITEM_LABEL ;
  String        end_label_text      = GUI::END_ITEM_LABEL ;
  String        duration_label_text = GUI::DURATION_ITEM_LABEL ;
  String        file_value_text     = STRING(clip_store[STORE::FILENAME_KEY  ]) ;
  double        begin_time          = double(clip_store[STORE::BEGIN_TIME_KEY]) ;
  double        end_time            = double(clip_store[STORE::END_TIME_KEY  ]) ;
  String        duration_value_text = STRING(clip_store[STORE::DURATION_KEY  ]) ;
  String        clip_label_text     = STRING(clip_store[STORE::LABEL_TEXT_KEY]) ;
  String        begin_value_text    = AudioTagToo::DurationString(begin_time) ;
  String        end_value_text      = AudioTagToo::DurationString(end_time  ) ;
  TreeViewItem* clip_item           = new ClipClipsTableItem(clip_id , clip_label_text , clip_store) ;
  TreeViewItem* filename_item       = newLeafItem(file_id     , file_label_text     , file_value_text     , STORE::FILENAME_KEY  ) ;
  TreeViewItem* begin_time_item     = newLeafItem(begin_id    , begin_label_text    , begin_value_text    , STORE::BEGIN_TIME_KEY) ;
  TreeViewItem* end_time_item       = newLeafItem(end_id      , end_label_text      , end_value_text      , STORE::END_TIME_KEY  ) ;
  TreeViewItem* duration_item       = newLeafItem(duration_id , duration_label_text , duration_value_text , STORE::DURATION_KEY  ) ;

  clip_item->addSubItem(filename_item   , 0) ;
  clip_item->addSubItem(begin_time_item , 1) ;
  clip_item->addSubItem(end_time_item   , 2) ;
  clip_item->addSubItem(duration_item   , 3) ;

DEBUG_TRACE_NEW_CLIP_ITEM

  return clip_item ;
}

TreeViewItem* ClipsTable::newLeafItem(const String& leaf_id    , const String& key_text ,
                                      const String& value_text , const Identifier& key  ,
                                      ValueTree     clip_store                          )
{
  TreeViewItem* leaf_item = new LeafClipsTableItem(leaf_id , key_text   , value_text ,
                                                   key     , clip_store              ) ;

DEBUG_TRACE_NEW_LEAF_ITEM

  return leaf_item ;
}

void ClipsTable::createMasterItem(ValueTree& root_store , ValueTree master_store)
{
DEBUG_TRACE_CREATE_MASTER_ITEM

  TreeViewItem* root_item   = getViewItemFor(root_store.getType()) ;
  TreeViewItem* master_item = newMasterItem(master_store) ;
  int           master_idx  = root_store.indexOf(master_store) ;

  root_item->addSubItem(master_item , master_idx) ;
  storeItemId(master_store , master_item) ;

  for (int clip_n = 0 ; clip_n < master_store.getNumChildren() ; ++clip_n)
    createClipItem(root_store , master_store.getChild(clip_n)) ;

  master_item->setOpen(false) ;
}

void ClipsTable::createClipItem(ValueTree& root_store , ValueTree clip_store)
{
  TreeViewItem* root_item    = getViewItemFor(root_store.getType()) ;
  ValueTree     master_store = clip_store.getParent() ;
  int           master_idx   = root_store  .indexOf(master_store) ;
  int           clip_idx     = master_store.indexOf(clip_store  ) ;
  TreeViewItem* master_item  = root_item->getSubItem(master_idx) ;

DEBUG_TRACE_CREATE_CLIP_ITEM

  // create new master item if necessary
  if (master_item == nullptr)
  {
    master_item = newMasterItem(master_store) ;

    root_item->addSubItem(master_item , master_idx) ;
    storeItemId(master_store , master_item) ;
  }

  // create new clip item
  TreeViewItem* clip_item    = newClipItem(clip_store) ;
  int           n_properties = clip_store.getNumProperties() ;

  master_item->addSubItem(clip_item , clip_idx) ;
  storeItemId(clip_store , clip_item) ;

  // create new leaf items for user-defined metadata if necessary
  for (int property_n = 0 ; property_n < n_properties ; ++property_n)
  {
    String key = STRING(clip_store.getPropertyName(property_n)) ;

    if (!STORE::ClipPersistentKeys.contains(key) &&
        !STORE::ClipTransientKeys .contains(key)  ) createLeafItem(clip_store , key) ;
  }
}

void ClipsTable::createLeafItem(ValueTree& clip_store , const Identifier& key)
{
  String        clip_id      = STRING(clip_store.getType()) ;
  String        leaf_id      = STRING(key) ;
  String        key_text     = STRING(key) ;
  String        value_text   = STRING(clip_store[key]) ;
  String        clip_item_id = STRING(clip_store[STORE::ITEM_ID_KEY]) ;
  TreeViewItem* clip_item    = this->clipsTreeview->findItemFromIdentifierString(clip_item_id) ;

DEBUG_TRACE_CREATE_LEAF_ITEM

  if (clip_item != nullptr)
  {
    TreeViewItem* leaf_item = newLeafItem(leaf_id , key_text , value_text , key , clip_store) ;

    clip_item->addSubItem(leaf_item) ;
  }
}

void ClipsTable::destroyItem(const String& item_id)
{
  TreeViewItem* deleted_item = this->clipsTreeview->findItemFromIdentifierString(item_id) ;
  TreeViewItem* parent_item  = (deleted_item != nullptr) ? deleted_item->getParentItem()    : nullptr ;
  int           deleted_idx  = (deleted_item != nullptr) ? deleted_item->getIndexInParent() : -1 ;

DEBUG_TRACE_DESTROY_ITEM

  if (parent_item != nullptr) parent_item->removeSubItem(deleted_idx) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ClipsTable" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
  <GROUPCOMPONENT name="" id="9d12890fad74e332" memberName="compilationsGroup"
                  virtualName="" explicitFocusOrder="0" pos="50.065% 0 50.065% 0M"
                  outlinecol="ffffffff" title="Compilations" textpos="36"/>
  <GROUPCOMPONENT name="" id="b75d2d1dcc7ad9d9" memberName="clipsGroup" virtualName=""
                  explicitFocusOrder="0" pos="0 0 50.065% 0M" outlinecol="ffffffff"
                  title="Clips" textpos="36"/>
  <TREEVIEW name="" id="878b1eebd70c300c" memberName="clipsTreeview" virtualName=""
            explicitFocusOrder="0" pos="16 16 32M 32M" posRelativeX="b75d2d1dcc7ad9d9"
            posRelativeY="b75d2d1dcc7ad9d9" posRelativeW="b75d2d1dcc7ad9d9"
            posRelativeH="b75d2d1dcc7ad9d9" rootVisible="0" openByDefault="0"/>
  <TREEVIEW name="" id="72e7d9a12570ef72" memberName="compilationsTreeview"
            virtualName="" explicitFocusOrder="0" pos="16 16 32M 32M" posRelativeX="9d12890fad74e332"
            posRelativeY="9d12890fad74e332" posRelativeW="9d12890fad74e332"
            posRelativeH="9d12890fad74e332" rootVisible="0" openByDefault="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
