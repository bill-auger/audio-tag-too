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


#include "Alert.h"


/* Alert private class variables */

OwnedArray<Alert> Alert::Alerts ;
bool              Alert::IsAlertModal = false ;


/* Alert public class methods */

void Alert::Push(GUI::AlertType message_type , String message_text)
{
#ifndef SUPRESS_ALERTS
  Alerts.add(new Alert(message_type , message_text)) ;
#endif // SUPRESS_ALERTS
}

bool Alert::AreAnyPending() { return IsAlertModal || Alerts.size() > 0 ; }


/* Alert private class methods */

void Alert::Display()
{
  if (!IsAlertModal && Alerts.size() > 0) IsAlertModal = true ; else return ;

  GUI::AlertType message_type = Alerts[0]->messageType ;
  String         message_text = Alerts[0]->messageText ;

  Alerts.remove(0) ;

  switch (message_type)
  {
    case GUI::ALERT_TYPE_WARNING: ShowAsync(AlertWindow::InfoIcon    ,
                                            GUI::MODAL_WARNING_TITLE ,
                                            message_text             ) ; break ;
    case GUI::ALERT_TYPE_ERROR:   ShowAsync(AlertWindow::WarningIcon ,
                                            GUI::MODAL_ERROR_TITLE   ,
                                            message_text             ) ; break ;
    default:                      IsAlertModal = false ;                 break ;
  }
}

void Alert::ShowAsync(AlertWindow::AlertIconType icon , String title , String text)
{
  ModalComponentManager::Callback* callback = ModalCallbackFunction::create(OnModalDismissed , 0) ;

  AlertWindow::showMessageBoxAsync(icon , title , text , "OK" , nullptr , callback) ;
}

void Alert::OnModalDismissed(int , int) { IsAlertModal = false ; }
