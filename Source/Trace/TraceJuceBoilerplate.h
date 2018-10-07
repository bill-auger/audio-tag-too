/*\
|*|  JuceBoilerplate - Clip and stitch audio samples
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


#include "Trace.h"


#ifdef DEBUG_TRACE

  #define DEBUG_TRACE_INIT_PHASE_1 Trace::TraceState("validating environment") ;

  #define DEBUG_TRACE_INIT_PHASE_2 Trace::TraceState("instantiating model") ;

  #define DEBUG_TRACE_INIT_PHASE_3 Trace::TraceState("processing CLI params") ;

  #define DEBUG_TRACE_INIT_PHASE_4 Trace::TraceState("initializing GUI") ;

  #define DEBUG_TRACE_INIT_PHASE_5 Trace::TraceState("finalizing initialization") ;

  #define DEBUG_TRACE_INIT_PHASE_6 Trace::TraceState("JuceBoilerplate ready") ;

  #define DEBUG_TRACE_SHUTDOWN_PHASE_1 Trace::TraceState("shutting down audio ") ;

  #define DEBUG_TRACE_SHUTDOWN_PHASE_2 Trace::TraceState("storing application state") ;

  #define DEBUG_TRACE_SHUTDOWN_PHASE_3 Trace::TraceState("shutting down storage") ;

  #define DEBUG_TRACE_HANDLE_CLI_PARAMS                                               \
    bool should_terminate = !token.isEmpty() ;                                        \
    if (should_terminate) Trace::TraceStoreVb("found terminating cli token " + token) ;

  #define DEBUG_TRACE_PROCESS_CLI_PARAMS                                                      \
    StringArray known_tokens , unknown_tokens , data_tokens ;                                 \
    for (String* token = cli_params.begin() ; token != cli_params.end() ; ++token)            \
    {                                                                                         \
      if      (*token == APP::CLI_AUDIO_TOKEN) known_tokens  .add(*token) ;                   \
      else if (*token == APP::CLI_DIR_TOKEN  ) known_tokens  .add(*token) ;                   \
      else if (*token == APP::CLI_FPS_TOKEN  ) known_tokens  .add(*token) ;                   \
      else if (*token == APP::CLI_ZOOM_TOKEN ) known_tokens  .add(*token) ;                   \
      else if ( token->startsWith("--")      ) unknown_tokens.add(*token) ;                   \
      else                                     data_tokens   .add(*token) ;                   \
    }                                                                                         \
    if (known_tokens  .size()) Trace::TraceStore("found pre-init cli tokens [ "           +   \
                                                 known_tokens  .joinIntoString(",") + " ]") ; \
    if (unknown_tokens.size()) Trace::TraceStore("found unknown cli tokens  [ "           +   \
                                                 unknown_tokens.joinIntoString(",") + " ]") ; \
    if (data_tokens   .size()) Trace::TraceStore("found data cli tokens  [ "              +   \
                                                 data_tokens   .joinIntoString(",") + " ]") ; \
    Trace::TraceStoreVb("dumping cli_params => [ " + cli_params.joinIntoString(",") + " ]")   ;

  #define DEBUG_TRACE_VALIDATE_ENVIRONMENT                                              \
    bool is_err = false ; String dbg = "" ;                                             \
    if (!is_valid_home_dir   ) { is_err = true ; dbg += " invlaid HOME_DIR"    ; }      \
    if (!is_valid_appdata_dir) { is_err = true ; dbg += " invlaid APPDATA_DIR" ; }      \
    if (!is_err) Trace::TraceState("environment is sane") ; else Trace::TraceError(dbg) ;

#else // DEBUG_TRACE

  #define DEBUG_TRACE_INIT_PHASE_1         ;
  #define DEBUG_TRACE_INIT_PHASE_2         ;
  #define DEBUG_TRACE_INIT_PHASE_3         ;
  #define DEBUG_TRACE_INIT_PHASE_4         ;
  #define DEBUG_TRACE_INIT_PHASE_5         ;
  #define DEBUG_TRACE_INIT_PHASE_6         ;
  #define DEBUG_TRACE_SHUTDOWN_PHASE_1     ;
  #define DEBUG_TRACE_SHUTDOWN_PHASE_2     ;
  #define DEBUG_TRACE_SHUTDOWN_PHASE_3     ;
  #define DEBUG_TRACE_HANDLE_CLI_PARAMS    ;
  #define DEBUG_TRACE_PROCESS_CLI_PARAMS   ;
  #define DEBUG_TRACE_VALIDATE_ENVIRONMENT ;

#endif // DEBUG_TRACE
