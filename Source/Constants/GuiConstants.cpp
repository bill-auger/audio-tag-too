
#include "GuiConstants.h"


// common
const uint8 GUI::PAD       = 4 ;
const uint8 GUI::PAD2      = PAD * 2 ;
const uint8 GUI::PAD4      = PAD * 4 ;
const float GUI::FONT_SIZE = 16.0 ;

// MainContent
const uint8  GUI::BORDERS_W        = 2 ;
const uint8  GUI::TITLEBAR_H       = 24 ;
const uint16 GUI::WINDOW_W         = 768 - BORDERS_W ;              // jucer 766
const uint16 GUI::WINDOW_H         = 768 - BORDERS_W - TITLEBAR_H ; // jucer 742
const Colour GUI::WINDOW_BG_COLOR  = Colour(0xFF404040) ;
const Colour GUI::BROWSER_BG_COLOR = Colour(0xFF606060) ;
const int    GUI::TITLEBAR_BTNS    = DocumentWindow::allButtons ;

// Waveform
const uint16 GUI::BIN_N_SAMPLES     = 512 ;
const uint8  GUI::SCROLLBARS_H      = 12 ;
const Colour GUI::WAVE_BG_COLOR     = Colour(0xFF000000) ;
const Colour GUI::WAVE_FG_COLOR     = Colour(0xFF80FF80) ;
const Colour GUI::CURSOR_COLOR      = Colour(0xFFFFFF80) ;
const Colour GUI::HEAD_COLOR        = Colour(0xFF8080FF) ;
const Colour GUI::TAIL_COLOR        = Colour(0xFFFF8080) ;
const uint8  GUI::COURSE_FPS        = 8 ;
const uint8  GUI::FINE_FPS          = 12 ;
const String GUI::UPPER_WAVEFORM_ID = "waveform-upper" ;
const String GUI::LOWER_WAVEFORM_ID = "waveform-lower" ;
const String GUI::NO_FILE_TEXT      = "(No audio file selected)" ;

// user messages
const String GUI::DEVICE_ERROR_TITLE         = "Audio Device Error" ;
const String GUI::DEVICE_ERROR_MSG           = "Audio Device Error\n\nCan not find a usable audio playback device" ;
const String GUI::FILESYSTEM_WRITE_ERROR_MSG = "I/O Error\n\nCan not write to filesystem" ;
const String GUI::STORAGE_WRITE_ERROR_MSG    = "I/O Error\n\nCan not write: " ;
