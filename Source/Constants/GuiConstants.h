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
/*
  // helpers
  static void ConfigureTextEditor(TextEditor* a_text_editor , TextEditor::Listener* a_text_listener ,
                                  int         max_n_chars   , const String          allowed_chars   ) ;
*/

  // common
  static const uint8  PAD ;
  static const uint8  PAD2 ;
  static const uint8  PAD4 ;
  static const uint8  STROKE_W ;
  static const float  FONT_SIZE ;
  static const Colour TEXT_NORMAL_COLOR ;
  static const Colour TEXT_DISABLED_COLOR ;
  static const Colour TEXT_INVALID_COLOR ;
  static const Colour TEXT_HILITE_COLOR ;
  static const Colour TEXT_HILITEBG_COLOR ;
  static const Colour TEXT_CARET_COLOR ;
  static const Colour TEXT_FOCUS_COLOR ;
  static const Colour TEXT_SHADOW_COLOR ;
  static const Colour TEXT_BG_COLOR ;
  static const Colour COMBOBOX_INVALID_COLOR ;

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
  static const int CLIPS_TABLE_IDX ;
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

  // ClipsTable
  static const int        TREE_ITEM_H ;
  static const Identifier METADATA_BTN_ID ;
  static const String     FILE_ITEM_LABEL ;
  static const String     BEGIN_ITEM_LABEL ;
  static const String     END_ITEM_LABEL ;
  static const String     DURATION_ITEM_LABEL ;
  static const uint8      MAX_CLIPNAME_TEXTEDITOR_N_CHARS ;
  static const uint8      MAX_KEY_TEXTEDITOR_N_CHARS ;
  static const uint16     MAX_VALUE_TEXTEDITOR_N_CHARS ;
  static const String     NEW_CLIPNAME_TEXT ;
  static const String     NEW_FIRST_KEY_TEXT ;
  static const String     NEW_KEY_TEXT ;
  static const String     NEW_VALUE_TEXT ;
  static const String     LOAD_BTN_HOVERTEXT ;
  static const String     EDIT_BTN_HOVERTEXT ;
  static const String     DELETE_BTN_HOVERTEXT ;
  static const String     METADATA_BTN_HOVERTEXT ;

  // Alert
  enum         AlertType { ALERT_TYPE_WARNING , ALERT_TYPE_ERROR } ;
  static const String    MODAL_WARNING_TITLE ;
  static const String    MODAL_ERROR_TITLE ;

  // user messages
  static const String DEVICE_ERROR_MSG ;
  static const String FILESYSTEM_WRITE_ERROR_MSG ;
  static const String STORAGE_WRITE_ERROR_MSG ;
  static const String ID_COLLISION_ERROR_MSG ;
} ;
