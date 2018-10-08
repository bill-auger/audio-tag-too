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


#include "../Constants/GuiConstants.h"
#include "../Trace/TraceWaveform.h"

//[/Headers]

#include "Waveform.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Waveform::Waveform (AudioFormatManager& format_manager , AudioTransportSource& source)
    : transport(source) , thumbnailCache(GUI::CACHE_N_THUMBS) , thumbnail(GUI::BIN_N_SAMPLES , format_manager , thumbnailCache) , zoomScaleFactor(1.0)
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

// DEBUG_TRACE_WAVEFORM_PAINT

  // scope background
  g.setColour(GUI::WAVE_BG_COLOR) ;
  g.fillRect(thumb_rect) ;

  // selected region
  int selection_w = this->tailMarker.getX() - this->headMarker.getRight() ;
  g.setColour(GUI::WAVE_SELECTED_COLOR) ;
  g.fillRect(this->headMarker.getBounds().withWidth(selection_w)) ;

  // waveform
  g.setColour(GUI::WAVE_FG_COLOR) ;
  if (this->thumbnail.getTotalLength() > 0.0)
  {
    double begin_secs = this->viewRange.getStart() ;
    double end_secs   = this->viewRange.getEnd  () ;

    this->thumbnail.drawChannels(g , thumb_rect , begin_secs , end_secs , 1.0f) ;
  }
  else
  {
    g.setFont(GUI::FONT_SIZE) ;
    g.drawFittedText(GUI::NO_FILE_TEXT , getLocalBounds() , Justification::centred , 2) ;
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

/* public getters/setters */

void Waveform::setUrl(const Url& url)
{
  this->currentZoom         = 1.0 ;
  InputSource* input_source = (url.isLocalFile())                                                ?
                              static_cast<InputSource*>(new FileInputSource(url.getLocalFile())) :
                              static_cast<InputSource*>(new URLInputSource (url)               ) ;

  if (input_source != nullptr)
  {
    this->thumbnail.setSource(input_source) ;

    double audio_n_secs = this->thumbnail.getTotalLength() ;
    Range<double> new_range(0.0 , audio_n_secs) ;

    setMarker(this->headMarker , (this->headTime = 0.0         )) ;
    setMarker(this->tailMarker , (this->tailTime = audio_n_secs)) ;
    this->scrollbar->setRangeLimits(new_range) ;
    setViewRange(new_range) ;
  }
}

void Waveform::resetPosition() { setPosition(this->headTime) ; }

double Waveform::getHeadTime() const { return this->headTime ; }

double Waveform::getTailTime() const { return this->tailTime ; }

void Waveform::setHeadMarker()
{
  this->headTime = jlimit((double)0.0                                 ,
                          (double)this->tailTime                      ,
                          (double)this->transport.getCurrentPosition()) ;

  setMarker(this->headMarker , this->headTime) ;
  repaint() ;

DEBUG_TRACE_WAVEFORM_SET_HEAD_OR_TAIL("headMarker")
}

void Waveform::setTailMarker()
{
  this->tailTime = jlimit((double)this->headTime                       ,
                          (double)this->transport.getLengthInSeconds() ,
                          (double)this->transport.getCurrentPosition() ) ;

  setMarker(this->tailMarker , this->tailTime) ;
  repaint() ;

DEBUG_TRACE_WAVEFORM_SET_HEAD_OR_TAIL("tailMarker")
}

void Waveform::setZoomFactor(double zoom_scaling_factor)
{
DEBUG_TRACE_WAVEFORM_SET_ZOOM_FACTOR

  this->zoomFactor = zoom_scaling_factor ;
}

double Waveform::getZoomScale() const { return this->currentZoom ; }


/* event handlers */

void Waveform::changeListenerCallback(ChangeBroadcaster* object_that_changed)
{
  if (object_that_changed == &(this->thumbnail)) repaint() ;
}

void Waveform::mouseDown(const MouseEvent& evt) { setPosition(xToTime((float)evt.x)) ; }

void Waveform::mouseDrag(const MouseEvent& evt) { setPosition(xToTime((float)evt.x)) ; }

void Waveform::mouseUp(const MouseEvent& evt)
{
  if (evt.mods.isRightButtonDown()) this->transport.start() ;
}

void Waveform::mouseWheelMove(const MouseEvent& , const MouseWheelDetails& wheel)
{
  double audio_n_secs = this->thumbnail.getTotalLength() ;

  if (audio_n_secs <= 0.0 || getName() == GUI::FULL_WAVEFORM_ID) return ;

  // set pan
  if (wheel.deltaX != 0.0f)
  {
    double visible_begin_time   = this->viewRange.getStart() ;
    double visible_n_secs       = this->viewRange.getLength() ;
    double requested_begin_time = visible_begin_time - wheel.deltaX * visible_n_secs / 10.0 ;
    double cropped_n_secs       = audio_n_secs - visible_n_secs ;
    double max_begin_time       = jmax(0.0 , cropped_n_secs) ;
    double new_begin_time       = jlimit(0.0 , max_begin_time , requested_begin_time) ;
    double new_n_secs           = new_begin_time + visible_n_secs ;

    setViewRange({ new_begin_time , new_n_secs }) ;
  }

  // set zoom level
  if (wheel.deltaY != 0.0f)
  {
    double zoom_delta      = (double)wheel.deltaY * this->zoomFactor ;
    this->currentZoom      = jlimit(0.0 , 1.0 , this->currentZoom - zoom_delta) ;
    double new_n_secs      = jmax(0.0 , total_n_secs * this->currentZoom) ;
    double mouse_x         = getMouseXYRelative().x ;
    double mouse_time      = xToTime(mouse_x) ;
    double mouse_x_percent = (mouse_x - GUI::PAD2) / (getWidth() - GUI::PAD4) ;
    double new_begin_time  = mouse_time - (     mouse_x_percent  * new_n_secs) ;
    double new_end_time    = mouse_time + ((1 - mouse_x_percent) * new_n_secs) ;

DEBUG_TRACE_WAVEFORM_MOUSE_WHEEL_MOVE

    setViewRange({ new_begin_time , new_end_time }) ;
  }
}

void Waveform::scrollBarMoved(ScrollBar* scrollbar_that_moved , double range_start)
{
  if (scrollbar_that_moved == this->scrollbar.get())
  { setViewRange(this->viewRange.movedToStartAt(range_start)) ; repaint() ; }
}

void Waveform::timerCallback() { updateCursor() ; }


/* private getters/setters */

void Waveform::setPosition(double time)
{
  this->transport.setPosition(jmax(0.0 , time)) ; updateCursor() ;
}

void Waveform::setMarker(DrawableRectangle& marker , double time)
{
  marker.setRectangle(Rectangle<float>(timeToX(time) - 0.75f                                   ,
                                       (float)GUI::STROKE_W                                    ,
                                       1.5f                                                    ,
                                       (float)(getHeight() - GUI::SCROLLBARS_H - GUI::STROKE_W))) ;
}

void Waveform::setViewRange(Range<double> view_range)
{
  this->cursorMarker.setVisible(view_range.contains(this->transport.getCurrentPosition())) ;
  this->headMarker  .setVisible(view_range.contains(this->headTime                      )) ;
  this->tailMarker  .setVisible(view_range.contains(this->tailTime                      )) ;

DEBUG_TRACE_WAVEFORM_SET_VIEWRANGE

  this->scrollbar->setCurrentRange(this->viewRange = view_range) ;
  this->scrollbar->setVisible(this->currentZoom < 1.0) ;

  setMarker(this->headMarker , this->headTime) ;
  setMarker(this->tailMarker , this->tailTime) ;
  updateCursor() ;
}


/* helpers */

float Waveform::timeToX(const double time) const
{
  double offset_n_secs  = time - this->viewRange.getStart() ;
  double visible_n_secs = this->viewRange.getLength() ;
  double scale_x        = (visible_n_secs == 0.0) ? 0.0 : offset_n_secs / visible_n_secs ;
  double view_l         = (double)GUI::PAD2 ;
  double view_r         = (double)getWidth() - (double)GUI::PAD2 ;
  double view_w         = (double)getWidth() - (double)GUI::PAD4 ;

  return (scale_x <= 0.0) ? view_l :
         (scale_x >= 1.0) ? view_r : view_w * scale_x ;
}

double Waveform::xToTime(const float x) const
{
  double view_r      = (double)getWidth() - (double)GUI::PAD2 ;
  double view_w      = (double)getWidth() - (double)GUI::PAD4 ;
  double scale_x     = x / view_w ;
  double begin_time  = this->viewRange.getStart() ;
  double end_time    = this->viewRange.getLength() ;
  double view_n_secs = scale_x * end_time ;

  return (scale_x <= 0.0) ? 0.0      :
         (scale_x >= 1.0) ? end_time : begin_time + view_n_secs ;
}

void Waveform::updateCursor()
{
  setMarker(this->cursorMarker , this->transport.getCurrentPosition()) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Waveform" componentName=""
                 parentClasses="public Component, private ChangeListener, public ChangeBroadcaster, private ScrollBar::Listener, public Timer"
                 constructorParams="AudioFormatManager&amp; format_manager , AudioTransportSource&amp; source"
                 variableInitialisers="transport(source) , thumbnailCache(GUI::CACHE_N_THUMBS) , thumbnail(GUI::BIN_N_SAMPLES , format_manager , thumbnailCache) , zoomScaleFactor(1.0)"
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
