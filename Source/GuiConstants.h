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
