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
#include "JuceBoilerplateStore.h"
#include "Statusbar.h"
#include "Waveform.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  MainComponent is the top-most parent GUI container for the JuceBoilerplate application.
                                                                    //[/Comments]
*/
class MainContent  : public AudioAppComponent,
                     private Button::Listener,
                     private FileBrowserListener,
                     private ChangeListener,
                     private ValueTree::Listener
{
public:
    //==============================================================================
    MainContent ();
    ~MainContent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    JUCEApplication* app ;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  AudioFormatManager                       formatManager ;
  TimeSliceThread                          thread { "audio-preview" } ;
  DirectoryContentsList                    directoryList { nullptr , thread } ;
  URL                                      currentAudioFile ;
  AudioSourcePlayer                        audioSourcePlayer ;
  AudioTransportSource                     transportSource ;
  std::unique_ptr<AudioFormatReaderSource> currentAudioFileSource ;
  std::unique_ptr<JuceBoilerplateStore>    storage ;

  // getters/setters
  void showAudioResource    (URL resource) ;
  bool loadURLIntoTransport (const URL& audio_url) ;
  void toggleFollowTransport(void) ;
  void toggleTransport      (void) ;
  void updateTransportButton(bool is_rolling) ;
  void setHeadMarker        (void) ;
  void setTailMarker        (void) ;

  // event handlers
  void prepareToPlay         (int samples_per_block , double sample_rate) override ;
  void getNextAudioBlock     (const AudioSourceChannelInfo& buffer)       override ;
  void releaseResources      (void)                                       override ;
  void buttonClicked         (Button* a_button)                           override ;
  void selectionChanged      (void)                                       override ;
  void changeListenerCallback(ChangeBroadcaster* source)                  override ;

  // unhandled ValueTree::Listener events
  void valueTreeRedirected       (ValueTree&                                                     ) override {}
  void valueTreeChildAdded       (ValueTree& parent_node , ValueTree& new_node                   ) override {}
  void valueTreeChildRemoved     (ValueTree& parent_node , ValueTree& deleted_node , int prev_idx) override {}
  void valueTreeChildOrderChanged(ValueTree& parent_node , int        prev_idx     , int curr_idx) override {}
  void valueTreePropertyChanged  (ValueTree& , const Identifier&                                 ) override {}
  void valueTreeParentChanged    (ValueTree&                                                     ) override {}

  // unhandled FileBrowserListener events
  void fileClicked       (const File&, const MouseEvent&) override {}
  void fileDoubleClicked (const File&)                    override {}
  void browserRootChanged(const File&)                    override {}

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Waveform> waveformUpper;
    std::unique_ptr<Waveform> waveformLower;
    std::unique_ptr<ToggleButton> followButton;
    std::unique_ptr<TextButton> headButton;
    std::unique_ptr<TextButton> transportButton;
    std::unique_ptr<TextButton> tailButton;
    std::unique_ptr<FileTreeComponent> fileTree;
    std::unique_ptr<AudioDeviceSelectorComponent> deviceSelector;
    std::unique_ptr<Statusbar> statusbar;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
