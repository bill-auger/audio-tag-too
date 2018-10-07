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


#include "AppConstants.h"
#include "GuiConstants.h"


// common
const uint8 GUI::PAD       = 4 ;
const uint8 GUI::PAD2      = PAD * 2 ;
const uint8 GUI::PAD4      = PAD * 4 ;
const uint8 GUI::STROKE_W  = 1 ;
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
const uint16 GUI::CACHE_N_THUMBS      = 512 ;
const uint16 GUI::BIN_N_SAMPLES       = 512 ;
const uint8  GUI::SCROLLBARS_H        = 12 ;
const Colour GUI::WAVE_BG_COLOR       = Colour(0xFF000000) ;
const Colour GUI::WAVE_FG_COLOR       = Colour(0xFF80FF80) ;
const Colour GUI::WAVE_SELECTED_COLOR = Colour(0xFF202040) ;
const Colour GUI::CURSOR_COLOR        = Colour(0xFFFFFF80) ;
const Colour GUI::HEAD_COLOR          = Colour(0xFF8080FF) ;
const Colour GUI::TAIL_COLOR          = Colour(0xFFFF8080) ;
const uint8  GUI::COURSE_FPS          = 8 ;
const uint8  GUI::FINE_FPS            = 12 ;
const String GUI::UPPER_WAVEFORM_ID   = "waveform-upper" ;
const String GUI::LOWER_WAVEFORM_ID   = "waveform-lower" ;
const String GUI::NO_FILE_TEXT        = "(No audio file selected)" ;

// Alert
const String GUI::MODAL_WARNING_TITLE = APP::APP_NAME + " Warning" ;
const String GUI::MODAL_ERROR_TITLE   = APP::APP_NAME + " Error" ;

// user messages
const String GUI::DEVICE_ERROR_MSG           = "Audio Device Error\n\nCan not find a usable audio playback device" ;
const String GUI::FILESYSTEM_WRITE_ERROR_MSG = "I/O Error\n\nCan not write to filesystem" ;
const String GUI::STORAGE_WRITE_ERROR_MSG    = "I/O Error\n\nCan not write: " ;
