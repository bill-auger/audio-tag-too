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

#include "GuiConstants.h"
#include "MediaConstants.h"

//[/Headers]

#include "MainContent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainContent::MainContent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    background.reset (new Background());
    addAndMakeVisible (background.get());
    background->setName ("background");

    waveformUpper.reset (new Waveform (formatManager , transportSource));
    addAndMakeVisible (waveformUpper.get());
    waveformUpper->setName ("waveformUpper");

    waveformLower.reset (new Waveform (formatManager , transportSource));
    addAndMakeVisible (waveformLower.get());
    waveformLower->setName ("waveformLower");

    followButton.reset (new ToggleButton ("followButton"));
    addAndMakeVisible (followButton.get());
    followButton->setButtonText (TRANS("Follow Cursor"));
    followButton->addListener (this);

    headButton.reset (new TextButton ("headButton"));
    addAndMakeVisible (headButton.get());
    headButton->setButtonText (TRANS("Head"));
    headButton->addListener (this);

    transportButton.reset (new TextButton ("transportButton"));
    addAndMakeVisible (transportButton.get());
    transportButton->setButtonText (TRANS("Play"));
    transportButton->addListener (this);

    tailButton.reset (new TextButton ("tailButton"));
    addAndMakeVisible (tailButton.get());
    tailButton->setButtonText (TRANS("Tail"));
    tailButton->addListener (this);

    fileTree.reset (new FileTreeComponent (directoryList));
    addAndMakeVisible (fileTree.get());
    fileTree->setName ("fileTree");

    statusbar.reset (new Statusbar());
    addAndMakeVisible (statusbar.get());
    statusbar->setName ("statusbar");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (766, 742);


    //[Constructor] You can add your own custom stuff here..

  fileTree->setColour(FileTreeComponent::backgroundColourId , Colours::lightgrey.withAlpha(0.6f)) ;

  setAudioChannels(MEDIA::N_CHANNELS_IN , MEDIA::N_CHANNELS_OUT) ;
  this->formatManager.registerBasicFormats() ;
  this->audioSourcePlayer.setSource(&transportSource) ;
  this->directoryList.setDirectory(File::getSpecialLocation(File::userHomeDirectory) , true , true) ;
  RuntimePermissions::request(RuntimePermissions::recordAudio , [this] (bool granted)
  {
    int numInputChannels = granted ? MEDIA::N_CHANNELS_IN : 0 ;

    this->deviceManager.initialise(numInputChannels , MEDIA::N_CHANNELS_IN , nullptr , true , {} , nullptr) ;
  }) ;

  this->deviceManager   .addAudioCallback (&audioSourcePlayer) ;
  this->waveformLower  ->addChangeListener(this) ;
  this->transportSource .addChangeListener(this) ;
  this->fileTree       ->addListener      (this) ;

  this->thread.startThread(3) ;

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

  this->fileTree       ->removeListener      (this) ;
  this->transportSource .removeChangeListener(this) ;
  this->waveformLower  ->removeChangeListener(this) ;
  this->deviceManager   .removeAudioCallback(&audioSourcePlayer) ;

    //[/Destructor_pre]

    background = nullptr;
    waveformUpper = nullptr;
    waveformLower = nullptr;
    followButton = nullptr;
    headButton = nullptr;
    transportButton = nullptr;
    tailButton = nullptr;
    fileTree = nullptr;
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
        float x = static_cast<float> ((getWidth() / 2) - ((getWidth() - 16) / 2)), y = 8.0f, width = static_cast<float> (getWidth() - 16), height = static_cast<float> (getHeight() - 48);
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

    background->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    waveformUpper->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), 16, getWidth() - 32, 120);
    waveformLower->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), 16 + 120 - -8, getWidth() - 32, 120);
    followButton->setBounds (624, (16 + 120 - -8) + 120 - -8, 126, 24);
    headButton->setBounds ((getWidth() / 2) + -150 - (150 / 2), (16 + 120 - -8) + 120 - -8, 150, 24);
    transportButton->setBounds ((getWidth() / 2) - (150 / 2), (16 + 120 - -8) + 120 - -8, 150, 24);
    tailButton->setBounds ((getWidth() / 2) + 150 - (150 / 2), (16 + 120 - -8) + 120 - -8, 150, 24);
    fileTree->setBounds ((getWidth() / 2) - ((getWidth() - 32) / 2), getHeight() - 48 - (getHeight() - 360), getWidth() - 32, getHeight() - 360);
    statusbar->setBounds (0, getHeight() - 32, proportionOfWidth (1.0000f), 32);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainContent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == followButton.get())
    {
        //[UserButtonCode_followButton] -- add your button handler code here..

      toggleFollowTransport() ;

        //[/UserButtonCode_followButton]
    }
    else if (buttonThatWasClicked == headButton.get())
    {
        //[UserButtonCode_headButton] -- add your button handler code here..

      setHeadMarker() ;

        //[/UserButtonCode_headButton]
    }
    else if (buttonThatWasClicked == transportButton.get())
    {
        //[UserButtonCode_transportButton] -- add your button handler code here..

      toggleTransport() ;

        //[/UserButtonCode_transportButton]
    }
    else if (buttonThatWasClicked == tailButton.get())
    {
        //[UserButtonCode_tailButton] -- add your button handler code here..

      setTailMarker() ;

        //[/UserButtonCode_tailButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
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

void MainContent::showAudioResource(URL resource)
{
  if (loadURLIntoTransport(resource)) this->currentAudioFile = static_cast<URL&&>(resource) ;

  this->waveformLower->setURL(currentAudioFile) ;
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
  this->waveformLower->setFollowsTransport(this->followButton->getToggleState()) ;
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

void MainContent::setHeadMarker() { this->waveformLower->setHeadMarker() ; }

void MainContent::setTailMarker() { this->waveformLower->setTailMarker() ; }

void MainContent::selectionChanged() { showAudioResource(URL(this->fileTree->getSelectedFile())) ; }

void MainContent::changeListenerCallback(ChangeBroadcaster* source)
{
  if      (source ==   this->waveformLower.get()) showAudioResource(URL(this->waveformLower->getLastDroppedFile())) ;
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
                 parentClasses="public AudioAppComponent, private FileBrowserListener, private ChangeListener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="766"
                 initialHeight="742">
  <BACKGROUND backgroundColour="ff101010">
    <ROUNDRECT pos="0Cc 8 16M 48M" cornerSize="10.00000000000000000000" fill="solid: ff202020"
               hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <GENERICCOMPONENT name="background" id="b8a8c3e1b18d4ac3" memberName="background"
                    virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" class="Background"
                    params=""/>
  <GENERICCOMPONENT name="waveformUpper" id="6d2236e7e917afa4" memberName="waveformUpper"
                    virtualName="" explicitFocusOrder="0" pos="0.5Cc 16 32M 120"
                    class="Waveform" params="formatManager , transportSource"/>
  <GENERICCOMPONENT name="waveformLower" id="f967fc403ed73574" memberName="waveformLower"
                    virtualName="" explicitFocusOrder="0" pos="0.5Cc -8R 32M 120"
                    posRelativeY="6d2236e7e917afa4" class="Waveform" params="formatManager , transportSource"/>
  <TOGGLEBUTTON name="followButton" id="643342ab575f0407" memberName="followButton"
                virtualName="" explicitFocusOrder="0" pos="624 -8R 126 24" posRelativeY="f967fc403ed73574"
                buttonText="Follow Cursor" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TEXTBUTTON name="headButton" id="9953692c678b8d85" memberName="headButton"
              virtualName="" explicitFocusOrder="0" pos="-150Cc -8R 150 24"
              posRelativeY="f967fc403ed73574" buttonText="Head" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="transportButton" id="d6f37465bfb799aa" memberName="transportButton"
              virtualName="" explicitFocusOrder="0" pos="0Cc -8R 150 24" posRelativeY="f967fc403ed73574"
              buttonText="Play" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="tailButton" id="306d8525bb18da83" memberName="tailButton"
              virtualName="" explicitFocusOrder="0" pos="150Cc -8R 150 24"
              posRelativeY="f967fc403ed73574" buttonText="Tail" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="fileTree" id="230286b07ddaa9d7" memberName="fileTree" virtualName=""
                    explicitFocusOrder="0" pos="0.5Cc 48Rr 32M 360M" class="FileTreeComponent"
                    params="directoryList"/>
  <GENERICCOMPONENT name="statusbar" id="957b301f5907e647" memberName="statusbar"
                    virtualName="" explicitFocusOrder="0" pos="0 32R 100% 32" class="Statusbar"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
