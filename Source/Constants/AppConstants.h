#pragma once


// disable standard features
#ifdef DEBUG
  #define DISABLE_AUDIO 0
#endif // DEBUG


#include "../../JuceLibraryCode/JuceHeader.h"


/** the APP class defines configuration and runtime constants
        pertaining to the core application and business logic */
class APP
{
public:

  // names and IDs
  static const String APP_NAME ;
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
  static const String CLI_AUDIO_TOKEN ;
  static const String CLI_DIR_TOKEN ;
  static const String CLI_FPS_TOKEN ;

  // feature set keys
  static const Identifier AUDIO_KEY ;
  static const Identifier INIT_DIR_KEY ;
  static const Identifier COURSE_FPS_KEY ;
  static const Identifier FINE_FPS_KEY ;

  // user messages
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
