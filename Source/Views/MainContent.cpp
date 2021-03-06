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
#include "../Controllers/AudioTagToo.h"
#ifdef CONTROLLER_OWNS_STORAGE
#include "../Models/AudioTagTooStore.h"
#endif // CONTROLLER_OWNS_STORAGE
#include "ClipsTable.h"
#include "Statusbar.h"
#include "Waveform.h"

//[/Headers]

#include "MainContent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainContent::MainContent ()
    : audioFileFilter(MEDIA::IMPORT_WAVEFILE_MASK , String("*") , MEDIA::IMPORT_WAVEFILE_DESC) , workerThread(APP::WORKER_THREAD_NAME)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    fullWaveform.reset (new Waveform (formatManager , transportSource));
    addAndMakeVisible (fullWaveform.get());

    clipWaveform.reset (new Waveform (formatManager , transportSource));
    addAndMakeVisible (clipWaveform.get());

    controlsGroup.reset (new GroupComponent (String(),
                                             String()));
    addAndMakeVisible (controlsGroup.get());
    controlsGroup->setColour (GroupComponent::outlineColourId, Colour (0x00000000));

    headButton.reset (new TextButton (String()));
    addAndMakeVisible (headButton.get());
    headButton->setButtonText (TRANS("Head"));

    transportButton.reset (new TextButton (String()));
    addAndMakeVisible (transportButton.get());
    transportButton->setButtonText (TRANS("Play"));

    clipButton.reset (new TextButton (String()));
    addAndMakeVisible (clipButton.get());
    clipButton->setButtonText (TRANS("Clip"));

    tailButton.reset (new TextButton (String()));
    addAndMakeVisible (tailButton.get());
    tailButton->setButtonText (TRANS("Tail"));

    tabPanel.reset (new TabbedComponent (TabbedButtonBar::TabsAtTop));
    addAndMakeVisible (tabPanel.get());
    tabPanel->setTabBarDepth (30);
    tabPanel->addTab (TRANS("Files"), Colour (0xff404040), new FileBrowserComponent ((FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles) , File() , &(this->audioFileFilter) , nullptr), true);
    tabPanel->addTab (TRANS("Clips"), Colour (0xff404040), new ClipsTable(), true);
    tabPanel->addTab (TRANS("Devices"), Colour (0xff404040), new AudioDeviceSelectorComponent (deviceManager , 0 , 0 , 2 , 2 , false , false , true , false), true);
    tabPanel->setCurrentTabIndex (0);

    statusbar.reset (new Statusbar());
    addAndMakeVisible (statusbar.get());


    //[UserPreSize]

  this->fileBrowser            = static_cast<FileBrowserComponent*>(this->tabPanel   ->getTabContentComponent(GUI::FILE_BROWSER_IDX)) ;
  FileListComponent* file_list = static_cast<FileListComponent*   >(this->fileBrowser->getDisplayComponent()                        ) ;
  this->clipsTable             = static_cast<ClipsTable*          >(this->tabPanel   ->getTabContentComponent(GUI::CLIPS_TABLE_IDX )) ;
#ifndef CONTROLLER_OWNS_STORAGE
  this->storage.reset(new AudioTagTooStore()) ;
#endif // CONTROLLER_OWNS_STORAGE

  this->waveforms.push_back(this->fullWaveform.get()) ;
  this->waveforms.push_back(this->clipWaveform.get()) ;

    //[/UserPreSize]

    setSize (766, 742);


    //[Constructor] You can add your own custom stuff here..

  this->fullWaveform->setName(GUI::FULL_WAVEFORM_ID) ;
  this->clipWaveform->setName(GUI::CLIP_WAVEFORM_ID) ;

  this->tabPanel->setColour(TabbedComponent::backgroundColourId , GUI::TABPANEL_BG_COLOR) ;
  this->tabPanel->setColour(TabbedComponent::outlineColourId    , GUI::TABPANEL_FG_COLOR) ;
  this->fileBrowser->setColour(FileBrowserComponent::currentPathBoxBackgroundColourId , GUI::FILEPATH_BG_COLOR   ) ;
  this->fileBrowser->setColour(FileBrowserComponent::currentPathBoxTextColourId       , GUI::FILEPATH_FG_COLOR   ) ;
  this->fileBrowser->setColour(FileBrowserComponent::currentPathBoxArrowColourId      , GUI::FILEPATH_ARROW_COLOR) ;
  this->fileBrowser->setColour(FileBrowserComponent::filenameBoxBackgroundColourId    , GUI::FILENAME_BG_COLOR   ) ;
  this->fileBrowser->setColour(FileBrowserComponent::filenameBoxTextColourId          , GUI::FILENAME_FG_COLOR   ) ;
  file_list->setColour(ListBox::backgroundColourId                                , GUI::BROWSER_BG_COLOR         ) ;
  file_list->setColour(ListBox::textColourId                                      , Colour(0xFF2020FF)) ; // nfg
  file_list->setColour(DirectoryContentsDisplayComponent::textColourId 		        , GUI::BROWSER_FG_COLOR         ) ;
  file_list->setColour(DirectoryContentsDisplayComponent::highlightColourId	      , GUI::BROWSER_SELECTED_BG_COLOR) ;
  file_list->setColour(DirectoryContentsDisplayComponent::highlightedTextColourId	, GUI::BROWSER_SELECTED_FG_COLOR) ;

  this->formatManager    .registerBasicFormats() ;
  this->audioSourcePlayer.setSource(&transportSource) ;

  // restore stored clips
#ifndef CONTROLLER_OWNS_STORAGE
  this->clipsTable->initialize(this->storage->clips , this->storage->compilations) ;
#endif // CONTROLLER_OWNS_STORAGE

  this->headButton     ->addListener      (this) ;
  this->transportButton->addListener      (this) ;
  this->clipButton     ->addListener      (this) ;
  this->tailButton     ->addListener      (this) ;
  this->deviceManager   .addAudioCallback (&audioSourcePlayer) ;
  this->deviceManager   .addChangeListener(this) ;
#ifndef CONTROLLER_OWNS_STORAGE
  this->deviceManager   .addChangeListener(this->storage.get()) ;
#endif // CONTROLLER_OWNS_STORAGE
  this->clipWaveform   ->addChangeListener(this) ;
  this->transportSource .addChangeListener(this) ;
  this->fileBrowser    ->addListener      (this) ;
#ifndef CONTROLLER_OWNS_STORAGE
  this->storage->clips       .addListener      (this->clipsTable) ;
  this->storage->compilations.addListener      (this->clipsTable) ;
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
  this->clipButton     ->removeListener      (this) ;
  this->tailButton     ->removeListener      (this) ;
  this->deviceManager   .removeAudioCallback  (&audioSourcePlayer) ;
  this->deviceManager   .removeChangeListener(this) ;
#ifndef CONTROLLER_OWNS_STORAGE
  this->deviceManager   .removeChangeListener(this->storage.get()) ;
#else // CONTROLLER_OWNS_STORAGE
  if (AudioTagToo::IsInitialized)
  this->deviceManager   .removeChangeListener (AudioTagToo::Store.get()) ;
#endif // CONTROLLER_OWNS_STORAGE
  this->clipWaveform   ->removeChangeListener(this) ;
  this->transportSource .removeChangeListener(this) ;
  this->fileBrowser    ->removeListener      (this) ;
#ifndef CONTROLLER_OWNS_STORAGE
  this->storage->clips       .removeListener (this->clipsTable) ;
  this->storage->compilations.removeListener (this->clipsTable) ;

  this->storage = nullptr ;
#else // CONTROLLER_OWNS_STORAGE
  if (AudioTagToo::IsInitialized)
  this->clips           .removeListener      (this->clipsTable) ;
  if (AudioTagToo::IsInitialized)
  this->compilations    .removeListener      (this->clipsTable) ;
#endif // CONTROLLER_OWNS_STORAGE

    //[/Destructor_pre]

    fullWaveform = nullptr;
    clipWaveform = nullptr;
    controlsGroup = nullptr;
    headButton = nullptr;
    transportButton = nullptr;
    clipButton = nullptr;
    tailButton = nullptr;
    tabPanel = nullptr;
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

    fullWaveform->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), 16, getWidth() - 32, 120);
    clipWaveform->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), 16 + 120 - -8, getWidth() - 32, 120);
    controlsGroup->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), (16 + 120 - -8) + 120 - -8, getWidth() - 32, 24);
    headButton->setBounds (((getWidth() / 2) - ((getWidth() - 32) / 2)) + (getWidth() - 32) / 2 + -100 - 100, ((16 + 120 - -8) + 120 - -8) + 0, 100, 24);
    transportButton->setBounds (((getWidth() / 2) - ((getWidth() - 32) / 2)) + (getWidth() - 32) / 2 - 100, ((16 + 120 - -8) + 120 - -8) + 0, 100, 24);
    clipButton->setBounds (((getWidth() / 2) - ((getWidth() - 32) / 2)) + (getWidth() - 32) / 2, ((16 + 120 - -8) + 120 - -8) + 0, 100, 24);
    tailButton->setBounds (((getWidth() / 2) - ((getWidth() - 32) / 2)) + (getWidth() - 32) / 2 + 100, ((16 + 120 - -8) + 120 - -8) + 0, 100, 24);
    tabPanel->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), ((16 + 120 - -8) + 120 - -8) + 24 - -8, getWidth() - 32, getHeight() - 366);
    statusbar->setBounds ((getWidth() / 2) - ((getWidth() - 16) / 2), getHeight() - 8 - 40, getWidth() - 16, 40);

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* setup/teardown */

#ifdef CONTROLLER_OWNS_STORAGE
void MainContent::initialize(ValueTree& clips , ValueTree& compilations , NamedValueSet& features)
{
  this->clips             = clips ;
  this->compilations      = compilations ;
#else // CONTROLLER_OWNS_STORAGE
void MainContent::initialize(NamedValueSet& features)
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

#ifdef CONTROLLER_OWNS_STORAGE
  // restore stored clips
  this->clipsTable->initialize(this->clips , this->compilations) ;

  this->fileBrowser ->setRoot(File(initial_dir)) ;

  this->deviceManager.addChangeListener(AudioTagToo::Store.get()) ;
  this->clips        .addListener      (this->clipsTable) ;
  this->compilations .addListener      (this->clipsTable) ;
#endif // CONTROLLER_OWNS_STORAGE

  this->fullWaveform->startTimerHz(course_fps) ;
  this->clipWaveform->startTimerHz(fine_fps  ) ;
  this->clipWaveform->setZoomFactor(zoom_factor) ;
}


/* getters/setters */

void MainContent::setStatusL(String statusText) { this->statusbar->setStatusL(statusText) ; }

void MainContent::setStatusC(String statusText) { this->statusbar->setStatusC(statusText) ; }

void MainContent::setStatusR(String statusText) { this->statusbar->setStatusR(statusText) ; }

void MainContent::setStatus()
{
  double head_time      = this->clipWaveform->getHeadTime() ;
  double tail_time      = this->clipWaveform->getTailTime() ;
  double cursor_time    = this->transportSource.getCurrentPosition() ;
  double clip_time      = tail_time - head_time ;
  bool   is_playing     = this->transportSource.isPlaying() ;
  double status_c_time  = (is_playing) ? cursor_time       : clip_time ;
  Colour status_c_color = (is_playing) ? GUI::CURSOR_COLOR : GUI::CURSOR_COLOR.darker(0.5) ;

  this->statusbar->setStatusL(durationString(head_time    ) , GUI::HEAD_COLOR) ;
  this->statusbar->setStatusC(durationString(status_c_time) , status_c_color ) ;
  this->statusbar->setStatusR(durationString(tail_time    ) , GUI::TAIL_COLOR) ;
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

  AudioTagToo::ResetAudio() ;
}

void MainContent::toggleTransport()
{
  if (this->transportSource.isPlaying()) this->transportSource.stop()  ;
  else                                   this->transportSource.start() ;
}

void MainContent::updateTransportButton()
{
  bool is_rolling = this->transportSource.isPlaying() ;

  if (!is_rolling) this->transportSource.setPosition(this->clipWaveform->getHeadTime()) ;
  transportButton->setButtonText((is_rolling) ? "Stop" : "Play") ;
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

void MainContent::createClip()
{
#ifndef CONTROLLER_OWNS_STORAGE
  this->storage->createClip(this->audioFilename               ,
                            this->fullWaveform->getHeadTime() ,
                            this->fullWaveform->getTailTime() ) ;
#else // CONTROLLER_OWNS_STORAGE
  AudioTagToo::CreateClip(this->audioFilename               ,
                          this->fullWaveform->getHeadTime() ,
                          this->fullWaveform->getTailTime() ) ;
#endif // CONTROLLER_OWNS_STORAGE
}

String MainContent::durationString(double duration)
{
  int    duration_int =        int(duration) ;
  String milliseconds = String(int(duration     * 1000.0) % 1000) ;
  String seconds      = String(   (duration_int         ) %   60) ;
  String minutes      = String(   (duration_int /     60) %   60) ;
  String hours        = String(   (duration_int /   3600)       ) ;
  String clip_time    = String(hours + ":" + minutes + ":" + seconds + ":" + milliseconds) ;

  return clip_time ;
}


/* event handlers */

void MainContent::paintOverChildren(Graphics& g)
{
  if (this->clipWaveform->getZoomScale() == 1.0) return ;

  Rectangle<int> full_wave_head_bounds = getLocalArea(this->fullWaveform.get() , this->fullWaveform->getHeadMarkerBounds()) ;
  Rectangle<int> full_wave_tail_bounds = getLocalArea(this->fullWaveform.get() , this->fullWaveform->getTailMarkerBounds()) ;
  Rectangle<int> clip_wave_tail_bounds = getLocalArea(this->clipWaveform.get() , this->clipWaveform->getTailMarkerBounds()) ;
  Rectangle<int> clip_wave_head_bounds = getLocalArea(this->clipWaveform.get() , this->clipWaveform->getHeadMarkerBounds()) ;
  Point<int>     full_wave_head_bl     = full_wave_head_bounds.getBottomLeft () ;
  Point<int>     full_wave_tail_br     = full_wave_tail_bounds.getBottomRight() ;
  Point<int>     clip_wave_tail_tr     = clip_wave_tail_bounds.getTopRight   () ;
  Point<int>     clip_wave_head_tl     = clip_wave_head_bounds.getTopLeft    () ;

  Path seam ;
  g.setColour(GUI::WAVE_SELECTED_COLOR) ;
//   bezier splines
//   seam.startNewSubPath(           (float)full_wave_head_bl.getX() , (float)full_wave_head_bl.getY()) ;
//   seam.quadraticTo(0.0f,  150.0f, (float)clip_wave_head_tl.getX() , (float)clip_wave_head_tl.getY()) ;
//   seam.lineTo(                    (float)clip_wave_tail_tr.getX() , (float)clip_wave_tail_tr.getY()) ;
//   seam.quadraticTo(0.0f,  150.0f, (float)full_wave_tail_br.getX() , (float)full_wave_tail_br.getY()) ;
//   seam.closeSubPath() ;
  seam.addQuadrilateral(full_wave_head_bl.getX() , full_wave_head_bl.getY() ,
                        full_wave_tail_br.getX() , full_wave_tail_br.getY() ,
                        clip_wave_tail_tr.getX() , clip_wave_tail_tr.getY() ,
                        clip_wave_head_tl.getX() , clip_wave_head_tl.getY() ) ;
  g.fillPath(seam) ;

  g.setColour(GUI::GUI::HEAD_COLOR) ;
  g.drawDashedLine(Line<float>(full_wave_head_bl.getX() , full_wave_head_bl.getY() ,
                               clip_wave_head_tl.getX() , clip_wave_head_tl.getY() ) ,
                   GUI::DASH_LENGTHS , GUI::N_DASH_LENGTHS                           ) ;

  g.setColour(GUI::GUI::TAIL_COLOR) ;
  g.drawDashedLine(Line<float>(full_wave_tail_br.getX() , full_wave_tail_br.getY() ,
                               clip_wave_tail_tr.getX() , clip_wave_tail_tr.getY() ) ,
                   GUI::DASH_LENGTHS , GUI::N_DASH_LENGTHS                           ) ;
}

void MainContent::prepareToPlay(int samplesPerBlockExpected, double sampleRate) { }

void MainContent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) { }

void MainContent::releaseResources() { }

void MainContent::buttonClicked(Button* a_button)
{
  if      (a_button == this->headButton     .get()) setHeadMarker() ;
  else if (a_button == this->transportButton.get()) toggleTransport() ;
  else if (a_button == this->clipButton     .get()) createClip() ;
  else if (a_button == this->tailButton     .get()) setTailMarker() ;
}

void MainContent::selectionChanged() { loadUrl(this->fileBrowser->getSelectedFile(0)) ; }

void MainContent::changeListenerCallback(ChangeBroadcaster* source)
{
  if      (source ==   this->clipWaveform.get()) repaint() ;
  else if (source == &(this->transportSource)  ) updateTransportButton() ;
  else if (source == &(this->deviceManager  )  )
  {
    bool is_device_ready = this->deviceManager.getCurrentAudioDevice() != nullptr ;
    int  tab_pane_idx    = (!is_device_ready                      ) ? GUI::DEVICE_SELECTOR_IDX :
                           (File(this->projectFilename).exists() ||
                            File(this->audioFilename  ).exists()  ) ? GUI::CLIPS_TABLE_IDX     :
                                                                      GUI::FILE_BROWSER_IDX    ;

    this->tabPanel->setCurrentTabIndex(tab_pane_idx) ;
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
                 parentClasses="public AudioAppComponent, private Button::Listener, private FileBrowserListener, private ChangeListener"
                 constructorParams="" variableInitialisers="audioFileFilter(MEDIA::IMPORT_WAVEFILE_MASK , String(&quot;*&quot;) , MEDIA::IMPORT_WAVEFILE_DESC) , workerThread(APP::WORKER_THREAD_NAME)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="766" initialHeight="742">
  <BACKGROUND backgroundColour="ff101010">
    <ROUNDRECT pos="0Cc 8 16M 64M" cornerSize="10.00000000000000000000" fill="solid: ff202020"
               hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <GENERICCOMPONENT name="" id="6d2236e7e917afa4" memberName="fullWaveform" virtualName=""
                    explicitFocusOrder="0" pos="0.5Cc 16 32M 120" class="Waveform"
                    params="formatManager , transportSource"/>
  <GENERICCOMPONENT name="" id="f967fc403ed73574" memberName="clipWaveform" virtualName=""
                    explicitFocusOrder="0" pos="0.5Cc -8R 32M 120" posRelativeY="6d2236e7e917afa4"
                    class="Waveform" params="formatManager , transportSource"/>
  <GROUPCOMPONENT name="" id="f42caa46057f2a0" memberName="controlsGroup" virtualName=""
                  explicitFocusOrder="0" pos="0.5Cc -8R 32M 24" posRelativeY="f967fc403ed73574"
                  outlinecol="0" title=""/>
  <TEXTBUTTON name="" id="9953692c678b8d85" memberName="headButton" virtualName=""
              explicitFocusOrder="0" pos="-100Cr 0 100 24" posRelativeX="f42caa46057f2a0"
              posRelativeY="f42caa46057f2a0" buttonText="Head" connectedEdges="0"
              needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="" id="d6f37465bfb799aa" memberName="transportButton" virtualName=""
              explicitFocusOrder="0" pos="0Cr 0 100 24" posRelativeX="f42caa46057f2a0"
              posRelativeY="f42caa46057f2a0" buttonText="Play" connectedEdges="0"
              needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="" id="17eafcc50188fee2" memberName="clipButton" virtualName=""
              explicitFocusOrder="0" pos="0C 0 100 24" posRelativeX="f42caa46057f2a0"
              posRelativeY="f42caa46057f2a0" buttonText="Clip" connectedEdges="0"
              needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="" id="306d8525bb18da83" memberName="tailButton" virtualName=""
              explicitFocusOrder="0" pos="100C 0 100 24" posRelativeX="f42caa46057f2a0"
              posRelativeY="f42caa46057f2a0" buttonText="Tail" connectedEdges="0"
              needsCallback="0" radioGroupId="0"/>
  <TABBEDCOMPONENT name="" id="c0b551b7ecf04741" memberName="tabPanel" virtualName=""
                   explicitFocusOrder="0" pos="0.5Cc -8R 32M 366M" posRelativeY="f42caa46057f2a0"
                   orientation="top" tabBarDepth="30" initialTab="0">
    <TAB name="Files" colour="ff404040" useJucerComp="0" contentClassName="FileBrowserComponent"
         constructorParams="(FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles) , File() , &amp;(this-&gt;audioFileFilter) , nullptr"
         jucerComponentFile=""/>
    <TAB name="Clips" colour="ff404040" useJucerComp="0" contentClassName="ClipsTable"
         constructorParams="" jucerComponentFile=""/>
    <TAB name="Devices" colour="ff404040" useJucerComp="0" contentClassName="AudioDeviceSelectorComponent"
         constructorParams="deviceManager , 0 , 0 , 2 , 2 , false , false , true , false"
         jucerComponentFile=""/>
  </TABBEDCOMPONENT>
  <GENERICCOMPONENT name="" id="957b301f5907e647" memberName="statusbar" virtualName=""
                    explicitFocusOrder="0" pos="0.5Cc 8Rr 16M 40" class="Statusbar"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
