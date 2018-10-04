#include "AppConstants.h"


// names and IDs
const String APP::APP_NAME           = ProjectInfo::projectName ;
const String APP::WORKER_THREAD_NAME = "juceboilerplate-worker" ;
const String APP::DIGITS             = "0123456789" ;
const String APP::LETTERS            = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" ;
const String APP::ALPHANUMERIC       = DIGITS + LETTERS ;
const String APP::VALID_ID_CHARS     = ALPHANUMERIC + "_- " ;
const String APP::FILTER_CHARS       = "-_.:/?=@#&[] " ;
const String APP::REPLACE_CHARS      = String::repeatedString("-" , FILTER_CHARS.length()) ;

// CLI params
const String     APP::CLI_HELP_TOKEN    = "--help" ;
const String     APP::CLI_VERSION_TOKEN = "--version" ;
const String     APP::CLI_AUDIO_TOKEN   = "--no-audio" ;
const String     APP::CLI_DIR_TOKEN     = "--dir" ;
const String     APP::CLI_FPS_TOKEN     = "--fps" ;
const Identifier APP::AUDIO_KEY         = "is-audio-enabled" ;
const Identifier APP::INIT_DIR_KEY      = "initial-dir" ;
const Identifier APP::COURSE_FPS_KEY    = "course-fps" ;
const Identifier APP::FINE_FPS_KEY      = "fine-fps" ;

// user messages
#define APP_CMD_PAD String("").paddedLeft(' ' , APP_CMD.length())
#define HELP_USAGE_MSG    "prints this message and exits"
#define VERSION_USAGE_MSG "prints the application version string and exits"
#define AUDIO_USAGE_MSG   "disables audio output (safe mode)"
#define DIR_USAGE_MSG     "starts " + APP_NAME + " with the file browser rooted at DIRECTORY"
#define FPS_USAGE_MSG     "starts " + APP_NAME + " with integer(N) frames per second graphics update"
#define CLI_DIR_TOKEN_ENTRY CLI_DIR_TOKEN + " <DIRECTORY>"
#define CLI_FPS_TOKEN_ENTRY CLI_FPS_TOKEN + " <N>"
const StringArray APP::CLI_USAGE_MSG = StringArray::fromLines(
  String("AudioTagToo Usage:\n")                                                  +
  "\n\t" + APP_CMD + " [ " + CLI_HELP_TOKEN      + " | "                          +
                             CLI_VERSION_TOKEN   + " ]"                           +
  "\n\t" + APP_CMD + " [ " + CLI_AUDIO_TOKEN     + " ]"                           +
                     " [ " + CLI_DIR_TOKEN_ENTRY + " ]"                           +
                     " [ " + CLI_FPS_TOKEN_ENTRY + " ]"                           +
  "\n\n\n\tINFORMATION:"                                                          +
  "\n\n\t\t"               + CLI_HELP_TOKEN      + "\n\t\t\t" + HELP_USAGE_MSG    +
  "\n\n\t\t"               + CLI_VERSION_TOKEN   + "\n\t\t\t" + VERSION_USAGE_MSG +
  "\n\n\n\tFEATURE SWITCHES:"                                                     +
  "\n\n\t\t"               + CLI_AUDIO_TOKEN     + "\n\t\t\t" + AUDIO_USAGE_MSG   +
  "\n\n\n\tCONFIGURATION:"                                                        +
  "\n\n\t\t"               + CLI_DIR_TOKEN_ENTRY + "\n\t\t\t" + DIR_USAGE_MSG     +
  "\n\n\t\t"               + CLI_FPS_TOKEN_ENTRY + "\n\t\t\t" + FPS_USAGE_MSG     ) ;


// filesystem
const String APP::IconFilename()    { return APP_CMD + ".png" ;                         }
const String APP::DesktopFilename() { return APP_CMD + ".desktop" ;                     }
const String APP::IconsPath()       { return ".local/share/icons/hicolor/48x48/apps/" ; }
const String APP::AppsPath()        { return ".local/share/applications/" ;             }
const File   APP::HomeDir()         { return File::getSpecialLocation(File::userHomeDirectory           ) ; }
const File   APP::MusicDir()        { return File::getSpecialLocation(File::userMusicDirectory          ) ; }
const File   APP::AppdataDir()      { return File::getSpecialLocation(File::userApplicationDataDirectory) ; }
const File   APP::BinFile()         { return File::getSpecialLocation(File::currentExecutableFile       ) ; }
const File   APP::IconFile()        { return HomeDir().getChildFile  (IconsPath() + IconFilename()   ) ; }
const File   APP::DesktopFile()     { return HomeDir().getChildFile  (AppsPath()  + DesktopFilename()) ; }
const String APP::DesktopFileText() { return String("[Desktop Entry]\r\n")                                   +
                                                    "Name=JuceBoilerplate\r\n"                               +
                                                    "GenericName=\r\n"                                       +
                                                    "Comment=Generic Juce Audio Boilerplate Application\r\n" +
                                                    "Categories=AudioVideo;\r\n"                             +
                                                    "Exec=" + BinFile() .getFullPathName() + "\r\n"          +
                                                    "Icon=" + IconFile().getFullPathName() + "\r\n"          +
                                                    "StartupNotify=true\r\n"                                 +
                                                    "Terminal=false\r\n"                                     +
                                                    "Type=Application\r\n"                                 ; }
