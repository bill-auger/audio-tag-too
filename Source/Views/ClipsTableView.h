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

#pragma once

//[Headers]     -- You can add your own extra header files here --

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Constants/GuiConstants.h"

class ValueControlledButton ;

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
class ClipsTableView  : public Component/*,
                        public ComboBox::Listener*/
{
public:
    //==============================================================================
    ClipsTableView (TreeView* treeview , const String& item_id);
    ~ClipsTableView();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
//     void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.


protected:

  virtual void showEditor(void) = 0 ; // clips and leaf nodes


  TreeView* parentTreeview ;
  String    itemId ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> labelL;
    std::unique_ptr<Label> labelR;
    std::unique_ptr<ImageButton> loadButton;
    std::unique_ptr<ImageButton> editButton;
    std::unique_ptr<ImageButton> deleteButton;
    std::unique_ptr<ValueControlledButton> addButton;
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

  MasterClipsTableView(TreeView* treeview , const String& item_id , const String& label_text) ;


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

  ClipClipsTableView(TreeView*     treeview   , const String& item_id   ,
                     const String& label_text , ValueTree     clip_store) ;
  ~ClipClipsTableView() ;


private:

  // event handlers
  void buttonClicked(Button* a_button) override ;

  // helpers
  void addMetadata(void) ;
  void showEditor (void) override ;
  void removeClip (void) ;


  ValueTree clipStore ;
} ;


/**
  LeafClipsTableView is a specialized ClipsTableView component.
  It represents individual metadata entries with buttons
    to edit the metedata value label and destroy the metedata entry.
  It is always a bottom-level (visible) child item of a ClipClipsTableView.
*/
class LeafClipsTableView : public  ClipsTableView   ,
                           private Button::Listener ,
                           private ComboBox::Listener/*
                           private Label::Listener*/
{
public:

  LeafClipsTableView(TreeView*         treeview                       ,
                     const String&     item_id                        ,
                     const String&     key_text                       ,
                     const String&     value_text                     ,
                     const Identifier& key_                           ,
                     ValueTree         clip_store = ValueTree::invalid) ;

  ~LeafClipsTableView() ;


private:

  // event handlers
  void buttonClicked  (Button* a_button)     override ;
  void comboBoxChanged(ComboBox* a_combobox) override ;
//   void labelTextChanged(Label* a_label)   override ;

  // helpers
  void resetMetadata    (void) ;
  void populateKeySelect(void) ;
  void handleComboBox   (const String& key_text) ;
  void showEditor       (void) override ;


  ValueTree  clipStore ;
  Identifier key ;
} ;


/**
  ValueControlledButton is a customized Button for the AudioTagToo application.
  It's toggled state is governed by the Value of a clip store ValueTree property;
  which is a work-around to, in turn, control it's enabled/disabled state.
*/
class ValueControlledButton : public ImageButton
{
public:

  ValueControlledButton(const String& item_id) ;

  // setup
  void initialize(Value label_storage) ;

  // event handlers
  void buttonStateChanged() override ;
} ;


/**
  ClipsTableItem is the TreeViewItem component host for the AudioTagToo application.
  It's purpose is to spawn and destroy ClipsTableView components on demand.
  This is an abstract class with three implementations:
    MasterClipsTableItem , ClipClipsTableItem, and LeafClipsTableItem
  Each subclass will spawn their corresponding ClipsTableView subclass components
    and will managed their life-cycle.
*/
class ClipsTableItem : public TreeViewItem
{
public:

  ClipsTableItem(const String& item_id , const String& label_text_l , const String& label_text_r = String::empty) ;


  // TreeViewItem implementation
  String             getUniqueName       (void) const override ;
  int                getItemHeight       (void) const override ;
  virtual bool       mightContainSubItems(void) = 0 ;
  virtual Component* createItemComponent (void) = 0 ;


protected:

  String itemId ;
  String labelTextL ;
  String labelTextR ;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ClipsTableItem)
} ;


/**
  MasterClipsTableItem is a specialized ClipsTableItem.
  It's purpose is to spawn and manage a transient MasterClipsTableView.
*/
class MasterClipsTableItem : public ClipsTableItem
{
public:

  MasterClipsTableItem(const String& item_id , const String& label_text = String::empty) ;

  bool       mightContainSubItems(void) override ;
  Component* createItemComponent (void) override ;
} ;


/**
  RootClipsTableItem is an alias for MasterClipsTableItem, merely for comvenience.
  It is the TreeView single root TreeViewItem holding any number of MasterClipsTableItems.
  It spawns no visible GUI component (per the ClipsTable constructor);
    but is nonetheless, always in the 'open' state in order to present its child
    MasterClipsTableItems views as if they were themselves (logical) tree roots.
*/
typedef MasterClipsTableItem RootClipsTableItem ;


/**
  ClipClipsTableItem is a specialized ClipsTableItem.
  It's purpose is to spawn and manage a transient ClipClipsTableView.
*/
class ClipClipsTableItem : public ClipsTableItem
{
public:

  ClipClipsTableItem(const String& item_id , const String& label_text , ValueTree clip_store) ;

  bool       mightContainSubItems(void) override ;
  Component* createItemComponent (void) override ;


private:

  ValueTree clipStore ;
} ;


/**
  LeafClipsTableItem is a specialized ClipsTableItem.
  It's purpose is to spawn and manage a transient LeafClipsTableView.
*/
class LeafClipsTableItem : public ClipsTableItem
{
public:

  LeafClipsTableItem(const String&     item_id                        ,
                     const String&     key_text                       ,
                     const String&     value_text                     ,
                     const Identifier& key_                           ,
                     ValueTree         clip_store = ValueTree::invalid) ;

  bool       mightContainSubItems(void) override ;
  Component* createItemComponent (void) override ;


private:

  ValueTree  clipStore ;
  Identifier key ;
} ;

//[/EndFile]
