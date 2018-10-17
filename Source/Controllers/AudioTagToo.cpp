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


#include "AudioTagToo.h"
#include "../Constants/AppConstants.h"
#include "../Constants/GuiConstants.h"
#ifdef CONTROLLER_OWNS_STORAGE
#include "../Constants/StorageConstants.h"
#endif // CONTROLLER_OWNS_STORAGE
#include "../Views/Alert.h"


/* AudioTagToo public class variables */
#ifdef CONTROLLER_OWNS_STORAGE
ScopedPointer<AudioTagTooStore> AudioTagToo::Store ; // Initialize()
#endif // CONTROLLER_OWNS_STORAGE


/* AudioTagToo private class variables */

JUCEApplicationBase* AudioTagToo::App            = nullptr ; // Initialize()
MainContent*         AudioTagToo::Gui            = nullptr ; // Initialize()
bool                 AudioTagToo::IsInitialized  = false ;   // Initialize()
NamedValueSet        AudioTagToo::DisabledFeatures ;         // (unused)


/* AudioTagToo public class methods */

void AudioTagToo::Warning(String message_text) { Alert::Push(GUI::ALERT_TYPE_WARNING , message_text) ; }

void AudioTagToo::Error(String message_text) { Alert::Push(GUI::ALERT_TYPE_ERROR , message_text) ; }

StringArray AudioTagToo::VersionMsg()
{
  StringArray version_msg = StringArray(GetVersionString()) ;

  version_msg.add(SystemStats::getJUCEVersion()) ;

  return version_msg ;
}

String AudioTagToo::GetVersionString()
{
#ifdef DEBUG
  return APP::APP_NAME + " v" + APP::APP_VERSION + " (DEBUG)" ;
#else // DEBUG
  return APP::APP_NAME + " v" + APP::APP_VERSION ;
#endif // DEBUG
}

void AudioTagToo::SetConfig(const Identifier& a_key , const var a_value)
{
#ifdef CONTROLLER_OWNS_STORAGE
  ValueTree storage_node = (STORE::RootKeys().contains(a_key)) ? Store->root        :
                                                                 ValueTree::invalid ;

  Store->setConfig(storage_node , a_key , a_value) ;
#endif // CONTROLLER_OWNS_STORAGE
}


/* AudioTagToo private class methods */

bool AudioTagToo::Initialize(JUCEApplicationBase* main_app   , MainContent* main_content ,
                             StringArray          cli_params                             )
{
  App = main_app ;
  Gui = main_content ;

  // load persistent configuration
#ifdef CONTROLLER_OWNS_STORAGE
  if ((Store = new AudioTagTooStore()) == nullptr) return false ;
#endif // CONTROLLER_OWNS_STORAGE

  // finalize initialization
  IsInitialized = true ;

  // subscribe to model change events
#ifdef CONTROLLER_OWNS_STORAGE
  Store->listen(true) ;
#endif // CONTROLLER_OWNS_STORAGE

  return IsInitialized ;
}

void AudioTagToo::Shutdown()
{
  Alert::Display() ; Alert::Alerts.clear() ;

  // shutdown storage
#ifdef CONTROLLER_OWNS_STORAGE
  if (Store != nullptr) Store->shutdown() ; Store = nullptr ;
#endif // CONTROLLER_OWNS_STORAGE

  IsInitialized = false ;
}

void AudioTagToo::HandleTimer(int timer_id)
{
  switch (timer_id)
  {
    case APP::TIMER_HI_ID:                                         break ;
    case APP::TIMER_MED_ID: UpdateStatusGUI() ; Alert::Display() ; break ;
    case APP::TIMER_LO_ID:  PumpThreads() ;                        break ;
    default:                                                       break ;
  }
}

void AudioTagToo::HandleConfigChanged(const Identifier& a_key) { }

void AudioTagToo::UpdateStatusGUI()
{
  Gui->setStatusL(String::empty) ;
  Gui->setStatusC(String::empty) ;
  Gui->setStatusR(String::empty) ;
}

void AudioTagToo::PumpThreads()
{
  bool is_quit_pending = App->getApplicationReturnValue() != 0 ;
  bool should_quit     = is_quit_pending && !Alert::AreAnyPending() ;

#ifndef SOME_MULTITHREADED_FEATURE_DISABLED
//   if (IsSomeFeatureEnabled) SomeFeature->pump() ;
#endif // SOME_MULTITHREADED_FEATURE_DISABLED

  if (should_quit) App->quit() ;
}
