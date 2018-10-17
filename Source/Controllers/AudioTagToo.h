/*\
|*|  AudioTagToo - Clip and stitch audio samples
|*|  Copyright 2018 bill-auger <https://github.com/bill-auger/audio-tag-too/issues>
|*|
|*|  This file is part of the AudioTagToo program.
|*|
|*|  AudioTagToo is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU General Public License version 3
|*|  as published by the Free Software Foundation.
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
#include "../Models/AudioTagTooStore.h"
#include "../Views/MainContent.h"


class AudioTagToo
{
  friend class AudioTagTooApplication ;
  friend class AudioTagTooStore ;


public:

  // GUI dispatchers
  static void Warning(String message_text) ;
  static void Error  (String message_text) ;

  // getters/setters
  static StringArray VersionMsg      (void) ;
  static String      GetVersionString(void) ;
  static void        SetConfig       (const Identifier& a_key , const var a_value) ;


private:

  // setup/teardown
  static bool Initialize(JUCEApplicationBase* main_app   , MainContent* main_content ,
                         StringArray          cli_params                             ) ;
  static void Shutdown  (void) ;

  // callbacks and event handlers
  static void HandleTimer        (int timer_id) ;
  static void HandleConfigChanged(const Identifier& a_key) ;
  static void UpdateStatusGUI    (void) ;
  static void PumpThreads        (void) ;

  // collaborator handles
  static JUCEApplicationBase* App ;
  static MainContent*         Gui ;

  // model/persistence
#ifdef CONTROLLER_OWNS_STORAGE
  static std::unique_ptr<AudioTagTooStore> Store ;
#endif // CONTROLLER_OWNS_STORAGE

  // intialization flags
  static bool          IsInitialized ;
  static NamedValueSet DisabledFeatures ;
} ;
