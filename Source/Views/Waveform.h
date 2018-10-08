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
                  public ChangeListener,
                  public FileDragAndDropTarget,
                  public ChangeBroadcaster,
                  private ScrollBar::Listener,
                  private Timer
{
public:
    //==============================================================================
    Waveform (AudioFormatManager& format_manager , AudioTransportSource& source);
    ~Waveform();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  void setURL              (const URL& url) ;
  void setZoomFactor       (float delta) ;
  void setViewRange        (Range<double> view_range) ;
  void setFollowsTransport (bool should_follow) ;
  URL  getLastDroppedFile  (void) const noexcept ;
  void setHeadMarker       (void) ;
  void setTailMarker       (void) ;

  void changeListenerCallback(ChangeBroadcaster* object_that_changed)             override ;
  bool isInterestedInFileDrag(const StringArray& files)                           override ;
  void filesDropped          (const StringArray& files , int x , int y)           override ;
  void mouseDown             (const MouseEvent& e)                                override ;
  void mouseDrag             (const MouseEvent& e)                                override ;
  void mouseUp               (const MouseEvent&)                                  override ;
  void mouseWheelMove        (const MouseEvent& , const MouseWheelDetails& wheel) override ;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  AudioTransportSource& transport ;
  AudioThumbnailCache   thumbnailCache { 5 } ;
  AudioThumbnail        thumbnail ;
  float                 zoomFactor ;
  Range<double>         viewRange ;
  bool                  isFollowingTransport ;
  URL                   lastFileDropped ;

  DrawableRectangle cursorMarker ;
  DrawableRectangle headMarker   ; double headTime ;
  DrawableRectangle tailMarker   ; double tailTime ;

  void scrollBarMoved(ScrollBar* scrollbar_that_moved , double new_range_start) override ;
  void timerCallback (void)                                                     override ;

  float  timeToX         (const double time) const ;
  double xToTime         (const float x)     const ;
  bool   canMoveTransport(void)              const noexcept ;
  void   updateCursor    (void) ;
  void   setMarker       (DrawableRectangle& marker , const double time) ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ScrollBar> scrollbar;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Waveform)
};

//[EndFile] You can add extra defines here...
//[/EndFile]