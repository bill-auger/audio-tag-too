/*\
|*|  JuceBoilerplate - JUCE boilerplate audio player GUI application
|*|  Copyright 2018 bill-auger <https://github.com/bill-auger/juce-boilerplate/issues>
|*|
|*|  This file is part of the JuceBoilerplate program.
|*|
|*|  JuceBoilerplate is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU General Public License as published by
|*|  the Free Software Foundation, either version 3 of the License, or
|*|  (at your option) any later version.
|*|
|*|  JuceBoilerplate is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU General Public License for more details.
|*|
|*|  You should have received a copy of the GNU General Public License
|*|  along with JuceBoilerplate.  If not, see <http://www.gnu.org/licenses/>.
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
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  WildcardFileFilter                       audioFileFilter ;
  AudioFormatManager                       formatManager ;
  TimeSliceThread                          workerThread ;
  DirectoryContentsList                    directoryList ;
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
    std::unique_ptr<Waveform> upperWaveform;
    std::unique_ptr<Waveform> lowerWaveform;
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
