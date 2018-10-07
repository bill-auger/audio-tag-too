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

  #define DEBUG_TRACE_INIT_VERSION                                        \
    if (!getCommandLineParameterArray().contains(APP::CLI_VERSION_TOKEN)) \
      LOG(JuceBoilerplate::VersionMsg().joinIntoString("\n") + "\n")      ;

  #define DEBUG_TRACE_SHUTDOWN_IN  Trace::TraceState("shutting down") ;

  #define DEBUG_TRACE_SHUTDOWN_OUT Trace::TraceState("clean shutdown - bye") ;

#else // DEBUG_TRACE

  #define DEBUG_TRACE_INIT_VERSION ;
  #define DEBUG_TRACE_SHUTDOWN_IN  ;
  #define DEBUG_TRACE_SHUTDOWN_OUT ;

#endif // DEBUG_TRACE
