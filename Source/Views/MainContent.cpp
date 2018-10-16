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
#include "../Constants/StorageConstants.h"
#include "../Trace/TraceMainContent.h"

//[/Headers]

#include "MainContent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainContent::MainContent ()
    : audioFileFilter(MEDIA::IMPORT_WAVEFILE_MASK , "*" , MEDIA::IMPORT_WAVEFILE_DESC) , workerThread(APP::WORKER_THREAD_NAME)
{
    //[Constructor_pre] You can add your own custom stuff here..

  processCliParams() ;

    //[/Constructor_pre]

    fullWaveform.reset (new Waveform (formatManager , transportSource , courseFps));
    addAndMakeVisible (fullWaveform.get());

    clipWaveform.reset (new Waveform (formatManager , transportSource , fineFps));
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
    clipButton->addListener (this);

    tailButton.reset (new TextButton (String()));
    addAndMakeVisible (tailButton.get());
    tailButton->setButtonText (TRANS("Tail"));

    tabPanel.reset (new TabbedComponent (TabbedButtonBar::TabsAtTop));
    addAndMakeVisible (tabPanel.get());
    tabPanel->setTabBarDepth (30);
    tabPanel->addTab (TRANS("Files"), Colour (0xff404040), new FileBrowserComponent ((FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles) , this->workingDir , &(this->audioFileFilter) , nullptr), true);
    tabPanel->addTab (TRANS("Clips"), Colour (0xff404040), new TreeView(), true);
    tabPanel->addTab (TRANS("Compilations"), Colour (0xff404040), new TreeView(), true);
    tabPanel->addTab (TRANS("Devices"), Colour (0xff404040), new AudioDeviceSelectorComponent (deviceManager , 0 , 0 , 2 , 2 , false , false , true , false), true);
    tabPanel->setCurrentTabIndex (0);

    statusbar.reset (new Statusbar());
    addAndMakeVisible (statusbar.get());


    //[UserPreSize]

  this->app                    = JUCEApplication::getInstance() ;
  this->fileBrowser            = static_cast<FileBrowserComponent*>(this->tabPanel   ->getTabContentComponent(GUI::FILE_BROWSER_IDX)) ;
  FileListComponent* file_list = static_cast<FileListComponent*   >(this->fileBrowser->getDisplayComponent()                        ) ;
  this->clipsTreeview          = static_cast<TreeView*            >(this->tabPanel   ->getTabContentComponent(GUI::CLIPS_IDX       )) ;
  this->compilationsTreeview   = static_cast<TreeView*            >(this->tabPanel   ->getTabContentComponent(GUI::COMPILATIONS_IDX)) ;
  this->clips       .reset(new ClipItem(STRING(STORE::COMPILATIONS_ID) , String::empty)) ;
  this->compilations.reset(new ClipItem(STRING(STORE::CLIPS_ID       ) , String::empty)) ;
  this->storage     .reset(new AudioTagTooStore()) ;

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

  this->clipsTreeview       ->setRootItem(this->clips       .get()) ;
  this->compilationsTreeview->setRootItem(this->compilations.get()) ;
  this->clipsTreeview       ->setRootItemVisible(false) ;
  this->compilationsTreeview->setRootItemVisible(false) ;

  this->formatManager    .registerBasicFormats() ;
  this->audioSourcePlayer.setSource(&transportSource) ;

  this->headButton          ->addListener      (this);
  this->transportButton     ->addListener      (this);
  this->tailButton          ->addListener      (this);
  this->deviceManager        .addAudioCallback (&audioSourcePlayer) ;
  this->deviceManager        .addChangeListener(this) ;
  this->clipWaveform        ->addChangeListener(this) ;
  this->transportSource      .addChangeListener(this) ;
  this->fileBrowser         ->addListener      (this) ;
  this->storage->clips       .addListener      (this) ;
  this->storage->compilations.addListener      (this) ;

  // initialize stored state
  this->storage->initialize() ;

#if ! DISABLE_MEDIA
  // start audio and worker threads
  setAudioChannels(0 , MEDIA::N_CHANNELS_OUT , this->storage->deviceStateXml.get()) ;
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
  this->storage->teardown() ;

  this->transportSource  .setSource(nullptr) ;
  this->audioSourcePlayer.setSource(nullptr) ;

  this->headButton     ->removeListener      (this);
  this->transportButton->removeListener      (this);
  this->tailButton     ->removeListener      (this);
  this->deviceManager   .removeAudioCallback (&audioSourcePlayer) ;
  this->deviceManager   .removeChangeListener(this) ;
  this->transportSource .removeChangeListener(this) ;
  this->fileBrowser    ->removeListener      (this) ;
  this->storage->root   .removeListener      (this) ;

  this->storage = nullptr ;

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

  this->clips        = nullptr ;
  this->compilations = nullptr ;

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
    controlsGroup->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), (16 + 120 - -8) + 120 - -8, getWidth() - 32, 24);
    headButton->setBounds (((getWidth() / 2) - ((getWidth() - 32) / 2)) + (getWidth() - 32) / 2 + -100 - 100, ((16 + 120 - -8) + 120 - -8) + 0, 100, 24);
    transportButton->setBounds (((getWidth() / 2) - ((getWidth() - 32) / 2)) + (getWidth() - 32) / 2 - 100, ((16 + 120 - -8) + 120 - -8) + 0, 100, 24);
    clipButton->setBounds (((getWidth() / 2) - ((getWidth() - 32) / 2)) + (getWidth() - 32) / 2, ((16 + 120 - -8) + 120 - -8) + 0, 100, 24);
    tailButton->setBounds (((getWidth() / 2) - ((getWidth() - 32) / 2)) + (getWidth() - 32) / 2 + 100, ((16 + 120 - -8) + 120 - -8) + 0, 100, 24);
    tabPanel->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), ((16 + 120 - -8) + 120 - -8) + 24 - -8, getWidth() - 32, getHeight() - 358);
    statusbar->setBounds ((getWidth() / 2) - ((getWidth() - 16) / 2), getHeight() - 8 - 32, getWidth() - 16, 32);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}


//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* getters/setters */

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

  shutdownAudio() ; setAudioChannels(0 , MEDIA::N_CHANNELS_OUT , this->storage->deviceStateXml.get()) ;
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
  if (!this->storage->createClip(this->audioFilename               ,
                                 this->fullWaveform->getHeadTime() ,
                                 this->fullWaveform->getHeadTime() ))
    ; // TODO: collision alert
}


/* model helpers */

TreeViewItem* MainContent::getViewItemFor(ValueTree root_store)
{
  return (root_store == this->storage->clips       ) ? this->clips.get()        :
         (root_store == this->storage->compilations) ? this->compilations.get() : nullptr ;
}
/*
bool MainContent::isClipsNode(ValueTree parent_node)
{
  return parent_node             == this->storage->clips ||
         parent_node.getParent() == this->storage->clips  ;
}

bool MainContent::isCompilationsNode(ValueTree parent_node)
{
  return parent_node             == this->storage->compilations ||
         parent_node.getParent() == this->storage->compilations  ;
}

bool MainContent::isMasterNode(ValueTree parent_node)
{
  return parent_node == this->storage->clips        ||
         parent_node == this->storage->compilations  ;
}

bool MainContent::isClipNode(ValueTree parent_node)
{
  return parent_node.getParent() == this->storage->clips        ||
         parent_node.getParent() == this->storage->compilations  ;
}
*/
TreeViewItem* MainContent::newMasterItem(ValueTree master_node)
{
  String        master_id       = STRING(master_node.getType()) ;
  String        master_filename = STRING(master_node[STORE::FILENAME_KEY]) ;
  String        master_label    = File(master_filename).getFileName() ;
  TreeViewItem* new_master      = new ClipItem(master_id , master_label) ;

DEBUG_TRACE_NEW_MASTER_ITEM
// Trace::DumpStore(master_node , "master_node") ;

  return new_master ;
}

TreeViewItem* MainContent::newClipItem(ValueTree clip_node)
{
  String        clip_id     = STRING(clip_node.getType()) ;
  String        file_id     = clip_id + "-filename" ;
  String        begin_id    = clip_id + "-begin_time" ;
  String        end_id      = clip_id + "-end_time" ;
  String        filename    = STRING(       clip_node[STORE::FILENAME_KEY  ]) ;
  String        begin_time  = String(double(clip_node[STORE::BEGIN_TIME_KEY]) , 6) ;
  String        end_time    = String(double(clip_node[STORE::END_TIME_KEY  ]) , 6) ;
  String        clip_label  = begin_time + " - " + end_time ;
  String        file_label  = GUI::FILE_ITEM_LABEL  + filename ;
  String        begin_label = GUI::BEGIN_ITEM_LABEL + begin_time ;
  String        end_label   = GUI::ENT_ITEM_LABEL   + end_time ;
  TreeViewItem* new_clip    = new ClipItem(clip_id  , clip_label) ;
  new_clip->addSubItem(       new ClipItem(file_id  , file_label  , false) , 0) ;
  new_clip->addSubItem(       new ClipItem(begin_id , begin_label , false) , 1) ;
  new_clip->addSubItem(       new ClipItem(end_id   , end_label   , false) , 2) ;

DEBUG_TRACE_NEW_CLIP_ITEM

  return new_clip ;
}

void MainContent::createMasterItem(ValueTree root_store , ValueTree master_node)
{
  TreeViewItem* root_item   = getViewItemFor(root_store) ;
  TreeViewItem* master_item = newMasterItem(master_node) ;
  int           master_idx  = root_store.indexOf(master_node) ;

  root_item->addSubItem(master_item , master_idx) ;
  String master_item_id = master_item->getItemIdentifierString() ;
  this->storage->setProperty(master_node , STORE::ITEM_ID_KEY , master_item_id) ;

DEBUG_TRACE_CREATE_MASTER_ITEM

  for (int clip_n = 0 ; clip_n < master_node.getNumChildren() ; ++clip_n)
//     master_item->addSubItem(newClipItem(master_node.getChild(clip_n)) , -1) ;
    createClipItem(root_store , master_node.getChild(clip_n)) ;
}

void MainContent::createClipItem(ValueTree root_store , ValueTree clip_node)
{
  TreeViewItem* root_item              = getViewItemFor(root_store) ;
  ValueTree     master_node            = clip_node.getParent() ;
  int           master_idx             = root_store.indexOf(master_node) ;
  int           clip_idx               = master_node.indexOf(clip_node) ;
  TreeViewItem* master_item            = root_item->getSubItem(master_idx) ;
  TreeViewItem* clip_item              = newClipItem(clip_node) ;
  String        master_item_id         = master_item->getItemIdentifierString() ;
  bool          does_master_item_exist = master_item != nullptr ;

  if (!does_master_item_exist)
  {
    master_item    = newMasterItem(master_node) ;
    root_item->addSubItem(master_item , master_idx) ;
    master_item_id = master_item->getItemIdentifierString() ;
    this->storage->setProperty(master_node , STORE::ITEM_ID_KEY , master_item_id) ;
  }

  master_item->addSubItem(clip_item , clip_idx) ;
  String clip_item_id = clip_item->getItemIdentifierString() ;
  this->storage->setProperty(clip_node , STORE::ITEM_ID_KEY , clip_item_id) ;

DEBUG_TRACE_CREATE_CLIP_ITEM
}


/* event handlers */

void MainContent::paintOverChildren(Graphics& g)
{
  if (this->clipWaveform->getZoomFactor() == 1.0) return ;

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

void MainContent::buttonClicked(Button* a_button)
{
  if      (a_button == this->headButton     .get()) setHeadMarker() ;
  else if (a_button == this->transportButton.get()) toggleTransport() ;
  else if (a_button == this->clipButton     .get()) createClip() ;
  else if (a_button == this->tailButton     .get()) setTailMarker() ;
}

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

void MainContent::selectionChanged() { loadUrl(this->fileBrowser->getSelectedFile(0)) ; }

void MainContent::changeListenerCallback(ChangeBroadcaster* source)
{
  if      (source ==   this->clipWaveform.get()) repaint() ;
  else if (source == &(this->transportSource)  ) updateTransportButton() ;
  else if (source == &(this->deviceManager  )  )
  {
    bool is_device_ready = this->deviceManager.getCurrentAudioDevice() != nullptr ;
    int  tab_pane_idx    = (!is_device_ready                    ) ? GUI::DEVICE_SELECTOR_IDX :
                           (File(this->projectFilename).exists()) ? GUI::COMPILATIONS_IDX    :
                           (File(this->audioFilename  ).exists()) ? GUI::CLIPS_IDX           :
                                                                    GUI::FILE_BROWSER_IDX    ;

DEBUG_TRACE_DEVICE_STATE_CHANGED

    if (is_device_ready) this->storage->storeConfig(this->deviceManager.createStateXml()) ;
    else                 AlertWindow::showMessageBox(AlertWindow::WarningIcon ,
                                                     GUI::DEVICE_ERROR_TITLE  ,
                                                     GUI::DEVICE_ERROR_MSG    ) ;

    this->tabPanel->setCurrentTabIndex(tab_pane_idx) ;
  }
}

void MainContent::valueTreeRedirected(ValueTree& root_store)
{
DEBUG_TRACE_STORAGE_REDIRECTED

  TreeViewItem* root_item = getViewItemFor(root_store) ;

  if (root_item != nullptr)
  {
    ValueTree master_node ;
    ValueTree clip_node ;

    while (root_item->getNumSubItems() > 0) root_item->removeSubItem(0) ;
    // clearSubItems()
    for (int master_n = 0 ; master_n < root_store.getNumChildren() ; ++master_n)
    {
      master_node = root_store.getChild(master_n) ;
      createMasterItem(root_store , master_node) ;

      for (int clip_n = 0 ; clip_n < master_node.getNumChildren() ; ++clip_n)
      {
        clip_node = master_node.getChild(clip_n) ;
        createClipItem(root_store , clip_node) ;
      }
    }
  }
}

void MainContent::valueTreeChildAdded(ValueTree& parent_node , ValueTree& new_node)
{
  bool is_master_clips_node        = parent_node             == this->storage->clips ;
  bool is_clip_clips_node          = parent_node.getParent() == this->storage->clips ;
  bool is_master_compilations_node = parent_node             == this->storage->compilations ;
  bool is_clip_compilations_node   = parent_node.getParent() == this->storage->compilations ;

//   bool is_master_clips_node        = isClipsNode       (parent_node) && isMasterNode(parent_node) ;
//   bool is_clip_clips_node          = isClipsNode       (parent_node) && isClipNode  (parent_node) ;
//   bool is_master_compilations_node = isCompilationsNode(parent_node) && isMasterNode(parent_node) ;
//   bool is_clip_compilations_node   = isCompilationsNode(parent_node) && isClipNode  (parent_node) ;

DEBUG_TRACE_STORAGE_CHILD_ADDED

  if      (is_master_clips_node       ) createMasterItem(this->storage->clips        , new_node) ;
  else if (is_clip_clips_node         ) createClipItem  (this->storage->clips        , new_node) ;
  else if (is_master_compilations_node) createMasterItem(this->storage->compilations , new_node) ;
  else if (is_clip_compilations_node  ) createClipItem  (this->storage->compilations , new_node) ;
}

void MainContent::createMasterItem(ValueTree master_node)
{
  int           master_idx      = this->storage->clips.indexOf(master_node) ;
  TreeViewItem* new_master_item = newMasterItem(master_node) ;

  for (int clip_n = 0 ; clip_n < master_node.getNumChildren() ; ++clip_n)
    new_master_item->addSubItem(newClipItem(master_node.getChild(clip_n)) , -1) ;
  this->clips->addSubItem(new_master_item , master_idx) ;
}

TreeViewItem* MainContent::newMasterItem(ValueTree master_node)
{
  String        master_label = STRING(master_node[STORE::FILENAME_KEY]) ;
  TreeViewItem* new_master   = new ClipsTreeViewItem(master_label) ;

  return new_master ;
}

void MainContent::createClipItem(ValueTree master_node , ValueTree clip_node)
{
  int           master_idx             = this->storage->clips.indexOf(master_node) ;
  TreeViewItem* master_item            = this->clips->getSubItem(master_idx) ;
  bool          does_master_item_exist = master_item != nullptr ;

  if (!does_master_item_exist)
  {
    master_item = newMasterItem(master_node) ;
    this->clips->addSubItem(master_item , master_idx) ;
  }

  int clip_idx = master_node.indexOf(clip_node) ;
  master_item->addSubItem(newClipItem(clip_node) , clip_idx) ;
}

TreeViewItem* MainContent::newClipItem(ValueTree clip_node)
{
  String        clip_label  = STRING(clip_node[STORE::BEGIN_TIME_KEY]) + " - " +
                              STRING(clip_node[STORE::END_TIME_KEY  ]) ;
  String        file_label  = STRING(clip_node[STORE::FILENAME_KEY  ]) ;
  String        begin_label = STRING(clip_node[STORE::BEGIN_TIME_KEY]) ;
  String        end_label   = STRING(clip_node[STORE::END_TIME_KEY  ]) ;
  TreeViewItem* new_clip    = new ClipsTreeViewItem("clip_label") ;
  new_clip   ->addSubItem(new ClipsTreeViewItem("file_label ") , 0) ;
  new_clip   ->addSubItem(new ClipsTreeViewItem("begin_label") , 1) ;
  new_clip   ->addSubItem(new ClipsTreeViewItem("end_label  ") , 2) ;

  return new_clip ;
}

void MainContent::valueTreeChildRemoved(ValueTree& parent_node , ValueTree& deleted_node ,
                                        int        prev_idx                              )
{
/*
  bool          is_master_node       = isMasterNode      (parent_node) ;                                          \
  bool          is_clip_node         = isClipNode        (parent_node) ;                                          \
  bool          is_clips_node        = isClipsNode       (parent_node) ;                                          \
  bool          is_compilations_node = isCompilationsNode(parent_node) ;                                          \
  ValueTree     root_store           = (is_clips_node       ) ? this->storage->clips        :
                                       (is_compilations_node) ? this->storage->compilations :
                                                                ValueTree::invalid ;
  ValueTree     master_node          = (is_master_node) ? deleted_node             :
                                       (is_clip_node  ) ? deleted_node.getParent() :
                                                          ValueTree::invalid ;
  int           master_idx           = root_store.indexOf(master_node) ;
  TreeViewItem* root_item            = (is_clips_node       ) ? this->clips        :
                                       (is_compilations_node) ? this->compilations :
                                                                nullptr ;
  TreeViewItem* parent_item          = (is_master_node) ? root_item                         :
                                       (is_clip_node  ) ? root_item->getSubItem(master_idx) :
                                                          nullptr ;
*/
  String        item_id      = STRING(deleted_node[STORE::ITEM_ID_KEY]) ;
  TreeViewItem* deleted_item = this->clipsTreeview->findItemFromIdentifierString(item_id) ;
  TreeViewItem* parent_item  = deleted_item->getParentItem() ;
  int           deleted_idx  = deleted_item->getIndexInParent() ;

DEBUG_TRACE_STORAGE_CHILD_REMOVED

  if (parent_item != nullptr) parent_item->removeSubItem(deleted_idx) ;
}

void MainContent::valueTreeChildOrderChanged(ValueTree& parent_node , int prev_idx , int curr_idx)
{
DBG("MainContent::valueTreeChildOrderChanged() parent_node=" + parent_node.getType() + " prev_idx=" + String(prev_idx) + " curr_idx=" + String(curr_idx)) ;
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
                 constructorParams="" variableInitialisers="audioFileFilter(MEDIA::IMPORT_WAVEFILE_MASK , &quot;*&quot; , MEDIA::IMPORT_WAVEFILE_DESC) , workerThread(APP::WORKER_THREAD_NAME)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="766" initialHeight="742">
  <BACKGROUND backgroundColour="ff101010">
    <ROUNDRECT pos="0Cc 8 16M 64M" cornerSize="10.00000000000000000000" fill="solid: ff202020"
               hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <GENERICCOMPONENT name="" id="6d2236e7e917afa4" memberName="fullWaveform" virtualName=""
                    explicitFocusOrder="0" pos="0.5Cc 16 32M 120" class="Waveform"
                    params="formatManager , transportSource , courseFps"/>
  <GENERICCOMPONENT name="" id="f967fc403ed73574" memberName="clipWaveform" virtualName=""
                    explicitFocusOrder="0" pos="0.5Cc -8R 32M 120" posRelativeY="6d2236e7e917afa4"
                    class="Waveform" params="formatManager , transportSource , fineFps"/>
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
         constructorParams="(FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles) , this-&gt;workingDir , &amp;(this-&gt;audioFileFilter) , nullptr"
         jucerComponentFile=""/>
    <TAB name="Clips" colour="ff404040" useJucerComp="0" contentClassName="TreeView"
         constructorParams="" jucerComponentFile=""/>
    <TAB name="Compilations" colour="ff404040" useJucerComp="0" contentClassName="TreeView"
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
