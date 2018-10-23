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


#include "AppConstants.h"
#include "GuiConstants.h"


// common
const uint8 GUI::PAD       = 4 ;
const uint8 GUI::PAD2      = PAD * 2 ;
const uint8 GUI::PAD4      = PAD * 4 ;
const uint8 GUI::STROKE_W  = 1 ;
const float GUI::FONT_SIZE = 16.0 ;

// MainContent
const uint8  GUI::BORDERS_W                    = 2 ;
const uint8  GUI::TITLEBAR_H                   = 24 ;
const uint16 GUI::WINDOW_W                     = 768 - BORDERS_W ;              // jucer 766
const uint16 GUI::WINDOW_H                     = 768 - BORDERS_W - TITLEBAR_H ; // jucer 742
const Colour GUI::WINDOW_BG_COLOR              = Colour(0xFF404040) ;
const int    GUI::TITLEBAR_BTNS                = DocumentWindow::allButtons ;
const float  GUI::DASH_LENGTHS[N_DASH_LENGTHS] = { 8.0f , 8.0f } ;

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
const String GUI::FULL_WAVEFORM_ID    = "full-waveform" ;
const String GUI::CLIP_WAVEFORM_ID    = "clip-waveform" ;
const String GUI::NO_FILE_TEXT        = "(No audio file selected)" ;

// TabbedComponent
const int GUI::FILE_BROWSER_IDX    = 0 ;
const int GUI::CLIPS_TABLE_IDX     = 1 ;
const int GUI::DEVICE_SELECTOR_IDX = 2 ;

// FileBrowserComponent
const Colour GUI::TABPANEL_BG_COLOR         = Colour(0xFF303030) ;
const Colour GUI::TABPANEL_FG_COLOR         = Colour(0xFF808080) ;
const Colour GUI::FILEPATH_BG_COLOR         = Colour(0xFF606060) ;
const Colour GUI::FILEPATH_FG_COLOR         = Colour(0xFFFFFFFF) ;
const Colour GUI::FILEPATH_ARROW_COLOR      = Colour(0xFF80FF80) ;
const Colour GUI::FILENAME_BG_COLOR         = Colour(0xFF000000) ;
const Colour GUI::FILENAME_FG_COLOR         = Colour(0xFFFFFFFF) ;
const Colour GUI::BROWSER_BG_COLOR          = Colour(0xFF000000) ;
const Colour GUI::BROWSER_FG_COLOR          = Colour(0xFFFFFFFF) ;
const Colour GUI::BROWSER_SELECTED_BG_COLOR = Colour(0xFF404040) ;
const Colour GUI::BROWSER_SELECTED_FG_COLOR = Colour(0xFF40FF40) ;

// ClipsTable::ClipItem
const int    GUI::TREE_ITEM_H      = 24 ;
const String GUI::FILE_ITEM_LABEL  = "Source: " ;
const String GUI::BEGIN_ITEM_LABEL = "Beginning: " ;
const String GUI::END_ITEM_LABEL   = "Ending: " ;

// AudioTagTooAlert
const String GUI::MODAL_WARNING_TITLE = APP::APP_NAME + " Warning" ;
const String GUI::MODAL_ERROR_TITLE   = APP::APP_NAME + " Error" ;

// user messages
const String GUI::DEVICE_ERROR_MSG           = "Audio Device Error\n\nCan not find a usable audio playback device" ;
const String GUI::FILESYSTEM_WRITE_ERROR_MSG = "I/O Error\n\nCan not write to filesystem" ;
const String GUI::STORAGE_WRITE_ERROR_MSG    = "I/O Error\n\nCan not write: " ;
const String GUI::ID_COLLISION_ERROR_MSG     = "ID Collision\n\nCan not create an entry for this file. The path/file name is ambiguous with another entry." ;
