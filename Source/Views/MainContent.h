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
class ClipsTable ;
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
                     private ChangeListener
{
public:
    //==============================================================================
    MainContent ();
    ~MainContent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  // setup/teardown
#ifdef CONTROLLER_OWNS_STORAGE
  bool initialize(ValueTree&     clips    , ValueTree&           compilations  ,
                  NamedValueSet& features , AudioThumbnailCache& thumbnailCache) ;
#else // CONTROLLER_OWNS_STORAGE
  void initialize(NamedValueSet& features , AudioThumbnailCache& thumbnailCache) ;
#endif // CONTROLLER_OWNS_STORAGE

  // getters/setters
  void setPosition  (double time) ;
  void setHeadMarker(void) ;
  void setTailMarker(void) ;

  // helpers
  void loadUrl              (File audio_url) ;
  void updateTransportButton(void) ;
  void createMasterItem     (ValueTree& root_store , ValueTree master_store) ;
  void createClipItem       (ValueTree& root_store , ValueTree clip_store) ;
  void destroyItem          (const String& item_id) ;
  void createMetadata       (ValueTree& clip_store , const Identifier& key) ;
  void setStatusL           (String statusText) ;
  void setStatusC           (String statusText) ;
  void setStatusR           (String statusText) ;
  void setStatus            (void) ;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  WildcardFileFilter                       audioFileFilter ;
  TimeSliceThread                          workerThread ;
  FileBrowserComponent*                    fileBrowser ;
  ClipsTable*                              clipsTable ;
  String                                   projectFilename ;
  String                                   audioFilename ;
  AudioFormatManager                       formatManager ;
  AudioSourcePlayer                        audioSourcePlayer ;
  AudioTransportSource                     transportSource ;
  std::unique_ptr<AudioFormatReaderSource> audioFileSource ;
  std::vector<Waveform*>                   waveforms ;
#ifndef CONTROLLER_OWNS_STORAGE
  std::unique_ptr<AudioTagTooStore>        storage ;
#endif // CONTROLLER_OWNS_STORAGE

  // getters/setters
  void createClip(void) ;

  // helpers
  void toggleTransport(void) ;

  // event handlers
  void paintOverChildren     (Graphics& g)                                override ;
  void prepareToPlay         (int samples_per_block , double sample_rate) override ;
  void getNextAudioBlock     (const AudioSourceChannelInfo& buffer)       override ;
  void releaseResources      (void)                                       override ;
  void buttonClicked         (Button* a_button)                           override ;
  void selectionChanged      (void)                                       override ;
  void changeListenerCallback(ChangeBroadcaster* source)                  override ;

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
