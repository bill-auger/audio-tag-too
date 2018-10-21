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


#include "ClipItem.h"


ClipItem::ClipItem(String  _item_id  , String     _label_text  , ValueTree _store) :
                   item_id(_item_id) , label_text(_label_text) , store(    _store) { }


String     ClipItem::getUniqueName       () const { return this->item_id         ; }
bool       ClipItem::mightContainSubItems()       { return this->store.isValid() ; }
int        ClipItem::getItemHeight       () const { return GUI::TREE_ITEM_H      ; }
Component* ClipItem::createItemComponent ()
{
  Label* item_label = new Label(this->item_id , this->label_text) ;

  if (this->store.hasProperty(STORE::LABEL_TEXT_KEY))
  {
    item_label->setEditable(true) ;
    Value stored_value = this->store.getPropertyAsValue(STORE::LABEL_TEXT_KEY , nullptr) ;
    item_label->getTextValue().referTo(stored_value) ;
  }

  return item_label ;
}
