/*\
|*|  AudioTagToo - Clip and stitch audio samples
|*|  Copyright 2018 bill-auger <https://github.com/bill-auger/audio-tag-too/issues>
|*|
|*|  This file is part of the AudioTagToo program.
|*|
|*|  AudioTagToo is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU General Public License version 3
|*|  as published by the Free Software Foundation.
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
#include "../Models/AudioTagTooStore.h"
#include "ClipsTable.h"
#include "Statusbar.h"
#include "Waveform.h"

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
                     private ChangeListener
{
public:
    //==============================================================================
    MainContent ();
    ~MainContent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  JUCEApplication* app ;


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
  ClipsTable*                              clipsTable ;
  File                                     workingDir ;
  String                                   projectFilename ;
  String                                   audioFilename ;
  AudioFormatManager                       formatManager ;
  AudioSourcePlayer                        audioSourcePlayer ;
  AudioTransportSource                     transportSource ;
  std::unique_ptr<AudioFormatReaderSource> audioFileSource ;
  std::unique_ptr<AudioTagTooStore>        storage ;
  std::vector<Waveform*>                   waveforms ;
  uint8                                    courseFps ;
  uint8                                    fineFps ;

  // getters/setters
  void processCliParams     () ;
  void loadUrl              (File audio_url) ;
  void toggleTransport      (void) ;
  void updateTransportButton(void) ;
  void setHeadMarker        (void) ;
  void setTailMarker        (void) ;
  void createClip           (void) ;

  // event handlers
  void paintOverChildren         (Graphics& g)                                                     override ;
  void prepareToPlay             (int samples_per_block , double sample_rate)                      override ;
  void getNextAudioBlock         (const AudioSourceChannelInfo& buffer)                            override ;
  void releaseResources          (void)                                                            override ;
  void buttonClicked             (Button* a_button)                                                override ;
  void selectionChanged          (void)                                                            override ;
  void changeListenerCallback    (ChangeBroadcaster* source)                                       override ;

  // unhandled FileBrowserListener events
  void fileClicked       (const File& , const MouseEvent&) override { }
  void fileDoubleClicked (const File&                    ) override { }
  void browserRootChanged(const File&                    ) override { }

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
