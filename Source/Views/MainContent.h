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


class AudioTagTooStore ;
class Statusbar ;
class Waveform ;

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  MainComponent is the top-most parent GUI container for the AudioTagToo application.
                                                                    //[/Comments]
*/
class MainContent  : public AudioAppComponent,
                     private Button::Listener,
                     private FileBrowserListener,
                     private ChangeListener,
                     private ValueTree::Listener
{
#ifndef CONTROLLER_OWNS_STORAGE
  friend class AudioTagToo ;
#endif // CONTROLLER_OWNS_STORAGE


public:
    //==============================================================================
    MainContent ();
    ~MainContent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

#ifdef CONTROLLER_OWNS_STORAGE
  void initialize(ValueTree&     clips    , ValueTree&           compilations  ,
                  NamedValueSet& features , AudioThumbnailCache& thumbnailCache) ;
#else // CONTROLLER_OWNS_STORAGE
  void initialize(NamedValueSet& features , AudioThumbnailCache& thumbnailCache) ;
#endif // CONTROLLER_OWNS_STORAGE
  void setStatusL(String statusText) ;
  void setStatusC(String statusText) ;
  void setStatusR(String statusText) ;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  WildcardFileFilter                       audioFileFilter ;
  TimeSliceThread                          workerThread ;
  FileBrowserComponent*                    fileBrowser ;
  TreeView*                                clipsTreeview ;
  std::unique_ptr<TreeViewItem>            clips ;
  TreeView*                                compilationsTreeview ;
  std::unique_ptr<TreeViewItem>            compilations ;
  String                                   projectFilename ;
  String                                   audioFilename ;
  AudioFormatManager                       formatManager ;
  AudioSourcePlayer                        audioSourcePlayer ;
  AudioTransportSource                     transportSource ;
  std::unique_ptr<AudioFormatReaderSource> audioFileSource ;
  std::vector<Waveform*>                   waveforms ;
#ifndef CONTROLLER_OWNS_STORAGE
  std::unique_ptr<AudioTagTooStore>        storage ;
#else // CONTROLLER_OWNS_STORAGE
  ValueTree                                clips ;
  ValueTree                                compilations ;
#endif // CONTROLLER_OWNS_STORAGE

  // getters/setters
  void          loadUrl              (File audio_url) ;
  void          toggleTransport      (void) ;
  void          updateTransportButton(void) ;
  void          setHeadMarker        (void) ;
  void          setTailMarker        (void) ;
  void          createClip           (void) ;
  void          createMasterItem     (ValueTree master_node) ;
  TreeViewItem* newMasterItem        (ValueTree master_node) ;
  void          createClipItem       (ValueTree master_node , ValueTree clip_node) ;
  TreeViewItem* newClipItem          (ValueTree clip_node) ;

  // event handlers
  void paintOverChildren         (Graphics& g)                                                     override ;
  void prepareToPlay             (int samples_per_block , double sample_rate)                      override ;
  void getNextAudioBlock         (const AudioSourceChannelInfo& buffer)                            override ;
  void releaseResources          (void)                                                            override ;
  void buttonClicked             (Button* a_button)                                                override ;
  void selectionChanged          (void)                                                            override ;
  void changeListenerCallback    (ChangeBroadcaster* source)                                       override ;
  void valueTreeRedirected       (ValueTree&                                                     ) override ;
  void valueTreeChildAdded       (ValueTree& parent_node , ValueTree& new_node                   ) override ;
  void valueTreeChildRemoved     (ValueTree& parent_node , ValueTree& deleted_node , int prev_idx) override ;
  void valueTreeChildOrderChanged(ValueTree& parent_node , int        prev_idx     , int curr_idx) override ;

  // unhandled ValueTree::Listener events
  void valueTreePropertyChanged(ValueTree& , const Identifier&) override {}
  void valueTreeParentChanged  (ValueTree&                    ) override {}

  // unhandled FileBrowserListener events
  void fileClicked       (const File& , const MouseEvent&) override {}
  void fileDoubleClicked (const File&                    ) override {}
  void browserRootChanged(const File&                    ) override {}


  class ClipsTreeViewItem : public TreeViewItem
  {
  public:

    ClipsTreeViewItem(String _label) : label(_label) { }

//     String     getUniqueName       () const override { return id   ; }
    bool       mightContainSubItems()       override { return true ; }
    int        getItemHeight       () const override { return 22   ; }
//     Component* createItemComponent ()       override { return new Label(id) ; }

    void paintItem(Graphics& g , int width , int height) override
    {
      g.setFont(Font(height * 0.7f , Font::bold)) ;
      g.setColour(GUI::FILENAME_FG_COLOR) ;
      g.drawText(this->label , 2 , 0 , width - 2 , height , Justification::centredLeft , true) ;
    }

    void itemOpennessChanged(bool is_open) override
    {
DBG("ClipsTreeViewItem::itemOpennessChanged()=" + String(is_open ? "is_open" : "is_closed")) ;
/*
        if (isNowOpen)
        {
            if (getNumSubItems() == 0)
                for (auto command : owner.getCommandManager().getCommandsInCategory (categoryName))
                    if (owner.shouldCommandBeIncluded (command))
                        addSubItem (new MappingItem (owner, command));
        }
        else
        {
            clearSubItems();
        }
*/
    }


  private:

    String label ;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ClipsTreeViewItem)
  } ;

    //[/UserVariables]

    //==============================================================================


    std::unique_ptr<Waveform> fullWaveform;
    std::unique_ptr<Waveform> clipWaveform;
    std::unique_ptr<GroupComponent> controlsGroup;
    std::unique_ptr<TextButton> headButton;
    std::unique_ptr<TextButton> transportButton;
    std::unique_ptr<TextButton> clipButton;
    std::unique_ptr<TextButton> tailButton;
    std::unique_ptr<TabbedComponent> tabPanel;
    std::unique_ptr<Statusbar> statusbar;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
