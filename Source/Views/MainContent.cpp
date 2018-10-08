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

//[Headers] You can add your own extra header files here...

#include "../Constants/AppConstants.h"
#include "../Constants/GuiConstants.h"
#include "../Constants/MediaConstants.h"
#include "../Constants/StorageConstants.h"
#include "../Models/AudioTagTooStore.h"
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

    upperWaveform.reset (new Waveform (formatManager , transportSource));
    addAndMakeVisible (upperWaveform.get());

    lowerWaveform.reset (new Waveform (formatManager , transportSource));
    addAndMakeVisible (lowerWaveform.get());

    followButton.reset (new ToggleButton (String()));
    addAndMakeVisible (followButton.get());
    followButton->setButtonText (TRANS("Follow Cursor"));

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

    deviceSelector.reset (new AudioDeviceSelectorComponent (deviceManager , 0 , 0 , 2 , 2 , false , false , true , true));
    addAndMakeVisible (deviceSelector.get());
    deviceSelector->setName ("deviceSelector");

    statusbar.reset (new Statusbar());
    addAndMakeVisible (statusbar.get());


    //[UserPreSize]

  this->upperWaveform->setName(GUI::UPPER_WAVEFORM_ID) ;
  this->lowerWaveform->setName(GUI::LOWER_WAVEFORM_ID) ;

    //[/UserPreSize]

    setSize (766, 742);


    //[Constructor] You can add your own custom stuff here..

  this->formatManager    .registerBasicFormats() ;
  this->audioSourcePlayer.setSource(&transportSource) ;
  this->directoryList    .setDirectory(File::getSpecialLocation(File::userHomeDirectory) , true , true) ;

  this->followButton   ->addListener      (this) ;
  this->headButton     ->addListener      (this) ;
  this->transportButton->addListener      (this) ;
  this->tailButton     ->addListener      (this) ;
  this->deviceManager   .addAudioCallback (&audioSourcePlayer) ;
  this->deviceManager   .addChangeListener(this) ;
  this->lowerWaveform  ->addChangeListener(this) ;
  this->transportSource .addChangeListener(this) ;
  this->fileTree       ->addListener      (this) ;

#if ! DISABLE_AUDIO
  // start audio and worker threads
  #if __ANDROID_API__ >= 23
  RuntimePermissions::request(RuntimePermissions::recordAudio , [this] (bool granted)
  {
    int numInputChannels = granted ? MEDIA::N_CHANNELS_IN : 0 ;

    this->deviceManager.initialise(numInputChannels , MEDIA::N_CHANNELS_IN , nullptr , true , {} , nullptr) ;
  }) ;
  #else // __ANDROID_API__ >= 23
  setAudioChannels(MEDIA::N_CHANNELS_IN , MEDIA::N_CHANNELS_OUT) ;
  #endif // __ANDROID_API__ >= 23
  this->workerThread.startThread(3) ;
#endif // DISABLE_AUDIO

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

  this->followButton   ->removeListener      (this) ;
  this->headButton     ->removeListener      (this) ;
  this->transportButton->removeListener      (this) ;
  this->tailButton     ->removeListener      (this) ;
  this->deviceManager   .removeAudioCallback(&audioSourcePlayer) ;
  this->transportSource .removeChangeListener(this) ;
  this->lowerWaveform  ->removeChangeListener(this) ;
  this->fileTree       ->removeListener      (this) ;

    //[/Destructor_pre]

    upperWaveform = nullptr;
    lowerWaveform = nullptr;
    followButton = nullptr;
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

    upperWaveform->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), 16, getWidth() - 32, 120);
    lowerWaveform->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), 16 + 120 - -8, getWidth() - 32, 120);
    followButton->setBounds (624, (16 + 120 - -8) + 120 - -8, 126, 24);
    headButton->setBounds ((getWidth() / 2) + -150 - (150 / 2), (16 + 120 - -8) + 120 - -8, 150, 24);
    transportButton->setBounds ((getWidth() / 2) - (150 / 2), (16 + 120 - -8) + 120 - -8, 150, 24);
    tailButton->setBounds ((getWidth() / 2) + 150 - (150 / 2), (16 + 120 - -8) + 120 - -8, 150, 24);
    fileTree->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), getHeight() - 56 - (getHeight() - 368), getWidth() - 32, getHeight() - 368);
    deviceSelector->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), getHeight() - 56 - (getHeight() - 368), getWidth() - 32, getHeight() - 368);
    statusbar->setBounds ((getWidth() / 2) - ((getWidth() - 16) / 2), getHeight() - 8 - 32, getWidth() - 16, 32);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* getters/setters */

void MainContent::showAudioResource(URL resource)
{
  if (loadURLIntoTransport(resource)) this->currentAudioFile = static_cast<URL&&>(resource) ;

  this->lowerWaveform->setURL(currentAudioFile) ;
}

bool MainContent::loadURLIntoTransport(const URL& audio_url)
{
  // unload the previous file source and delete it..
  this->transportSource.stop() ;
  this->transportSource.setSource(nullptr) ;
  this->currentAudioFileSource.reset() ;

  AudioFormatReader* reader = nullptr ;

  #if ! JUCE_IOS
  if (audio_url.isLocalFile()) reader = this->formatManager.createReaderFor(audio_url.getLocalFile()) ;
  else
  #endif
  if (reader == nullptr) reader = this->formatManager.createReaderFor(audio_url.createInputStream(false)) ;

  bool did_load_succeed = (reader != nullptr) ;

  if (did_load_succeed)
  {
    this->currentAudioFileSource.reset(new AudioFormatReaderSource(reader , true)) ;
    this->transportSource.setSource(this->currentAudioFileSource.get() ,
                                    32768                              ,
                                    &thread                            ,
                                    reader->sampleRate                 ) ;
  }

  return did_load_succeed ;
}

void MainContent::toggleFollowTransport()
{
  this->lowerWaveform->setFollowsTransport(this->followButton->getToggleState()) ;
}

void MainContent::toggleTransport()
{
  bool is_rolling = this->transportSource.isPlaying() ;

  if (is_rolling) { this->transportSource.stop() ;                                         }
  else            { this->transportSource.setPosition(0) ; this->transportSource.start() ; }

  updateTransportButton(is_rolling) ;
}

void MainContent::updateTransportButton(bool is_rolling)
{
  transportButton->setButtonText((is_rolling) ? "Stop" : "Start") ;
  transportButton->setToggleState(is_rolling , juce::dontSendNotification) ;
}

void MainContent::setHeadMarker() { this->lowerWaveform->setHeadMarker() ; }

void MainContent::setTailMarker() { this->lowerWaveform->setTailMarker() ; }

void MainContent::prepareToPlay (int samplesPerBlockExpected, double sampleRate) { }

void MainContent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) { }

void MainContent::releaseResources() { }

void MainContent::buttonClicked(Button* a_button)
{
  if      (a_button == this->followButton   .get()) toggleFollowTransport() ;
  else if (a_button == this->headButton     .get()) setHeadMarker() ;
  else if (a_button == this->transportButton.get()) toggleTransport() ;
  else if (a_button == this->tailButton     .get()) setTailMarker() ;
}

void MainContent::selectionChanged() { showAudioResource(URL(this->fileTree->getSelectedFile())) ; }

void MainContent::changeListenerCallback(ChangeBroadcaster* source)
{
  if      (source ==   this->lowerWaveform.get()) showAudioResource(URL(this->lowerWaveform->getLastDroppedFile())) ;
  else if (source == &(this->transportSource)   ) updateTransportButton(this->transportSource.isPlaying()) ;
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
  <TOGGLEBUTTON name="" id="643342ab575f0407" memberName="followButton" virtualName=""
                explicitFocusOrder="0" pos="624 -8R 126 24" posRelativeY="f967fc403ed73574"
                buttonText="Follow Cursor" connectedEdges="0" needsCallback="0"
                radioGroupId="0" state="0"/>
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
                    explicitFocusOrder="0" pos="0.5Cc 56Rr 32M 368M" class="FileTreeComponent"
                    params="directoryList"/>
  <GENERICCOMPONENT name="deviceSelector" id="fa801866cc59e27a" memberName="deviceSelector"
                    virtualName="" explicitFocusOrder="0" pos="0.5Cc 56Rr 32M 368M"
                    class="AudioDeviceSelectorComponent" params="deviceManager , 0 , 0 , 2 , 2 , false , false , true , true"/>
  <GENERICCOMPONENT name="" id="957b301f5907e647" memberName="statusbar" virtualName=""
                    explicitFocusOrder="0" pos="0.5Cc 8Rr 16M 32" class="Statusbar"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
