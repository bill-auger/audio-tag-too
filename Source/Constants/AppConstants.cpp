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

// CLI params
const String APP::CLI_HELP_TOKEN    = "--help" ;
const String APP::CLI_VERSION_TOKEN = "--version" ;
const String APP::CLI_DIR_TOKEN     = "--dir" ;
const String APP::CLI_FPS_TOKEN     = "--fps" ;

// timers
int timer_ids[]  = { APP::TIMER_HI_ID  , APP::TIMER_MED_ID  , APP::TIMER_LO_ID  } ;
int timer_ivls[] = { APP::TIMER_HI_IVL , APP::TIMER_MED_IVL , APP::TIMER_LO_IVL } ;
const Array<int> APP::TIMER_IDS  = Array<int>(timer_ids  , N_TIMERS) ;
const Array<int> APP::TIMER_IVLS = Array<int>(timer_ivls , N_TIMERS) ;

// runtime constants
#define APP_CMD_PAD String("").paddedLeft(' ' , APP_CMD.length())
const StringArray APP::CLI_USAGE_MSG = StringArray::fromLines(
    String("AudioTagToo Usage:\n")                                                                                                              +
    "\n\t" + APP_CMD     + " [ " + CLI_HELP_TOKEN                 + " | "                                                                       +
                                   CLI_VERSION_TOKEN              + " ]"                                                                        +
    "\n\t" + APP_CMD     + " [ " + CLI_DIR_TOKEN                  + " <DIRECTORY> ]"                                                            +
    "\n\t" + APP_CMD     + " [ " + CLI_FPS_TOKEN                  + " <N> ]"                                                                    +
    "\n\n\n\tINFORMATION:"                                                                                                                      +
    "\n\n\t\t"                   + CLI_HELP_TOKEN                 + "\n\t\t\tprints this message and exits"                                     +
    "\n\n\t\t"                   + CLI_VERSION_TOKEN              + "\n\t\t\tprints the application version string and exits"                   +
    "\n\n\n\tCONFIGURATION:"                                                                                                                    +
    "\n\n\t\t"                   + CLI_DIR_TOKEN + " <DIRECTORY>" + "\n\t\t\tstarts " + APP_NAME + " with the file browser rooted at DIRECTORY" +
    "\n\n\t\t"                   + CLI_FPS_TOKEN + " <N>"         + "\n\t\t\tstarts " + APP_NAME + " with N frames per second graphics update"  ) ;

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
                                                    "Comment=\r\n"                                  +
                                                    "Categories=AudioVideo;\r\n"                    +
                                                    "Exec=" + BinFile() .getFullPathName() + "\r\n" +
                                                    "Icon=" + IconFile().getFullPathName() + "\r\n" +
                                                    "StartupNotify=true\r\n"                        +
                                                    "Terminal=false\r\n"                            +
                                                    "Type=Application\r\n"                          ; }
