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

#include "GuiConstants.h"

//[/Headers]

#include "Waveform.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Waveform::Waveform (AudioFormatManager& format_manager , AudioTransportSource& source)
    : transport(source) , thumbnail(GUI::BIN_N_SAMPLES , format_manager , thumbnailCache)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    scrollbar.reset (new ScrollBar (false));
    addAndMakeVisible (scrollbar.get());
    scrollbar->setName ("scrollbar");


    //[UserPreSize]

  this->addAndMakeVisible(cursorMarker) ;
  this->addAndMakeVisible(headMarker  ) ;
  this->addAndMakeVisible(tailMarker  ) ;

    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..

  this->thumbnail .addChangeListener(this) ;
  this->scrollbar->addListener      (this) ;

  this->scrollbar->setRangeLimits(viewRange) ;
  this->scrollbar->setAutoHide(false) ;

  this->cursorMarker.setFill(GUI::CURSOR_COLOR.withAlpha(0.85f)) ;
  this->headMarker  .setFill(GUI::HEAD_COLOR  .withAlpha(0.85f)) ;
  this->tailMarker  .setFill(GUI::TAIL_COLOR  .withAlpha(0.85f)) ;
  this->headTime = this->tailTime = 0.0 ;

  this->isFollowingTransport = false ;

    //[/Constructor]
}

Waveform::~Waveform()
{
    //[Destructor_pre]. You can add your own custom destruction code here..

  this->thumbnail .removeChangeListener(this) ;
  this->scrollbar->removeListener      (this) ;

    //[/Destructor_pre]

    scrollbar = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Waveform::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = 0.0f, y = 0.0f, width = static_cast<float> (getWidth() - 0), height = static_cast<float> (getHeight() - 0);
        Colour fillColour = Colour (0xff181818);
        Colour strokeColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 1.000f);
    }

    //[UserPaint] Add your own custom painting code here..

  Rectangle<int> thumb_rect = getLocalBounds().withTrimmedBottom(GUI::SCROLLBARS_H)
                                              .reduced(GUI::PAD2) ;

  // scope background
  g.setColour(GUI::WAVE_BG_COLOR) ;
  g.fillRect(thumb_rect) ;

  // selected region
  g.setColour(Colour(0xFF202040)) ;
  g.fillRect(this->headMarker.getBounds().withWidth(this->tailMarker.getX()    -
                                                    this->headMarker.getRight())) ;

  // waveform
  g.setColour(GUI::WAVE_FG_COLOR) ;
  if (this->thumbnail.getTotalLength() > 0.0)
  {
    auto begin_secs = this->viewRange.getStart() ;
    auto end_secs   = this->viewRange.getEnd() ;

    this->thumbnail.drawChannels(g , thumb_rect , begin_secs , end_secs , 1.0f) ;
  }
  else
  {
    g.setFont(GUI::FONT_SIZE) ;
    g.drawFittedText("(No audio file selected)" , getLocalBounds() , Justification::centred , 2) ;
  }

    //[/UserPaint]
}

void Waveform::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    scrollbar->setBounds ((getWidth() / 2) - ((getWidth() - 16) / 2), getHeight() - 8 - 12, getWidth() - 16, 12);

    //[UserResized] Add your own custom resize handling here..

    this->scrollbar->setBounds(getLocalBounds().reduced         (GUI::PAD4 , 0    )
                                               .removeFromBottom(GUI::SCROLLBARS_H)) ;

    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

// TODO: these are is from the AudioPlayback JuceDemo
void Waveform::setURL(const URL& url)
{
  this->zoomFactor          = 1.0 ;
  InputSource* input_source = nullptr;

  if      (url.isLocalFile()      ) input_source = new FileInputSource(url.getLocalFile()) ;
  else if (input_source == nullptr) input_source = new URLInputSource(url) ;

  if (input_source != nullptr)
  {
    this->thumbnail.setSource(input_source) ;

    double audio_n_secs = this->thumbnail.getTotalLength() ;
    Range<double> newRange(0.0 , audio_n_secs) ;

    this->scrollbar->setRangeLimits(newRange) ;
    setViewRange(newRange) ;
    setMarker(this->headMarker , (this->headTime = 0.0         )) ;
    setMarker(this->tailMarker , (this->tailTime = audio_n_secs)) ;
    repaint() ;

    startTimerHz(40) ;
  }
}

URL Waveform::getLastDroppedFile() const noexcept { return this->lastFileDropped ; }

void Waveform::setHeadMarker()
{
  this->headTime = jlimit((double)0.0                                 ,
                          (double)this->tailTime                      ,
                          (double)this->transport.getCurrentPosition()) ;
  setMarker(this->headMarker , this->headTime) ;
  repaint() ;
}

void Waveform::setTailMarker()
{
  this->tailTime = jlimit((double)this->headTime                      ,
                          (double)this->transport.getTotalLength()    ,
                          (double)this->transport.getCurrentPosition()) ;
  setMarker(this->tailMarker , this->tailTime) ;
  repaint() ;
}

void Waveform::setZoomFactor(float delta)
{
  double audio_n_secs = this->thumbnail.getTotalLength() ;
  this->zoomFactor    = jlimit(0.0 , 1.0 , (double)(this->zoomFactor += delta)) ;

  if (audio_n_secs > 0)
  {
    auto new_scale = jmax(0.001 , audio_n_secs * this->zoomFactor) ;
    auto time_at_centre = xToTime(getWidth() / 2.0f) ;

    setViewRange({ time_at_centre - new_scale * 0.5 , time_at_centre + new_scale * 0.5 }) ;
  }
}

void Waveform::setViewRange(Range<double> view_range)
{
  this->cursorMarker.setVisible(view_range.contains(this->transport.getCurrentPosition())) ;
  this->headMarker  .setVisible(view_range.contains(this->headTime                      )) ;
  this->tailMarker  .setVisible(view_range.contains(this->tailTime                      )) ;
  this->scrollbar->setCurrentRange(this->viewRange = view_range) ;

  setMarker(this->headMarker , this->headTime) ;
  setMarker(this->tailMarker , this->tailTime) ;
  updateCursor() ; repaint() ;
}

void Waveform::setFollowsTransport(bool should_follow) { this->isFollowingTransport = should_follow ; }

void Waveform::changeListenerCallback(ChangeBroadcaster* object_that_changed)
{
  if (object_that_changed == &(this->thumbnail)) repaint() ;
}

bool Waveform::isInterestedInFileDrag(const StringArray& files) { return true ; }

void Waveform::filesDropped(const StringArray& files , int x , int y)
{
  this->lastFileDropped = URL(File(files[0])) ;
  sendChangeMessage() ;
}

void Waveform::mouseDown(const MouseEvent& e) { mouseDrag(e) ; }

void Waveform::mouseDrag(const MouseEvent& e)
{
  if (canMoveTransport()) this->transport.setPosition(jmax(0.0 , xToTime((float)e.x))) ;
}

void Waveform::mouseUp(const MouseEvent&) { /*this->transport.start() ;*/ }

void Waveform::mouseWheelMove(const MouseEvent& , const MouseWheelDetails& wheel)
{
  double audio_n_secs        = this->thumbnail.getTotalLength() ;
  double scroll_range_begin  = this->viewRange.getStart() ;
  double scroll_range_length = this->viewRange.getLength() ;

  if (audio_n_secs > 0.0)
  {
    auto new_start = jlimit(0.0 , jmax(0.0 , audio_n_secs - scroll_range_length) ,
                     scroll_range_begin - wheel.deltaX * scroll_range_length / 10.0) ;

    if (canMoveTransport()  ) setViewRange({ new_start , new_start + scroll_range_length }) ;
    if (wheel.deltaY != 0.0f) setZoomFactor(-wheel.deltaY) ;
    repaint() ;
  }
}

void Waveform::scrollBarMoved(ScrollBar* scrollbar_that_moved , double new_range_start)
{
  if (scrollbar_that_moved == this->scrollbar.get() && canMoveTransport())
    setViewRange(this->viewRange.movedToStartAt(new_range_start)) ;
}

void Waveform::timerCallback()
{
  if (canMoveTransport()) updateCursor() ;
  else setViewRange(this->viewRange.movedToStartAt(this->transport.getCurrentPosition() -
                                                  (this->viewRange.getLength() / 2.0)   )) ;
}

float Waveform::timeToX(const double time) const
{
  if (viewRange.getLength() <= 0.0) return 0.0 ;

  return (getWidth() - GUI::PAD4) * (float)((time - this->viewRange.getStart()) / viewRange.getLength()) ;
}

double Waveform::xToTime(const float x) const
{
  return (x / (getWidth() - GUI::PAD4)) * this->viewRange.getLength() + this->viewRange.getStart() ;
}

bool Waveform::canMoveTransport() const noexcept
{
  return ! (this->isFollowingTransport && this->transport.isPlaying()) ;
}

void Waveform::updateCursor()
{
  setMarker(this->cursorMarker , this->transport.getCurrentPosition()) ;
}

void Waveform::setMarker(DrawableRectangle& marker , double time)
{
  marker.setRectangle(Rectangle<float>(timeToX(time) - 0.75f                   ,
                                       0                                       ,
                                       1.5f                                    ,
                                       (float)(getHeight() - GUI::SCROLLBARS_H))) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Waveform" componentName=""
                 parentClasses="public Component, public ChangeListener, public FileDragAndDropTarget, public ChangeBroadcaster, private ScrollBar::Listener, private Timer"
                 constructorParams="AudioFormatManager&amp; format_manager , AudioTransportSource&amp; source"
                 variableInitialisers="transport(source) , thumbnail(GUI::BIN_N_SAMPLES , format_manager , thumbnailCache)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1" initialHeight="1">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10.00000000000000000000" fill="solid: ff181818"
               hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <GENERICCOMPONENT name="scrollbar" id="5d0cd6e06ff57863" memberName="scrollbar"
                    virtualName="" explicitFocusOrder="0" pos="0.5Cc 8Rr 16M 12"
                    class="ScrollBar" params="false"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
