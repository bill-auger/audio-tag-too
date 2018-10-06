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
