
#include "GuiConstants.h"


// common
const int   GUI::PAD       = 4 ;
const int   GUI::PAD2      = PAD * 2 ;
const int   GUI::PAD4      = PAD * 4 ;
const float GUI::FONT_SIZE = 16.0 ;

// MainWindow
const int    GUI::BORDERS_W       = 2 ;
const int    GUI::TITLEBAR_H      = 24 ;
const int    GUI::WINDOW_W        = 768 - BORDERS_W ;              // jucer 766
const int    GUI::WINDOW_H        = 768 - BORDERS_W - TITLEBAR_H ; // jucer 742
const Colour GUI::WINDOW_BG_COLOR = Colour(0xFF404040) ;
const int    GUI::TITLEBAR_BTNS   = DocumentWindow::minimiseButton | DocumentWindow::closeButton ; // allButtonsallButtons

// Waveform
const int    GUI::BIN_N_SAMPLES = 512 ;
const int    GUI::SCROLLBARS_H  = 12 ;
const Colour GUI::WAVE_BG_COLOR = Colour(0xFF000000) ;
const Colour GUI::WAVE_FG_COLOR = Colour(0xFF80FF80) ;
const Colour GUI::CURSOR_COLOR  = Colour(0xFFFFFF80) ;
const Colour GUI::HEAD_COLOR    = Colour(0xFF8080FF) ;
const Colour GUI::TAIL_COLOR    = Colour(0xFFFF8080) ;
