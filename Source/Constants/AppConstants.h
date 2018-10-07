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


#pragma once


// disable standard features
#ifdef DEBUG
  #define DISABLE_MEDIA 0
#endif // DEBUG


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
