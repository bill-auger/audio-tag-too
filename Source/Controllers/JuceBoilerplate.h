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


#include "../JuceLibraryCode/JuceHeader.h"
#ifdef CONTROLLER_OWNS_STORAGE
#include "../Views/MainContent.h"
#endif // CONTROLLER_OWNS_STORAGE

class JuceBoilerplateStore ;
#ifndef CONTROLLER_OWNS_STORAGE
class MainContent ;
#endif // CONTROLLER_OWNS_STORAGE


class JuceBoilerplate
{
  friend class JuceBoilerplateApplication ;
  friend class JuceBoilerplateStore ;
#ifdef CONTROLLER_OWNS_STORAGE
  friend class MainContent ;
#endif // CONTROLLER_OWNS_STORAGE


public:

  // GUI dispatchers
  static void Warning(String message_text) ;
  static void Error  (String message_text) ;

  // getters/setters
  static StringArray VersionMsg      (void) ;
  static String      GetVersionString(void) ;
  static void        SetConfig       (const Identifier& a_key , const var a_value) ;
  static void        ResetAudio      (void) ;


private:

  // setup/teardown
  static bool Initialize(DocumentWindow* main_window , MainContent* main_content) ;
  static void Teardown  (void) ;

  // callbacks and event handlers
  static void HandleTimer        (int timer_id) ;
  static void HandleConfigChanged(const Identifier& a_key) ;

  // helpers
  static bool HandleCliParams    (StringArray cli_params) ;
  static void ProcessCliParams   (StringArray cli_params) ;
  static bool ValidateEnvironment(void) ;
  static void UpdateStatusGUI    (void) ;
  static void PumpThreads        (void) ;


  // collaborator handles
  static JUCEApplication* App ;
  static DocumentWindow*  Window ;
  static MainContent*     Gui ;

  // model/persistence
#ifdef CONTROLLER_OWNS_STORAGE
  static std::unique_ptr<JuceBoilerplateStore> Store ;
#endif // CONTROLLER_OWNS_STORAGE

  // intialization flags
  static bool          IsInitialized ;
  static bool          IsAudioEnabled ;
  static NamedValueSet Features ;
} ;
