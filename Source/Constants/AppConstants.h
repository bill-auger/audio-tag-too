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


// disable standard features
#ifdef DEBUG
  #define QUIT_BEFORE_MAIN_LOOP 0
  #define QUIT_AFTER_MAIN_LOOP  0
  #define DISABLE_MEDIA         0
  #define SUPRESS_ALERTS        0
#endif // DEBUG


#if QUIT_BEFORE_MAIN_LOOP
  #define DEBUG_QUIT_BEFORE_MAIN_LOOP                                              \
    Trace::TraceEvent("forced quit per 'QUIT_BEFORE_MAIN_LOOP'") ; quit() ; return ;
#else // QUIT_BEFORE_MAIN_LOOP
  #define DEBUG_QUIT_BEFORE_MAIN_LOOP ;
#endif // QUIT_BEFORE_MAIN_LOOP

#if QUIT_AFTER_MAIN_LOOP
  #define DEBUG_QUIT_AFTER_MAIN_LOOP                                                  \
    String quit_msg = "forced quit per 'DEBUG_QUIT_AFTER_MAIN_LOOP'" ;                \
    if (timer_id == APP::TIMER_LO_ID) { Trace::TraceEvent(quit_msg) ; quit() ; } else
#else // QUIT_AFTER_MAIN_LOOP
  #define DEBUG_QUIT_AFTER_MAIN_LOOP ;
#endif // QUIT_AFTER_MAIN_LOOP


#include "../../JuceLibraryCode/JuceHeader.h"


/** the APP class defines configuration and runtime constants
        pertaining to the core application and business logic */
class APP
{
public:

  // names and IDs
  static const String APP_NAME ;
  static const String APP_VERSION ;
  static const String APP_CMD ;
  static const String WORKER_THREAD_NAME ;

  static const String DIGITS ;
  static const String LETTERS ;
  static const String ALPHANUMERIC ;
  static const String VALID_ID_CHARS ;
  static const String FILTER_CHARS ;
  static const String REPLACE_CHARS ;

  // timers
  static const int        N_TIMERS     = 3 ; // ASSERT: number of *_TIMER_IDs defined below
  static const int        TIMER_HI_ID  = 1 ; static const int        TIMER_HI_IVL  = 125 ;
  static const int        TIMER_MED_ID = 2 ; static const int        TIMER_MED_IVL = 500 ;
  static const int        TIMER_LO_ID  = 3 ; static const int        TIMER_LO_IVL  = 2000 ;
  static const Array<int> TIMER_IDS ;        static const Array<int> TIMER_IVLS ;

  // CLI params
  static const String CLI_HELP_TOKEN ;
  static const String CLI_VERSION_TOKEN ;
  static const String CLI_DIR_TOKEN ;
  static const String CLI_FPS_TOKEN ;

  // runtime constants
  static const StringArray CLI_USAGE_MSG ;

  // filesystem
  static const String IconFilename()    ;
  static const String DesktopFilename() ;
  static const String IconsPath()       ;
  static const String AppsPath()        ;
  static const File   HomeDir()         ;
  static const File   MusicDir()        ;
  static const File   AppdataDir()      ;
  static const File   BinFile()         ;
  static const File   IconFile()        ;
  static const File   DesktopFile()     ;
  static const String DesktopFileText() ;
} ;
