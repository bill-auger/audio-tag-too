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

  this->clipsStore       .removeListener(this) ;
  this->compilationsStore.removeListener(this) ;

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
  bool is_initialized = this->clipsStore.isValid() || this->compilationsStore.isValid() ;

  if (!is_initialized)
  {
    createItemsTree(this->clipsStore        = clips_store       ) ;
    createItemsTree(this->compilationsStore = compilations_store) ;

    this->clipsStore       .addListener(this) ;
    this->compilationsStore.addListener(this) ;
  }

  is_initialized = this->clipsStore.isValid() || this->compilationsStore.isValid() ;

  return is_initialized ;
}


/* ClipsTable private instance methods */

/* model helpers */

void ClipsTable::storeItemId(TreeViewItem* an_item , ValueTree a_store)
{
  String item_id = an_item->getItemIdentifierString() ;

  a_store.setProperty(STORE::ITEM_ID_KEY , var(item_id) , nullptr) ;
}

TreeViewItem* ClipsTable::getViewItemFor(ValueTree& root_store)
{
  return (root_store == this->clipsStore       ) ? this->clipItems.get()        :
         (root_store == this->compilationsStore) ? this->compilationItems.get() : nullptr ;
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
  TreeViewItem* root_item   = getViewItemFor(root_store) ;
  TreeViewItem* master_item = newMasterItem(master_store) ;
  int           master_idx  = root_store.indexOf(master_store) ;

  root_item->addSubItem(master_item , master_idx) ;
  storeItemId(master_item , master_store) ;

DEBUG_TRACE_CREATE_MASTER_ITEM

  for (int clip_n = 0 ; clip_n < master_store.getNumChildren() ; ++clip_n)
    createClipItem(root_store , master_store.getChild(clip_n)) ;
}

void ClipsTable::createClipItem(ValueTree& root_store , ValueTree clip_store)
{
  TreeViewItem* root_item              = getViewItemFor(root_store) ;
  ValueTree     master_store           = clip_store.getParent() ;
  int           master_idx             = root_store.indexOf(master_store) ;
  int           clip_idx               = master_store.indexOf(clip_store) ;
  TreeViewItem* master_item            = root_item->getSubItem(master_idx) ;
  TreeViewItem* clip_item              = newClipItem(clip_store) ;
  bool          does_master_item_exist = master_item != nullptr ;

  if (!does_master_item_exist)
  {
    master_item = newMasterItem(master_store) ;

    root_item->addSubItem(master_item , master_idx) ;
    storeItemId(master_item , master_store) ;
  }

  master_item->addSubItem(clip_item , clip_idx) ;
  storeItemId(clip_item , clip_store) ;

DEBUG_TRACE_CREATE_CLIP_ITEM
}

void ClipsTable::createLeafItem(ValueTree& clip_store , const Identifier& key)
{
  String        clip_id      = STRING(clip_store.getType()) ;
  String        leaf_id      = STRING(key) ;
  String        key_text     = STRING(key) ;
  String        value_text   = STRING(clip_store[key]) ;
  TreeViewItem* leaf_item    = newLeafItem(leaf_id , key_text , value_text , key , clip_store) ;
  String        clip_item_id = STRING(clip_store[STORE::ITEM_ID_KEY]) ;
  TreeViewItem* clip_item    = this->clipsTreeview->findItemFromIdentifierString(clip_item_id) ;

DEBUG_TRACE_CREATE_LEAF_ITEM

  if (clip_item != nullptr) clip_item->addSubItem(leaf_item , 0) ;
}

void ClipsTable::createItemsTree(ValueTree& root_store)
{
DEBUG_TRACE_INIT_STORAGE(root_store)

  for (int master_n = 0 ; master_n < root_store.getNumChildren() ; ++master_n)
    createMasterItem(root_store , root_store.getChild(master_n)) ;
}


/* event handlers */

void ClipsTable::valueTreeChildAdded(ValueTree& parent_node , ValueTree& new_node)
{
/*
  const StringArray STORE::CLIPS_STORES    = StringArray::fromLines(STORE::CLIPS_ID        + newLine +
                                                                    STORE::COMPILATIONS_ID           ) ;
  bool is_master_node = STORE::CLIPS_STORES.contains(parent_node            .getType()) ;
  bool is_clip_node   = STORE::CLIPS_STORES.contains(parent_node.getParent().getType()) ;
*/

  bool      is_master_node = parent_node             == this->clipsStore       ||
                             parent_node             == this->compilationsStore ;
  bool      is_clip_node   = parent_node.getParent() == this->clipsStore       ||
                             parent_node.getParent() == this->compilationsStore ;
  ValueTree root_node      = (is_master_node) ? parent_node             :
                             (is_clip_node  ) ? parent_node.getParent() : ValueTree::invalid ;

DEBUG_TRACE_STORAGE_CHILD_ADDED

  if      (is_master_node) createMasterItem(root_node , new_node) ;
  else if (is_clip_node  ) createClipItem  (root_node , new_node) ;
}

void ClipsTable::valueTreeChildOrderChanged(ValueTree& parent_node , int prev_idx , int curr_idx)
{
DBG("ClipsTable::valueTreeChildOrderChanged() parent_node=" + parent_node.getType() + " prev_idx=" + String(prev_idx) + " curr_idx=" + String(curr_idx)) ;
  // TODO:
}

void ClipsTable::valueTreeChildRemoved(ValueTree& parent_node , ValueTree& deleted_node ,
                                       int        prev_idx                              )
{
  String        item_id      = STRING(deleted_node[STORE::ITEM_ID_KEY]) ;
  TreeViewItem* deleted_item = this->clipsTreeview->findItemFromIdentifierString(item_id) ;
  TreeViewItem* parent_item  = (deleted_item != nullptr) ? deleted_item->getParentItem()    : nullptr ;
  int           deleted_idx  = (deleted_item != nullptr) ? deleted_item->getIndexInParent() : -1 ;

DEBUG_TRACE_STORAGE_CHILD_REMOVED

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
                 parentClasses="public Component, public ValueTree::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
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
