
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


/** the GUI class defines configuration and runtime constants
        pertaining to graphical elements                      */
class GUI
{
public:

  // common
  static const int   PAD ;
  static const int   PAD2 ;
  static const int   PAD4 ;
  static const float FONT_SIZE ;

  // MainWindow
  static const int    BORDERS_W ;
  static const int    TITLEBAR_H ;
  static const int    WINDOW_W ;
  static const int    WINDOW_H ;
  static const Colour WINDOW_BG_COLOR ;
  static const int    TITLEBAR_BTNS ;

  // Waveform
  static const int    BIN_N_SAMPLES ;
  static const int    SCROLLBARS_H ;
  static const Colour WAVE_BG_COLOR ;
  static const Colour WAVE_FG_COLOR ;
  static const Colour CURSOR_COLOR ;
  static const Colour HEAD_COLOR ;
  static const Colour TAIL_COLOR ;
} ;
