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


#pragma once


#include "Trace.h"


#if DEBUG_TRACE

  #define DEBUG_TRACE_WAVEFORM_PAINT                                                                                                                         \
    double cursorTime = transport.getCurrentPosition() ;                                                                                                     \
    Trace::TraceGuiVb("re-painting headTime="   + String(headTime  ) + "(x=" + String(timeToX(headTime  )) + ") actual= " + String(tailMarker  .getX())    + \
                                 " cursorTime=" + String(cursorTime) + "(x=" + String(timeToX(cursorTime)) + ") actual= " + String(cursorMarker.getX())    + \
                                 " tailTime="   + String(tailTime  ) + "(x=" + String(timeToX(tailTime  )) + ") actual= " + String(headMarker  .getRight())) ;

  #define DEBUG_TRACE_WAVEFORM_SET_HEAD_OR_TAIL(marker_name)                                                        \
    Trace::TraceGui     ("setting "    + String(marker_name   ) + " of " + this->getName() +                        \
                         " [ "         + String(this->headTime)                            +                        \
                         " ... "       + String(this->tailTime) + " ]"                     ) ;                      \
    Trace::TraceNoPrefix("viewRange="  + String(this->viewRange.getStart()                              ) + " + " + \
                                         String(this->viewRange.getLength()                             ) + " = " + \
                                         String(this->viewRange.getStart() + this->viewRange.getLength())         + \
                         " transport=" + String(this->transport.getCurrentPosition()                    )         ) ;

  #define DEBUG_TRACE_WAVEFORM_SET_ZOOM_FACTOR                                     \
    Trace::TraceGui("setting zoom scaling factor: " + String(zoom_scaling_factor)) ;

  #define DEBUG_TRACE_WAVEFORM_MOUSE_WHEEL_MOVE                                                            \
    if (DEBUG_TRACE_GUI_VB||true) { Trace::TraceGui("Waveform::mouseWheelMove()") ;                        \
                                    Trace::TraceNoPrefix("mouse_x         = " + String(mouse_x        )) ; \
                                    Trace::TraceNoPrefix("mouse_time      = " + String(mouse_time     )) ; \
                                    Trace::TraceNoPrefix("mouse_x_percent = " + String(mouse_x_percent)) ; \
                                    Trace::TraceNoPrefix("new_begin_time  = " + String(new_begin_time )) ; \
                                    Trace::TraceNoPrefix("new_end_time    = " + String(new_end_time   )) ; }

  #define DEBUG_TRACE_WAVEFORM_SET_VIEWRANGE                                                             \
    Trace::TraceGuiVb("setting ViewRange of " + this->getName()                                        + \
                      " view_range=" + String(view_range.getStart()                         ) + " + "  + \
                                       String(view_range.getLength()                        ) + " = "  + \
                                       String(view_range.getStart() + view_range.getLength())          + \
                      " transport="  + String(this->transport.getCurrentPosition()          ) + " of " + \
                                       String(this->transport.getLengthInSeconds()          )          + \
                      " headTime="   + String(this->headTime                                )          + \
                      " tailTime="   + String(this->tailTime                                )          ) ;

  #define DEBUG_TRACE_WAVEFORM_TIME_TO_X                            \
    Trace::TraceGuiVb("offset_n_secs="   + String(offset_n_secs ) + \
                      " visible_n_secs=" + String(visible_n_secs) + \
                      " scale_x="        + String(scale_x       ) + \
                      " view_l="         + String(view_l        ) + \
                      " view_r="         + String(view_r        ) + \
                      " view_w="         + String(view_w        ) ) ;

  #define DEBUG_TRACE_WAVEFORM_X_TO_TIME                            \
    Trace::TraceGuiVb("view_r="          + String(view_r        ) + \
                      " view_w="         + String(view_w        ) + \
                      " scale_x="        + String(scale_x       ) + \
                      " begin_time="     + String(begin_time    ) + \
                      " end_time="       + String(end_time      ) + \
                      " visible_n_secs=" + String(visible_n_secs) ) ;

#else // DEBUG_TRACE

  #define DEBUG_TRACE_WAVEFORM_PAINT                         ;
  #define DEBUG_TRACE_WAVEFORM_SET_HEAD_OR_TAIL(marker_name) ;
  #define DEBUG_TRACE_WAVEFORM_SET_ZOOM_FACTOR               ;
  #define DEBUG_TRACE_WAVEFORM_MOUSE_WHEEL_MOVE              ;
  #define DEBUG_TRACE_WAVEFORM_SET_VIEWRANGE                 ;
  #define DEBUG_TRACE_WAVEFORM_TIME_TO_X                     ;
  #define DEBUG_TRACE_WAVEFORM_X_TO_TIME                     ;

#endif // DEBUG_TRACE
