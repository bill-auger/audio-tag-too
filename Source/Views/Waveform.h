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


#pragma once

//[Headers]     -- You can add your own extra header files here --

#include "../../JuceLibraryCode/JuceHeader.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  Waveform is the audio wave graph for the JuceBoilerplate application.
                                                                    //[/Comments]
*/
class Waveform  : public Component,
                  private ChangeListener,
                  public ChangeBroadcaster,
                  private ScrollBar::Listener,
                  public Timer
{
public:
    //==============================================================================
    Waveform (AudioFormatManager& format_manager , AudioTransportSource& source);
    ~Waveform();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  // getters/setters
  void   setUrl       (const Url& url) ;
  void   resetPosition(void) ;
  double getHeadTime  (void) const ;
  double getTailTime  (void) const ;
  void   setHeadMarker(void) ;
  void   setTailMarker(void) ;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  // event handlers
  void changeListenerCallback(ChangeBroadcaster* object_that_changed)               override ;
  void mouseDown             (const MouseEvent& e)                                  override ;
  void mouseDrag             (const MouseEvent& e)                                  override ;
  void mouseUp               (const MouseEvent&)                                    override ;
  void mouseWheelMove        (const MouseEvent& , const MouseWheelDetails& wheel)   override ;
  void scrollBarMoved        (ScrollBar* scrollbar_that_moved , double range_start) override ;
  void timerCallback         (void)                                                 override ;

  // getters/setters
  void setPosition (double time) ;
  void setViewRange(Range<double> view_range) ;

  // helpers
  float  timeToX     (const double time) const ;
  double xToTime     (const float x)     const ;
  void   updateCursor(void) ;
  void   setMarker   (DrawableRectangle& marker , const double time) ;

  // vars
  AudioTransportSource& transport ;
  AudioThumbnailCache   thumbnailCache ;
  AudioThumbnail        thumbnail ;
  double                zoomFactor ;
  Range<double>         viewRange ;
  DrawableRectangle     cursorMarker ;
  DrawableRectangle     headMarker ; double headTime ;
  DrawableRectangle     tailMarker ; double tailTime ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ScrollBar> scrollbar;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Waveform)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
