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


#include "../Constants/GuiConstants.h"
#include "../Constants/StorageConstants.h"


class ClipItem : public TreeViewItem
{
public:

  ClipItem(String item_id , String label_text , ValueTree store = ValueTree::invalid) ;


  // TreeViewItem implementation
  String     getUniqueName       () const override ;
  bool       mightContainSubItems()       override ;
  int        getItemHeight       () const override ;
  Component* createItemComponent ()       override ;


private:

  String    item_id ;
  String    label_text ;
  ValueTree store ;


  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ClipItem)
} ;
