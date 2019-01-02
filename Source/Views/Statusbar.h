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

//[Headers]     -- You can add your own extra header files here --

#include "../../JuceLibraryCode/JuceHeader.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  Statusbar is the bottom statusbar GUI for the AudioTagToo application.
  It does nothing useful yet.
                                                                    //[/Comments]
*/
class Statusbar  : public Component
{
public:
    //==============================================================================
    Statusbar ();
    ~Statusbar();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  void setStatusL(String status_text , Colour text_color = GUI::TEXT_NORMAL_COLOR) ;
  void setStatusC(String status_text , Colour text_color = GUI::TEXT_NORMAL_COLOR) ;
  void setStatusR(String status_text , Colour text_color = GUI::TEXT_NORMAL_COLOR) ;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> statusLLabel;
    std::unique_ptr<Label> statusCLabel;
    std::unique_ptr<Label> statusRLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Statusbar)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
