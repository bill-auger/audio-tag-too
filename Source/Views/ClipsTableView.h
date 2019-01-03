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


#pragma once

//[Headers]     -- You can add your own extra header files here --

#include "../../JuceLibraryCode/JuceHeader.h"

#include "../Constants/GuiConstants.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  ClipsTableView is the TreeViewItem component for the AudioTagToo application.
  This is an abstract class with three implementations:
    MasterClipsTableView, ClipClipsTableView, and LeafClipsTableView
  Subclass constructors are called by their corresponding ClipsTableItem subclass constructors.
                                                                    //[/Comments]
*/
class ClipsTableView  : public Component,
                        public ComboBox::Listener
{
public:
    //==============================================================================
    ClipsTableView ();
    ~ClipsTableView();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.


protected:

  virtual void showEditor(void) = 0 ; // clips and leaf nodes

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> labelL;
    std::unique_ptr<Label> labelR;
    std::unique_ptr<ImageButton> loadButton;
    std::unique_ptr<ImageButton> editButton;
    std::unique_ptr<ImageButton> deleteButton;
    std::unique_ptr<ImageButton> addButton;
    std::unique_ptr<ComboBox> keySelect;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ClipsTableView)
};

//[EndFile] You can add extra defines here...

/**
  MasterClipsTableView is a specialized ClipsTableView component.
  It represents a source audio file from which clips are created.
  It is always a top-level (hidden) root item containing a MasterClipsTableView or
    that top-level (visible) item containing any numbre of ClipClipsTableViews
    and their respective LeafClipsTableViews.
*/
class MasterClipsTableView : public ClipsTableView
{
public:

  MasterClipsTableView(String label_text) ;


private:

  void showEditor(void) override { }
} ;


/**
  ClipClipsTableView is a specialized ClipsTableView component.
  It represents individual audio segment clip entries with buttons
    to load the clip into the GUI, edit it's friendly name label, add metedata
    edit metedata, and destroy the clip entry.
  It is always a child of a top-level (visible) MasterClipsTableView item
    and contains LeafClipsTableViews for the associated metadata.
  It will always contain LeafClipsTableViews for each in
    the basic set of metadata items as denoted in GUI::MetadataLabels().
*/
class ClipClipsTableView : public ClipsTableView    ,
                           private Button::Listener
{
public:

  ClipClipsTableView(String label_text , ValueTree store_) ;
  ~ClipClipsTableView() ;


private:

  // event handlers
  void buttonClicked(Button* a_button) override ;

  // helpers
  void showEditor (void) override ;
  void removeClip (void) ;
  void setMetadata(void) ;


  ValueTree store ;
} ;


/**
  LeafClipsTableView is a specialized ClipsTableView component.
  It represents individual metadata entries with buttons
    to edit the metedata value label and destroy the metedata entry.
  It is always a bottom-level (visible) child item of a ClipClipsTableView.
*/
class LeafClipsTableView : public  ClipsTableView   ,
                           private Button::Listener/* ,
                           private Label::Listener*/
{
public:

  LeafClipsTableView(String     key_text                      ,
                     String     value_text                    ,
                     Identifier key_   = Identifier("unused") ,
                     ValueTree  store_ = ValueTree::invalid   ) ;

  ~LeafClipsTableView() ;


private:

  // event handlers
  void buttonClicked   (Button* a_button) override ;
//   void labelTextChanged(Label* a_label)   override ;

  // helpers
  void showEditor       (void) override ;
  void resetMetadata    (void) ;
  void populateKeySelect(void) ;

  ValueTree  store ;
  Identifier key ;
} ;



/**
  ClipsTableItem is the TreeViewItem place-holder component for the AudioTagToo application.
  It's purpose is to spawn and destroy ClipsTableView components on demand.
  This is an abstract class with three implementations:
    MasterClipsTableItem , ClipClipsTableItem, and LeafClipsTableItem
  Each subclass will spawn their corresponding ClipsTableView subclass components
    and will managed their life-cycle.
*/
class ClipsTableItem : public TreeViewItem
{
public:

  ClipsTableItem(String item_id , String label_text_l , String label_text_r = String::empty) ;


  // TreeViewItem implementation
  String             getUniqueName       (void) const override ;
  int                getItemHeight       (void) const override ;
  virtual bool       mightContainSubItems(void) = 0 ;
  virtual Component* createItemComponent (void) = 0 ;

  // helpers
  ClipsTableView* setId(ClipsTableView* new_view) ;


protected:

  String itemId ;
  String labelTextL ;
  String labelTextR ;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ClipsTableItem)
} ;


/**
  MasterClipsTableItem is a specialized ClipsTableItem component.
  It's purpose is to spawn and manage a transient MasterClipsTableView.
*/
class MasterClipsTableItem : public ClipsTableItem
{
public:

  MasterClipsTableItem(String item_id , String label_text = String::empty) ;

  bool       mightContainSubItems(void) override ;
  Component* createItemComponent (void) override ;
} ;


/**
  RootClipsTableItem is an alias for MasterClipsTableItem, merely for comvenience.
  It is the TreeView single root TreeViewItem holding any number of MasterClipsTableItem components.
  It is not itself a visible GUI component (per the ClipsTable constructor);
    but is nonetheless, always in the 'open' state in order to present its child components
    as if they were themselves (logical) tree roots.
*/
typedef MasterClipsTableItem RootClipsTableItem ;


/**
  ClipClipsTableItem is a specialized ClipsTableItem component.
  It's purpose is to spawn and manage a transient ClipClipsTableView.
*/
class ClipClipsTableItem : public ClipsTableItem
{
public:

  ClipClipsTableItem(String item_id , String label_text , ValueTree store) ;

  bool       mightContainSubItems(void) override ;
  Component* createItemComponent (void) override ;


private:

  ValueTree store ;
} ;


/**
  LeafClipsTableItem is a specialized ClipsTableItem component.
  It's purpose is to spawn and manage a transient LeafClipsTableView.
*/
class LeafClipsTableItem : public ClipsTableItem
{
public:

  LeafClipsTableItem(String     item_id                       ,
                     String     key_text                      ,
                     String     value_text                    ,
                     Identifier key_   = Identifier("unused") ,
                     ValueTree  store_ = ValueTree::invalid   ) ;

  bool       mightContainSubItems(void) override ;
  Component* createItemComponent (void) override ;


private:

  ValueTree  store ;
  Identifier key ;
} ;

//[/EndFile]
