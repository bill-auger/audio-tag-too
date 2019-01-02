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
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ConfigMetadata  : public Component,
                        private Button::Listener,
                        public ComboBox::Listener
{
public:
    //==============================================================================
    ConfigMetadata (ValueTree clip_store);
    ~ConfigMetadata();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  void buttonClicked     (Button* a_button) ;
  bool handleAcceptButton(void) ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> keyLabel;
    std::unique_ptr<Label> valueLabel;
    std::unique_ptr<ComboBox> keySelect;
    std::unique_ptr<TextEditor> valueText;
    std::unique_ptr<ComboBox> keySelect2;
    std::unique_ptr<TextEditor> valueText2;
    std::unique_ptr<ComboBox> keySelect3;
    std::unique_ptr<TextEditor> valueText3;
    std::unique_ptr<ComboBox> keySelect4;
    std::unique_ptr<TextEditor> valueText4;
    std::unique_ptr<ComboBox> keySelect5;
    std::unique_ptr<TextEditor> valueText5;
    std::unique_ptr<ComboBox> keySelect6;
    std::unique_ptr<TextEditor> valueText6;
    std::unique_ptr<ComboBox> keySelect7;
    std::unique_ptr<TextEditor> valueText7;
    std::unique_ptr<ComboBox> keySelect8;
    std::unique_ptr<TextEditor> valueText8;
    std::unique_ptr<TextButton> acceptButton;
    std::unique_ptr<TextButton> cancelButton;
    std::unique_ptr<Label> clipLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigMetadata)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
