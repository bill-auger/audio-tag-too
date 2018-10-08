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


// names and IDs
const String APP::APP_NAME           = ProjectInfo::projectName ;
const String APP::APP_VERSION        = ProjectInfo::versionString ;
const String APP::APP_CMD            = "audio-tag-too" ;
const String APP::WORKER_THREAD_NAME = "audiotagtoo-worker" ;
const String APP::DIGITS             = "0123456789" ;
const String APP::LETTERS            = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" ;
const String APP::ALPHANUMERIC       = DIGITS + LETTERS ;
const String APP::VALID_ID_CHARS     = ALPHANUMERIC + "_- " ;
const String APP::FILTER_CHARS       = "-_.:/?=@#&[] " ;
const String APP::REPLACE_CHARS      = String::repeatedString("-" , FILTER_CHARS.length()) ;

// timers
int timer_ids[]  = { APP::TIMER_HI_ID  , APP::TIMER_MED_ID  , APP::TIMER_LO_ID  } ;
int timer_ivls[] = { APP::TIMER_HI_IVL , APP::TIMER_MED_IVL , APP::TIMER_LO_IVL } ;
const Array<int> APP::TIMER_IDS  = Array<int>(timer_ids  , N_TIMERS) ;
const Array<int> APP::TIMER_IVLS = Array<int>(timer_ivls , N_TIMERS) ;

// CLI params
const String     APP::CLI_HELP_TOKEN    = "--help" ;
const String     APP::CLI_VERSION_TOKEN = "--version" ;
const String     APP::CLI_AUDIO_TOKEN   = "--no-audio" ;
const String     APP::CLI_DIR_TOKEN     = "--dir" ;
const String     APP::CLI_FPS_TOKEN     = "--fps" ;
const String     APP::CLI_ZOOM_TOKEN    = "--zoom-scale" ;
const Identifier APP::AUDIO_KEY         = "is-audio-enabled" ;
const Identifier APP::INIT_DIR_KEY      = "initial-dir" ;
const Identifier APP::COURSE_FPS_KEY    = "course-fps" ;
const Identifier APP::FINE_FPS_KEY      = "fine-fps" ;
const Identifier APP::ZOOM_KEY          = "zoom-speed" ;


// user messages
#define APP_CMD_PAD String("").paddedLeft(' ' , APP_CMD.length())
#define HELP_USAGE_MSG    "prints this message and exits"
#define VERSION_USAGE_MSG "prints the application version string and exits"
#define AUDIO_USAGE_MSG   "disables audio output (safe mode)"
#define DIR_USAGE_MSG     "starts " + APP_NAME + " with the file browser rooted at DIRECTORY"
#define FPS_USAGE_MSG     "starts " + APP_NAME + " with integer(N) frames per second graphics update"
#define ZOOM_USAGE_MSG    "starts " + APP_NAME + " with zoom granularity scaled per decimal(N)" + \
                          "a negative number inverts the mouse wheel direction (e.g. -1.0)"
#define CLI_DIR_TOKEN_ENTRY  CLI_DIR_TOKEN  + " <DIRECTORY>"
#define CLI_FPS_TOKEN_ENTRY  CLI_FPS_TOKEN  + " <N>"
#define CLI_ZOOM_TOKEN_ENTRY CLI_ZOOM_TOKEN + " <N>"
const StringArray APP::CLI_USAGE_MSG = StringArray::fromLines(
  String("AudioTagToo Usage:\n")                                                   +
  "\n\t" + APP_CMD + " [ " + CLI_HELP_TOKEN       + " | "                          +
                             CLI_VERSION_TOKEN    + " ]"                           +
  "\n\t" + APP_CMD + " [ " + CLI_AUDIO_TOKEN      + " ]"                           +
                     " [ " + CLI_DIR_TOKEN_ENTRY  + " ]"                           +
                     " [ " + CLI_FPS_TOKEN_ENTRY  + " ]"                           +
                     " [ " + CLI_ZOOM_TOKEN_ENTRY + " ]"                           +
  "\n\n\n\tINFORMATION:"                                                           +
  "\n\n\t\t"               + CLI_HELP_TOKEN       + "\n\t\t\t" + HELP_USAGE_MSG    +
  "\n\n\t\t"               + CLI_VERSION_TOKEN    + "\n\t\t\t" + VERSION_USAGE_MSG +
  "\n\n\n\tFEATURE SWITCHES:"                                                      +
  "\n\n\t\t"               + CLI_AUDIO_TOKEN      + "\n\t\t\t" + AUDIO_USAGE_MSG   +
  "\n\n\n\tCONFIGURATION:"                                                         +
  "\n\n\t\t"               + CLI_DIR_TOKEN_ENTRY  + "\n\t\t\t" + DIR_USAGE_MSG     +
  "\n\n\t\t"               + CLI_FPS_TOKEN_ENTRY  + "\n\t\t\t" + FPS_USAGE_MSG     +
  "\n\n\t\t"               + CLI_ZOOM_TOKEN_ENTRY + "\n\t\t\t" + ZOOM_USAGE_MSG    ) ;


// filesystem
const String APP::IconFilename()    { return APP_CMD + ".png"                         ; }
const String APP::DesktopFilename() { return APP_CMD + ".desktop"                     ; }
const String APP::IconsPath()       { return ".local/share/icons/hicolor/48x48/apps/" ; }
const String APP::AppsPath()        { return ".local/share/applications/"             ; }
const File   APP::HomeDir()         { return File::getSpecialLocation(File::userHomeDirectory           ) ; }
const File   APP::MusicDir()        { return File::getSpecialLocation(File::userMusicDirectory          ) ; }
const File   APP::AppdataDir()      { return File::getSpecialLocation(File::userApplicationDataDirectory) ; }
const File   APP::BinFile()         { return File::getSpecialLocation(File::currentExecutableFile       ) ; }
const File   APP::IconFile()        { return HomeDir().getChildFile  (IconsPath() + IconFilename()   ) ; }
const File   APP::DesktopFile()     { return HomeDir().getChildFile  (AppsPath()  + DesktopFilename()) ; }
const String APP::DesktopFileText() { return String("[Desktop Entry]\r\n")                          +
                                                    "Name=AudioTagToo\r\n"                          +
                                                    "GenericName=\r\n"                              +
                                                    "Comment=Clip and stitch audio samples\r\n"     +
                                                    "Categories=AudioVideo;\r\n"                    +
                                                    "Exec=" + BinFile() .getFullPathName() + "\r\n" +
                                                    "Icon=" + IconFile().getFullPathName() + "\r\n" +
                                                    "StartupNotify=true\r\n"                        +
                                                    "Terminal=false\r\n"                            +
                                                    "Type=Application\r\n"                          ; }
