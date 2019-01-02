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


#include "AudioTagToo.h"
#include "../Constants/AppConstants.h"
#include "../Constants/GuiConstants.h"
#include "../Constants/MediaConstants.h"
#include "../Constants/StorageConstants.h"
#include "../Models/AudioTagTooStore.h"
#include "../Trace/TraceAudioTagToo.h"
#include "../Views/Alert.h"
#include "../Views/MainContent.h"


/* AudioTagToo public class variables */

#ifdef CONTROLLER_OWNS_STORAGE
std::unique_ptr<AudioTagTooStore> AudioTagToo::Store ; // Initialize()
#endif // CONTROLLER_OWNS_STORAGE


/* AudioTagToo private class variables */

JUCEApplication* AudioTagToo::App            = nullptr ; // Initialize()
DocumentWindow*  AudioTagToo::Window         = nullptr ; // Initialize()
MainContent*     AudioTagToo::Gui            = nullptr ; // Initialize()
bool             AudioTagToo::IsInitialized  = false ;   // Initialize()
bool             AudioTagToo::IsAudioEnabled = true ;    // Initialize()
NamedValueSet    AudioTagToo::Features ;                 // ProcessCliParams()


/* AudioTagToo public class methods */

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

bool AudioTagToo::GetIsInitialized() { return IsInitialized ; }

void AudioTagToo::SetConfig(const Identifier& a_key , const var a_value)
{
#ifdef CONTROLLER_OWNS_STORAGE
  ValueTree storage_node = (STORE::RootKeys.contains(key)) ? Store->root        :
                                                             ValueTree::invalid ;

  Store->setConfig(storage_node , key , value) ;
#endif // CONTROLLER_OWNS_STORAGE
}

void AudioTagToo::ResetAudio()
{
#if ! DISABLE_AUDIO
  if (bool(Features[APP::AUDIO_KEY]))
  {
    // start/restart audio thread
    Gui->shutdownAudio() ;
#ifndef CONTROLLER_OWNS_STORAGE
    Gui->setAudioChannels(0 , MEDIA::N_CHANNELS_OUT , Gui->storage->deviceStateXml.get()) ;
#else // CONTROLLER_OWNS_STORAGE
    Gui->setAudioChannels(0 , MEDIA::N_CHANNELS_OUT , Store->deviceStateXml.get()) ;
#endif // CONTROLLER_OWNS_STORAGE
  }
#endif // DISABLE_AUDIO
}

ValueTree AudioTagToo::CreateClip(String audio_filename , double begin_time , double end_time)
{
  return Store->createClip(audio_filename , begin_time , end_time) ;
}

void AudioTagToo::Warning(String message_text) { Alert::Push(GUI::ALERT_TYPE_WARNING , message_text) ; }

void AudioTagToo::Error(String message_text) { Alert::Push(GUI::ALERT_TYPE_ERROR , message_text) ; }

void AudioTagToo::LoadClip(ValueTree clip_store)
{
  String master_filename = STRING(clip_store[STORE::FILENAME_KEY  ]) ;
  double begin_time      = double(clip_store[STORE::BEGIN_TIME_KEY]) ;
  double end_time        = double(clip_store[STORE::END_TIME_KEY  ]) ;

  Gui->loadUrl(File(master_filename)) ;
  Gui->setPosition(begin_time) ; Gui->setHeadMarker() ;
  Gui->setPosition(end_time  ) ; Gui->setTailMarker() ;
  Gui->updateTransportButton() ; Gui->repaint() ;
}

String AudioTagToo::DurationString(double duration)
{
  int    duration_int =        int(duration) ;
  String milliseconds = String(int(duration     * 1000.0) % 1000) ;
  String seconds      = String(   (duration_int         ) %   60) ;
  String minutes      = String(   (duration_int /     60) %   60) ;
  String hours        = String(   (duration_int /   3600)       ) ;
  String clip_time    = String(hours + ":" + minutes + ":" + seconds + ":" + milliseconds) ;

  return clip_time ;
}


/* AudioTagToo private class methods */

bool AudioTagToo::Initialize(DocumentWindow* main_window , MainContent* main_content)
{
  App                    = JUCEApplication::getInstance() ;
  Window                 = main_window ;
  Gui                    = main_content ;
  StringArray cli_params = JUCEApplication::getCommandLineParameterArray() ;

  // detect and handle terminating command line switches
  if (HandleCliParams(cli_params)) { Trace::EnableTracing(false) ; return false ; }

DEBUG_TRACE_INIT_PHASE_1

  if (!ValidateEnvironment()) return false ;

DEBUG_TRACE_INIT_PHASE_2

  if (!STORE::Initialize()) return false ;

DEBUG_TRACE_INIT_PHASE_3

  // load persistent configuration
#ifdef CONTROLLER_OWNS_STORAGE
  AudioTagTooStore* store = new AudioTagTooStore() ;
  if (store != nullptr) Store.reset(store) ; else return false ;
#endif // CONTROLLER_OWNS_STORAGE

DEBUG_TRACE_INIT_PHASE_4

  // load transient configuration options passed via command line or set defaults
  ProcessCliParams(cli_params) ;

DEBUG_TRACE_INIT_PHASE_5

  // initialze GUI
#ifdef CONTROLLER_OWNS_STORAGE
  Window->restoreWindowStateFromString(STRING(Store->root[STORE::WINDOW_STATE_KEY])) ;
  if (!Gui->initialize(Store->clips , Store->compilations , Features , Store->thumbnailCache))
    return false ;
#else // CONTROLLER_OWNS_STORAGE
  Gui->initialize(Features , Store->thumbnailCache) ;
  Window->restoreWindowStateFromString(STRING(Gui->storage->root[STORE::WINDOW_STATE_KEY])) ;
#endif // CONTROLLER_OWNS_STORAGE

DEBUG_TRACE_INIT_PHASE_6

  // finalize initialization
  IsInitialized = true ;

  // subscribe to model change events
#ifdef CONTROLLER_OWNS_STORAGE
  Store->listen(true) ;
#endif // CONTROLLER_OWNS_STORAGE

DEBUG_TRACE_INIT_PHASE_7

  return IsInitialized ;
}

void AudioTagToo::Teardown()
{
  Alert::Display() ; Alert::Alerts.clear() ;

DEBUG_TRACE_SHUTDOWN_PHASE_1

  if (IsInitialized) Gui->shutdownAudio() ;

DEBUG_TRACE_SHUTDOWN_PHASE_2

#ifdef CONTROLLER_OWNS_STORAGE
  if (IsInitialized) SetConfig(STORE::WINDOW_STATE_KEY , Window->getWindowStateAsString()) ;
#else // CONTROLLER_OWNS_STORAGE
  if (IsInitialized) Gui->storage->root.setProperty(STORE::WINDOW_STATE_KEY , Window->getWindowStateAsString() , nullptr) ;
#endif // CONTROLLER_OWNS_STORAGE

DEBUG_TRACE_SHUTDOWN_PHASE_3

  // shutdown storage
#ifdef CONTROLLER_OWNS_STORAGE
  Store = nullptr ;
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

bool AudioTagToo::HandleCliParams(StringArray cli_params)
{
  // detect terminating CLI params
  String token = (cli_params.contains(APP::CLI_HELP_TOKEN   )) ? APP::CLI_HELP_TOKEN    :
                 (cli_params.contains(APP::CLI_VERSION_TOKEN)) ? APP::CLI_VERSION_TOKEN :
                                                                 String::empty          ;

DEBUG_TRACE_HANDLE_CLI_PARAMS

  if (token.isEmpty()) return false ;

  StringArray cli_output ;

  // handle terminating CLI params
  if      (token == APP::CLI_HELP_TOKEN   ) cli_output = APP::CLI_USAGE_MSG ;
  else if (token == APP::CLI_VERSION_TOKEN) cli_output = VersionMsg() ;

  if (!cli_output.isEmpty()) printf("%s\n\n" , CHARSTAR(cli_output.joinIntoString("\n"))) ;

  return true ;
}

void AudioTagToo::ProcessCliParams(StringArray cli_params)
{
DEBUG_TRACE_PROCESS_CLI_PARAMS

  /* disable features */

  bool is_audio_enabled = !cli_params.contains(APP::CLI_AUDIO_TOKEN) ;


  /* parse config vars */

  int    token_idx ;
  String string_value ;
  int    int_value ;
  double double_value ;

  // initial browser directory
  bool is_valid_dir  = (((token_idx    = cli_params.indexOf(APP::CLI_DIR_TOKEN)) > -1) &&
                        ((string_value = cli_params[token_idx + 1]).isNotEmpty()     ) &&
                        File(string_value).exists()                                     ) ;
  String initial_dir = (is_valid_dir            ) ? string_value                      :
                       (APP::MusicDir().exists()) ? APP::MusicDir().getFullPathName() :
                                                    APP::HomeDir ().getFullPathName() ;

  // FPS
  bool is_valid_fps = (((token_idx = cli_params.indexOf(APP::CLI_FPS_TOKEN))  > -1) &&
                       ((int_value = cli_params[token_idx + 1].getIntValue()) >  0)  ) ;
  int course_fps    = GUI::COURSE_FPS ;
  int fine_fps      = (is_valid_fps) ? int_value : GUI::FINE_FPS ;

  // zoom scale
  bool   is_valid_zoom = (((token_idx    = cli_params.indexOf(APP::CLI_ZOOM_TOKEN))    >  -1) &&
                          ((double_value = cli_params[token_idx + 1].getDoubleValue()) > 0.0)  ) ;
  double zoom_factor   = (is_valid_zoom) ? double_value : 1.0 ;

  Features.set(APP::AUDIO_KEY      , var(is_audio_enabled)) ;
  Features.set(APP::INIT_DIR_KEY   , var(initial_dir     )) ;
  Features.set(APP::COURSE_FPS_KEY , var(course_fps      )) ;
  Features.set(APP::FINE_FPS_KEY   , var(fine_fps        )) ;
  Features.set(APP::ZOOM_KEY       , var(zoom_factor     )) ;
}

bool AudioTagToo::ValidateEnvironment()
{
  bool is_valid_home_dir    = APP::HomeDir   ().isDirectory() ;
  bool is_valid_appdata_dir = APP::AppdataDir().isDirectory() ;

DEBUG_TRACE_VALIDATE_ENVIRONMENT

  return is_valid_home_dir && is_valid_appdata_dir ;
}

void AudioTagToo::UpdateStatusGUI()
{
  Gui->setStatus() ; return ; // TODO: refactor

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
