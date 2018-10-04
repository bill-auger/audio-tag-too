
#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"


/** the GUI class defines configuration and runtime constants
        pertaining to graphical elements                      */
class GUI
{
public:

  // common
  static const uint8 PAD ;
  static const uint8 PAD2 ;
  static const uint8 PAD4 ;
  static const float FONT_SIZE ;

  // MainWindow
  static const uint8  BORDERS_W ;
  static const uint8  TITLEBAR_H ;
  static const uint16 WINDOW_W ;
  static const uint16 WINDOW_H ;
  static const Colour WINDOW_BG_COLOR ;
  static const int    TITLEBAR_BTNS ;

  // Waveform
  static const uint16 BIN_N_SAMPLES ;
  static const uint8  SCROLLBARS_H ;
  static const Colour WAVE_BG_COLOR ;
  static const Colour WAVE_FG_COLOR ;
  static const Colour CURSOR_COLOR ;
  static const Colour HEAD_COLOR ;
  static const Colour TAIL_COLOR ;
  static const uint8  COURSE_FPS ;
  static const uint8  FINE_FPS ;
  static const String UPPER_WAVEFORM_ID ;
  static const String LOWER_WAVEFORM_ID ;
  static const String NO_FILE_TEXT ;
} ;
