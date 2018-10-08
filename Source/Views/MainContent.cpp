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

/* This class was derived from:
  ==============================================================================

   JUCE AudioPlaybackDemo v1.0.0
   Copyright (c) 2017 - ROLI Ltd.

   The code included in this file is provided under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license. Permission
   To use, copy, modify, and/or distribute this software for any purpose with or
   without fee is hereby granted provided that the above copyright notice and
   this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES,
   WHETHER EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR
   PURPOSE, ARE DISCLAIMED.

  ==============================================================================
*/


#include "../Constants/AppConstants.h"
#include "../Constants/GuiConstants.h"
#include "../Constants/MediaConstants.h"

//[/Headers]

#include "MainContent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainContent::MainContent ()
    : audioFileFilter(MEDIA::IMPORT_WAVEFILE_MASK , "*" , MEDIA::IMPORT_WAVEFILE_DESC) , directoryList(&audioFileFilter , workerThread) , workerThread(APP::WORKER_THREAD_NAME)
{
    //[Constructor_pre] You can add your own custom stuff here..

  processCliParams() ;

    //[/Constructor_pre]

    fullWaveform.reset (new Waveform (formatManager , transportSource , courseFps));
    addAndMakeVisible (fullWaveform.get());

    clipWaveform.reset (new Waveform (formatManager , transportSource , fineFps));
    addAndMakeVisible (clipWaveform.get());

    groupComponent.reset (new GroupComponent ("new group",
                                              String()));
    addAndMakeVisible (groupComponent.get());
    groupComponent->setColour (GroupComponent::outlineColourId, Colour (0x00000000));

    headButton.reset (new TextButton (String()));
    addAndMakeVisible (headButton.get());
    headButton->setButtonText (TRANS("Head"));

    transportButton.reset (new TextButton (String()));
    addAndMakeVisible (transportButton.get());
    transportButton->setButtonText (TRANS("Play"));

    tailButton.reset (new TextButton (String()));
    addAndMakeVisible (tailButton.get());
    tailButton->setButtonText (TRANS("Tail"));

    fileTree.reset (new FileTreeComponent (directoryList));
    addAndMakeVisible (fileTree.get());

    deviceSelector.reset (new AudioDeviceSelectorComponent (deviceManager , 0 , 0 , 2 , 2 , false , false , true , false));
    addAndMakeVisible (deviceSelector.get());

    statusbar.reset (new Statusbar());
    addAndMakeVisible (statusbar.get());

    //[UserPreSize]

  this->app = JUCEApplication::getInstance() ;
  this->storage.reset(new AudioTagTooStore()) ;

  this->fullWaveform->setName(GUI::FULL_WAVEFORM_ID) ;
  this->clipWaveform->setName(GUI::CLIP_WAVEFORM_ID) ;
  this->waveforms.push_back(this->fullWaveform.get()) ;
  this->waveforms.push_back(this->clipWaveform.get()) ;

  this->fileTree->setColour(FileTreeComponent::backgroundColourId , GUI::BROWSER_BG_COLOR) ;

    //[/UserPreSize]

    setSize (766, 742);


    //[Constructor] You can add your own custom stuff here..

  this->directoryList    .setDirectory(this->workingDir , true , true) ;
  this->formatManager    .registerBasicFormats() ;
  this->audioSourcePlayer.setSource(&transportSource) ;
  this->directoryList    .setDirectory(File::getSpecialLocation(File::userHomeDirectory) , true , true) ;

  this->headButton     ->addListener      (this);
  this->transportButton->addListener      (this);
  this->tailButton     ->addListener      (this);
  this->deviceManager   .addAudioCallback (&audioSourcePlayer) ;
  this->deviceManager   .addChangeListener(this) ;
  this->transportSource .addChangeListener(this) ;
  this->fileTree       ->addListener      (this) ;
  this->storage->root  ->addListener      (this) ;

  // initialize stored state
  this->storage->initialize() ;

#if ! DISABLE_MEDIA
  // start audio and worker threads
  setAudioChannels(MEDIA::N_CHANNELS_IN , MEDIA::N_CHANNELS_OUT , this->storage->deviceStateXml.get()) ;
  this->workerThread.startThread(3) ;
#endif // DISABLE_MEDIA

  setOpaque(true) ;
  setSize(GUI::WINDOW_W , GUI::WINDOW_H) ;

    //[/Constructor]
}

MainContent::~MainContent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..

  shutdownAudio() ;

  this->transportSource  .setSource(nullptr) ;
  this->audioSourcePlayer.setSource(nullptr) ;

  this->headButton     ->removeListener      (this);
  this->transportButton->removeListener      (this);
  this->tailButton     ->removeListener      (this);
  this->deviceManager   .removeAudioCallback (&audioSourcePlayer) ;
  this->deviceManager   .removeChangeListener(this) ;
  this->transportSource .removeChangeListener(this) ;
  this->fileTree       ->removeListener      (this) ;
  this->storage->root   .removeListener      (this) ;

  this->storage = nullptr ;

    //[/Destructor_pre]

    fullWaveform = nullptr;
    clipWaveform = nullptr;
    groupComponent = nullptr;
    headButton = nullptr;
    transportButton = nullptr;
    tailButton = nullptr;
    fileTree = nullptr;
    deviceSelector = nullptr;
    statusbar = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainContent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff101010));

    {
        float x = static_cast<float> ((getWidth() / 2) - ((getWidth() - 16) / 2)), y = 8.0f, width = static_cast<float> (getWidth() - 16), height = static_cast<float> (getHeight() - 56);
        Colour fillColour = Colour (0xff202020);
        Colour strokeColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 1.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainContent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    fullWaveform->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), 16, getWidth() - 32, 120);
    clipWaveform->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), 16 + 120 - -8, getWidth() - 32, 120);
    groupComponent->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), (16 + 120 - -8) + 120 - -8, getWidth() - 32, 24);
    headButton->setBounds ((getWidth() / 2) + -150 - (150 / 2), (16 + 120 - -8) + 120 - -8, 150, 24);
    transportButton->setBounds ((getWidth() / 2) - (150 / 2), (16 + 120 - -8) + 120 - -8, 150, 24);
    tailButton->setBounds ((getWidth() / 2) + 150 - (150 / 2), (16 + 120 - -8) + 120 - -8, 150, 24);
    fileTree->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), ((16 + 120 - -8) + 120 - -8) + 24 - -8, getWidth() - 32, proportionOfHeight (0.3900f));
    deviceSelector->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), ((16 + 120 - -8) + 120 - -8) + 24 - -8, getWidth() - 32, proportionOfHeight (0.3900f));
    statusbar->setBounds ((getWidth() / 2) - ((getWidth() - 16) / 2), getHeight() - 8 - 32, getWidth() - 16, 32);

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}


//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MainContent::prepareToPlay(int samples_per_block , double sample_rate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainContent::getNextAudioBlock(const AudioSourceChannelInfo& buffer)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    buffer.clearActiveBufferRegion() ;
}

void MainContent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

void MainContent::processCliParams()
{
  // load configuration options passed via command line
  StringArray cli_params = JUCEApplicationBase::getCommandLineParameterArray() ;
  int         token_idx ;
  String      string_value ;
  int         int_value ;

  bool is_valid_dir = (((token_idx    = cli_params.contains(APP::CLI_DIR_TOKEN)) > -1) &&
                       ((string_value = cli_params[token_idx + 1]).isNotEmpty()      ) &&
                       File(string_value).exists()                                      ) ;
  this->workingDir  = (is_valid_dir            ) ? File(string_value) :
                      (APP::MusicDir().exists()) ? APP::MusicDir()    : APP::HomeDir() ;

  bool is_valid_fine_fps = (((token_idx = cli_params.contains(APP::CLI_FPS_TOKEN)) > -1) &&
                            ((int_value = cli_params[token_idx + 1].getIntValue()) >  0)  ) ;
  this->courseFps        = GUI::COURSE_FPS ;
  this->fineFps          = (is_valid_fine_fps) ? int_value : GUI::FINE_FPS ;
}

void MainContent::buttonClicked(Button* a_button)
{
  if      (a_button == this->headButton     .get()) setHeadMarker() ;
  else if (a_button == this->transportButton.get()) toggleTransport() ;
  else if (a_button == this->tailButton     .get()) setTailMarker() ;
}

void MainContent::loadUrl(File audio_file)
{
  const Url          url    = Url(audio_file) ;
  AudioFormatReader* reader = nullptr ;

  this->transportSource.stop() ;
  this->transportSource.setSource(nullptr) ;
  this->audioFileSource.reset() ;

  #if ! JUCE_IOS
  if (url.isLocalFile()) reader = this->formatManager.createReaderFor(url.getLocalFile()) ;
  else
  #endif
  reader = this->formatManager.createReaderFor(url.createInputStream(false)) ;

  if (reader == nullptr) return ;

  std::unique_ptr<AudioFormatReaderSource> audio_source(new AudioFormatReaderSource(reader , true)) ;
  this->transportSource.setSource(audio_source.get() , 32768 , &workerThread , reader->sampleRate) ;
  this->audioFileSource.reset(audio_source.release()) ;
  this->audioFilename = audio_file.getFullPathName() ;

  for (Waveform* waveform : this->waveforms) { waveform->setUrl(url) ; }

  shutdownAudio() ; setAudioChannels(MEDIA::N_CHANNELS_IN , MEDIA::N_CHANNELS_OUT , this->storage->deviceStateXml.get()) ;
}

void MainContent::toggleTransport()
{
  if (this->transportSource.isPlaying()) this->transportSource.stop()  ;
  else                                   this->transportSource.start() ;
}

void MainContent::updateTransportButton()
{
  bool is_rolling = this->transportSource.isPlaying() ;

  if (!is_rolling) this->transportSource.setPosition(this->waveformLower->getHeadTime()) ;
  transportButton->setButtonText((is_rolling) ? "Stop" : "Start") ;
  transportButton->setToggleState(is_rolling , juce::dontSendNotification) ;
}

void MainContent::setHeadMarker()
{
  for (Waveform* waveform : this->waveforms) { waveform->setHeadMarker() ; }
}

void MainContent::setTailMarker()
{
  for (Waveform* waveform : this->waveforms) waveform->setTailMarker() ;
  if (!this->transportSource.isPlaying())
    for (Waveform* waveform : this->waveforms) waveform->resetPosition() ;
}

void MainContent::selectionChanged() { loadUrl(this->fileTree->getSelectedFile()) ; }

void MainContent::changeListenerCallback(ChangeBroadcaster* source)
{
  if      (source == &(this->transportSource)) updateTransportButton() ;
  else if (source == &(this->deviceManager  ))
  {
    bool is_device_initialized = this->deviceManager.getCurrentAudioDevice() != nullptr ;

    if (is_device_initialized) this->storage->storeConfig(this->deviceManager.createStateXml()) ;
    else AlertWindow::showMessageBox(AlertWindow::WarningIcon , GUI::DEVICE_ERROR_TITLE ,
                                                                GUI::DEVICE_ERROR_MSG   ) ;
    this->fileTree      ->setVisible( is_device_initialized) ;
    this->deviceSelector->setVisible(!is_device_initialized) ;
  }
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainContent" componentName=""
                 parentClasses="public AudioAppComponent, private Button::Listener, private FileBrowserListener, private ChangeListener, private ValueTree::Listener"
                 constructorParams="" variableInitialisers="audioFileFilter(MEDIA::IMPORT_WAVEFILE_MASK , &quot;*&quot; , MEDIA::IMPORT_WAVEFILE_DESC) , directoryList(&amp;audioFileFilter , workerThread) , workerThread(APP::WORKER_THREAD_NAME)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="766" initialHeight="742">
  <BACKGROUND backgroundColour="ff101010">
    <ROUNDRECT pos="0Cc 8 16M 56M" cornerSize="10.00000000000000000000" fill="solid: ff202020"
               hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <GENERICCOMPONENT name="" id="6d2236e7e917afa4" memberName="fullWaveform" virtualName=""
                    explicitFocusOrder="0" pos="0.5Cc 16 32M 120" class="Waveform"
                    params="formatManager , transportSource , courseFps"/>
  <GENERICCOMPONENT name="" id="f967fc403ed73574" memberName="clipWaveform" virtualName=""
                    explicitFocusOrder="0" pos="0.5Cc -8R 32M 120" posRelativeY="6d2236e7e917afa4"
                    class="Waveform" params="formatManager , transportSource , fineFps"/>
  <GROUPCOMPONENT name="new group" id="f42caa46057f2a0" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="0.5Cc -8R 32M 24"
                  posRelativeY="f967fc403ed73574" outlinecol="0" title=""/>
  <TEXTBUTTON name="" id="9953692c678b8d85" memberName="headButton" virtualName=""
              explicitFocusOrder="0" pos="-150Cc -8R 150 24" posRelativeY="f967fc403ed73574"
              buttonText="Head" connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="" id="d6f37465bfb799aa" memberName="transportButton" virtualName=""
              explicitFocusOrder="0" pos="0Cc -8R 150 24" posRelativeY="f967fc403ed73574"
              buttonText="Play" connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="" id="306d8525bb18da83" memberName="tailButton" virtualName=""
              explicitFocusOrder="0" pos="150Cc -8R 150 24" posRelativeY="f967fc403ed73574"
              buttonText="Tail" connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <GENERICCOMPONENT name="" id="230286b07ddaa9d7" memberName="fileTree" virtualName=""
                    explicitFocusOrder="0" pos="0.5Cc -8R 32M 39.000%" posRelativeY="f42caa46057f2a0"
                    class="FileTreeComponent" params="directoryList"/>
  <GENERICCOMPONENT name="" id="fa801866cc59e27a" memberName="deviceSelector" virtualName=""
                    explicitFocusOrder="0" pos="0.5Cc -8R 32M 39.000%" posRelativeY="f42caa46057f2a0"
                    class="AudioDeviceSelectorComponent" params="deviceManager , 0 , 0 , 2 , 2 , false , false , true , false"/>
  <GENERICCOMPONENT name="" id="957b301f5907e647" memberName="statusbar"
                    virtualName="" explicitFocusOrder="0" pos="0.5Cc 8Rr 16M 32"
                    class="Statusbar" params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
