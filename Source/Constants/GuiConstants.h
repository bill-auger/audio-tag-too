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
  static const uint8 STROKE_W ;
  static const float FONT_SIZE ;

  // MainWindow
  static const uint8  BORDERS_W ;
  static const uint8  TITLEBAR_H ;
  static const uint16 WINDOW_W ;
  static const uint16 WINDOW_H ;
  static const Colour WINDOW_BG_COLOR ;
  static const int    TITLEBAR_BTNS ;
  static const int    N_DASH_LENGTHS = 2 ; // ASSERT: number of floats defiend in DASH_LENGTHS
  static const float  DASH_LENGTHS[N_DASH_LENGTHS] ;

  // Waveform
  static const uint16 CACHE_N_THUMBS ;
  static const uint16 BIN_N_SAMPLES ;
  static const uint8  SCROLLBARS_H ;
  static const Colour WAVE_BG_COLOR ;
  static const Colour WAVE_FG_COLOR ;
  static const Colour WAVE_SELECTED_COLOR ;
  static const Colour CURSOR_COLOR ;
  static const Colour HEAD_COLOR ;
  static const Colour TAIL_COLOR ;
  static const uint8  COURSE_FPS ;
  static const uint8  FINE_FPS ;
  static const String FULL_WAVEFORM_ID ;
  static const String CLIP_WAVEFORM_ID ;
  static const String NO_FILE_TEXT ;

  // TabbedComponent
  static const int FILE_BROWSER_IDX ;
  static const int CLIPS_IDX ;
  static const int COMPILATIONS_IDX ;
  static const int DEVICE_SELECTOR_IDX ;

  // FileBrowserComponent
  static const Colour TABPANEL_BG_COLOR ;
  static const Colour TABPANEL_FG_COLOR ;
  static const Colour FILEPATH_BG_COLOR ;
  static const Colour FILEPATH_FG_COLOR ;
  static const Colour FILEPATH_ARROW_COLOR ;
  static const Colour FILENAME_BG_COLOR ;
  static const Colour FILENAME_FG_COLOR ;
  static const Colour BROWSER_BG_COLOR ;
  static const Colour BROWSER_FG_COLOR ;
  static const Colour BROWSER_SELECTED_BG_COLOR ;
  static const Colour BROWSER_SELECTED_FG_COLOR ;

  // clips/compilations TreeViewItems
  static const int    TREE_ITEM_H ;
  static const String FILE_ITEM_LABEL ;
  static const String BEGIN_ITEM_LABEL ;
  static const String END_ITEM_LABEL ;

  // AudioTagTooAlert
  enum         AlertType { ALERT_TYPE_WARNING , ALERT_TYPE_ERROR } ;
  static const String    MODAL_WARNING_TITLE ;
  static const String    MODAL_ERROR_TITLE ;

  // user messages
  static const String DEVICE_ERROR_MSG ;
  static const String FILESYSTEM_WRITE_ERROR_MSG ;
  static const String STORAGE_WRITE_ERROR_MSG ;
  static const String ID_COLLISION_ERROR_MSG ;
} ;
