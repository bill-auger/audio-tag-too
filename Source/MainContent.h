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

#include "../JuceLibraryCode/JuceHeader.h"
#include "Background.h"
#include "Statusbar.h"
#include "Waveform.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainContent  : public AudioAppComponent,
                     private FileBrowserListener,
                     private ChangeListener,
                     public Button::Listener
{
public:
    //==============================================================================
    MainContent ();
    ~MainContent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    void prepareToPlay    (int samples_per_block , double sample_rate) override ;
    void getNextAudioBlock(const AudioSourceChannelInfo& buffer)       override ;
    void releaseResources (void)                                       override ;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  AudioFormatManager                       formatManager ;
  TimeSliceThread                          thread { "audio-preview" } ;

  DirectoryContentsList                    directoryList { nullptr , thread } ;
  URL                                      currentAudioFile ;
  AudioSourcePlayer                        audioSourcePlayer ;
  AudioTransportSource                     transportSource ;
  std::unique_ptr<AudioFormatReaderSource> currentAudioFileSource ;

  void showAudioResource    (URL resource) ;
  bool loadURLIntoTransport (const URL& audio_url) ;
  void toggleFollowTransport(void) ;
  void toggleTransport      (void) ;
  void updateTransportButton(bool is_rolling) ;
  void setHeadMarker        (void) ;
  void setTailMarker        (void) ;

  void selectionChanged      (void)                      override  ;
  void changeListenerCallback(ChangeBroadcaster* source) override  ;

  // unhandled FileBrowserListener events
  void fileClicked       (const File&, const MouseEvent&) override {}
  void fileDoubleClicked (const File&)                    override {}
  void browserRootChanged(const File&)                    override {}

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Background> background;
    std::unique_ptr<Waveform> waveformUpper;
    std::unique_ptr<Waveform> waveformLower;
    std::unique_ptr<ToggleButton> followButton;
    std::unique_ptr<TextButton> headButton;
    std::unique_ptr<TextButton> transportButton;
    std::unique_ptr<TextButton> tailButton;
    std::unique_ptr<FileTreeComponent> fileTree;
    std::unique_ptr<Statusbar> statusbar;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
