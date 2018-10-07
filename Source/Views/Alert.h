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


#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Constants/GuiConstants.h"


/**
  Alert is a public helper class for the JuceBoilerplate application.
  It queues and presents GUI message boxes to the user.
*/
class Alert
{
  friend class JuceBoilerplate ;


public:

  static void Push         (GUI::AlertType message_type , String message_text) ;
  static bool AreAnyPending() ;


private:

  Alert(GUI::AlertType message_type , String message_text     ) :
        messageType(message_type)   , messageText(message_text) { }


  // runtime state
  static OwnedArray<Alert> Alerts ;
  static bool              IsAlertModal ;

  // presentation
  static void Display() ;
  static void ShowAsync(AlertWindow::AlertIconType icon , String title , String text) ;

  // event handlers
  static void OnModalDismissed(int /*result*/ , int /*user-any-type*/) ;


  // instance configuration
  GUI::AlertType messageType ;
  String         messageText ;


  JUCE_DECLARE_NON_COPYABLE(Alert)
} ;
