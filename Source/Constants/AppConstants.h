
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
} ;
