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
#include "../Controllers/JuceBoilerplate.h"
#ifdef CONTROLLER_OWNS_STORAGE
#include "../Models/JuceBoilerplateStore.h"
#endif // CONTROLLER_OWNS_STORAGE
#include "Statusbar.h"
#include "Waveform.h"

//[/Headers]

#include "MainContent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainContent::MainContent ()
    : audioFileFilter(MEDIA::IMPORT_WAVEFILE_MASK , String("*") , MEDIA::IMPORT_WAVEFILE_DESC) , directoryList(&audioFileFilter , workerThread) , workerThread(APP::WORKER_THREAD_NAME)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    upperWaveform.reset (new Waveform (transportSource));
    addAndMakeVisible (upperWaveform.get());

    lowerWaveform.reset (new Waveform (transportSource));
    addAndMakeVisible (lowerWaveform.get());

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
    statusbar->setName ("statusbar");


    //[UserPreSize]

#ifndef CONTROLLER_OWNS_STORAGE
  this->storage.reset(new JuceBoilerplateStore()) ;
#endif // CONTROLLER_OWNS_STORAGE

  this->upperWaveform->setName(GUI::UPPER_WAVEFORM_ID) ;
  this->lowerWaveform->setName(GUI::LOWER_WAVEFORM_ID) ;
  this->waveforms.push_back(this->upperWaveform.get()) ;
  this->waveforms.push_back(this->lowerWaveform.get()) ;

  this->fileTree->setColour(FileTreeComponent::backgroundColourId , GUI::BROWSER_BG_COLOR) ;

    //[/UserPreSize]

    setSize (766, 742);


    //[Constructor] You can add your own custom stuff here..

  this->formatManager    .registerBasicFormats() ;
  this->audioSourcePlayer.setSource(&transportSource) ;
  this->directoryList    .setDirectory(File::getSpecialLocation(File::userHomeDirectory) , true , true) ;

  this->headButton     ->addListener      (this);
  this->transportButton->addListener      (this);
  this->tailButton     ->addListener      (this);
  this->deviceManager   .addAudioCallback (&audioSourcePlayer) ;
  this->deviceManager   .addChangeListener(this) ;
#ifndef CONTROLLER_OWNS_STORAGE
  this->deviceManager   .addChangeListener(this->storage.get()) ;
#endif // CONTROLLER_OWNS_STORAGE
  this->lowerWaveform  ->addChangeListener(this) ;
  this->transportSource .addChangeListener(this) ;
  this->fileTree       ->addListener      (this) ;
#ifndef CONTROLLER_OWNS_STORAGE
  this->storage->root   .addListener      (this) ;
#endif // CONTROLLER_OWNS_STORAGE

  setOpaque(true) ;
  setSize(GUI::WINDOW_W , GUI::WINDOW_H) ;

    //[/Constructor]
}

MainContent::~MainContent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..

  this->transportSource  .setSource(nullptr) ;
  this->audioSourcePlayer.setSource(nullptr) ;

  this->headButton     ->removeListener      (this) ;
  this->transportButton->removeListener      (this) ;
  this->tailButton     ->removeListener      (this) ;
  this->deviceManager  .removeAudioCallback  (&audioSourcePlayer) ;
  this->deviceManager  .removeChangeListener (this) ;
#ifndef CONTROLLER_OWNS_STORAGE
  this->deviceManager  .removeChangeListener (this->storage.get()) ;
#else // CONTROLLER_OWNS_STORAGE
  if (JuceBoilerplate::IsInitialized)
  this->deviceManager  .removeChangeListener (JuceBoilerplate::Store.get()) ;
#endif // CONTROLLER_OWNS_STORAGE
  this->lowerWaveform  ->removeChangeListener(this) ;
  this->transportSource .removeChangeListener(this) ;
  this->lowerWaveform  ->removeChangeListener(this) ;
  this->fileTree       ->removeListener      (this) ;
#ifndef CONTROLLER_OWNS_STORAGE
  this->storage->root   .removeListener      (this) ;

  this->storage = nullptr ;
#else // CONTROLLER_OWNS_STORAGE
  if (JuceBoilerplate::IsInitialized)
  this->storage         .removeListener      (this) ;
#endif // CONTROLLER_OWNS_STORAGE

    //[/Destructor_pre]

    upperWaveform = nullptr;
    lowerWaveform = nullptr;
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
        float x = static_cast<float> ((getWidth() / 2) - ((getWidth() - 16) / 2)), y = 8.0f, width = static_cast<float> (getWidth() - 16), height = static_cast<float> (getHeight() - 64);
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

    upperWaveform->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), 16, getWidth() - 32, 120);
    lowerWaveform->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), 16 + 120 - -8, getWidth() - 32, 120);
    groupComponent->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), (16 + 120 - -8) + 120 - -8, getWidth() - 32, 24);
    headButton->setBounds ((getWidth() / 2) + -150 - (150 / 2), (16 + 120 - -8) + 120 - -8, 150, 24);
    transportButton->setBounds ((getWidth() / 2) - (150 / 2), (16 + 120 - -8) + 120 - -8, 150, 24);
    tailButton->setBounds ((getWidth() / 2) + 150 - (150 / 2), (16 + 120 - -8) + 120 - -8, 150, 24);
    fileTree->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), ((16 + 120 - -8) + 120 - -8) + 24 - -8, getWidth() - 32, proportionOfHeight (0.3901f));
    deviceSelector->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), ((16 + 120 - -8) + 120 - -8) + 24 - -8, getWidth() - 32, proportionOfHeight (0.3901f));
    statusbar->setBounds ((getWidth() / 2) - ((getWidth() - 16) / 2), getHeight() - 8 - 32, getWidth() - 16, 32);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}


//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* setup/teardown */

#ifdef CONTROLLER_OWNS_STORAGE
void MainContent::initialize(ValueTree&           storage         , NamedValueSet& features ,
                             AudioThumbnailCache& thumbnail_cache                           )
{
  this->storage           = storage ;
#else // CONTROLLER_OWNS_STORAGE
void MainContent::initialize(NamedValueSet& features , AudioThumbnailCache& thumbnail_cache)
{
#endif // CONTROLLER_OWNS_STORAGE
  bool   is_audio_enabled = bool  (features[APP::AUDIO_KEY     ]) ;
  String initial_dir      = STRING(features[APP::INIT_DIR_KEY  ]) ;
  int    course_fps       = int   (features[APP::COURSE_FPS_KEY]) ;
  int    fine_fps         = int   (features[APP::FINE_FPS_KEY  ]) ;
  double zoom_factor      = double(features[APP::ZOOM_KEY      ]) ;

#if ! DISABLE_AUDIO
  if (is_audio_enabled) this->workerThread.startThread(3) ;
#endif // DISABLE_AUDIO

  this->directoryList .setDirectory(File(initial_dir) , true , true) ;
  this->lowerWaveform->setZoomFactor(zoom_factor) ;

#ifdef CONTROLLER_OWNS_STORAGE
  this->deviceManager.addChangeListener(JuceBoilerplate::Store.get()) ;
  this->storage      .addListener      (this) ;
#else // CONTROLLER_OWNS_STORAGE
  this->storage->root.addListener      (this) ;
#endif // CONTROLLER_OWNS_STORAGE

  this->upperWaveform->startTimerHz(course_fps) ;
  this->lowerWaveform->startTimerHz(fine_fps  ) ;
}


/* getters/setters */

void MainContent::setStatusL(String statusText) { this->statusbar->setStatusL(statusText) ; }

void MainContent::setStatusC(String statusText) { this->statusbar->setStatusC(statusText) ; }

void MainContent::setStatusR(String statusText) { this->statusbar->setStatusR(statusText) ; }

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

  JuceBoilerplate::ResetAudio() ;
}

void MainContent::toggleTransport()
{
  if (this->transportSource.isPlaying()) this->transportSource.stop()  ;
  else                                   this->transportSource.start() ;
}

void MainContent::updateTransportButton()
{
  bool is_rolling = this->transportSource.isPlaying() ;

  if (!is_rolling) this->transportSource.setPosition(this->lowerWaveform->getHeadTime()) ;
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

/* event handlers */

void MainContent::prepareToPlay (int samplesPerBlockExpected, double sampleRate) { }

void MainContent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) { }

void MainContent::releaseResources() { }

void MainContent::buttonClicked(Button* a_button)
{
  if      (a_button == this->headButton     .get()) setHeadMarker() ;
  else if (a_button == this->transportButton.get()) toggleTransport() ;
  else if (a_button == this->tailButton     .get()) setTailMarker() ;
}

void MainContent::selectionChanged() { loadUrl(this->fileTree->getSelectedFile()) ; }

void MainContent::changeListenerCallback(ChangeBroadcaster* source)
{
  if      (source == &(this->transportSource)) updateTransportButton() ;
  else if (source == &(this->deviceManager  ))
  {
    bool is_device_initialized = this->deviceManager.getCurrentAudioDevice() != nullptr ;

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
                 constructorParams="" variableInitialisers="audioFileFilter(MEDIA::IMPORT_WAVEFILE_MASK , String(&quot;*&quot;) , MEDIA::IMPORT_WAVEFILE_DESC) , directoryList(&amp;audioFileFilter , workerThread) , workerThread(APP::WORKER_THREAD_NAME)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="766" initialHeight="742">
  <BACKGROUND backgroundColour="ff101010">
    <ROUNDRECT pos="0Cc 8 16M 56M" cornerSize="10.00000000000000000000" fill="solid: ff202020"
               hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <GENERICCOMPONENT name="" id="6d2236e7e917afa4" memberName="upperWaveform" virtualName=""
                    explicitFocusOrder="0" pos="0.5Cc 16 32M 120" class="Waveform"
                    params="formatManager , transportSource"/>
  <GENERICCOMPONENT name="" id="f967fc403ed73574" memberName="lowerWaveform" virtualName=""
                    explicitFocusOrder="0" pos="0.5Cc -8R 32M 120" posRelativeY="6d2236e7e917afa4"
                    class="Waveform" params="formatManager , transportSource"/>
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
                    explicitFocusOrder="0" pos="0.5Cc -8R 32M 39.012%" posRelativeY="f42caa46057f2a0"
                    class="FileTreeComponent" params="directoryList"/>
  <GENERICCOMPONENT name="" id="fa801866cc59e27a" memberName="deviceSelector" virtualName=""
                    explicitFocusOrder="0" pos="0.5Cc -8R 32M 39.012%" posRelativeY="f42caa46057f2a0"
                    class="AudioDeviceSelectorComponent" params="deviceManager , 0 , 0 , 2 , 2 , false , false , true , false"/>
  <GENERICCOMPONENT name="statusbar" id="957b301f5907e647" memberName="statusbar"
                    virtualName="" explicitFocusOrder="0" pos="0.5Cc 8Rr 16M 32"
                    class="Statusbar" params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
