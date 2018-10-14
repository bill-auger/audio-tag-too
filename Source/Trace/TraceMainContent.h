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

#include "Trace.h"


#if DEBUG_TRACE

  #define DEBUG_TRACE_NEW_MASTER_ITEM                                  \
    Trace::TraceGui("created new master item: [ " + master_label + " ]") ;

  #define DEBUG_TRACE_NEW_CLIP_ITEM                                                     \
    Trace::TraceGui("created new clip item: [ " + clip_label + "," + file_label + "," + \
                                                 begin_label + "," + end_label  + " ]") ;

  #define DEBUG_TRACE_CREATE_MASTER_ITEM                                                       \
    Trace::TraceGui("added master item master_idx=" + String(master_idx)                     + \
                                   " master_item="  + master_item->getItemIdentifierString() + \
                                   " master_item="  + master_item->getUniqueName()           ) ;

  #define DEBUG_TRACE_CREATE_CLIP_ITEM                                                         \
    if (!does_master_item_exist) Trace::TraceGui("created master item") ;                      \
    Trace::TraceGui("added clip item master_idx="   + String(master_idx)                     + \
                                    " master_item=" + master_item->getItemIdentifierString() + \
                                    " master_item=" + master_item->getUniqueName()           ) ;

#else // DEBUG_TRACE

  #define DEBUG_TRACE_NEW_MASTER_ITEM    ;
  #define DEBUG_TRACE_NEW_CLIP_ITEM      ;
  #define DEBUG_TRACE_CREATE_MASTER_ITEM ;
  #define DEBUG_TRACE_CREATE_CLIP_ITEM   ;

#endif // DEBUG_TRACE
