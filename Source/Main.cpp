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


#include "AppConstants.h"
#include "GuiConstants.h"
#include "MainContent.h"


class AudioTagTooApplication : public JUCEApplication
{
public:

  AudioTagTooApplication() {}

  void initialise(const String& commandLine) override
  {
    this->mainWindow.reset(new MainWindow()) ;

    if (! true /*AudioTagToo::Init()*/) { setApplicationReturnValue(255) ; shutdown() ; quit() ; }
  }

  void shutdown() override { this->mainWindow = nullptr ; }

  void systemRequestedQuit() override { quit() ; }

  void anotherInstanceStarted(const String& command_line) override {}

  const String getApplicationName()    override { return ProjectInfo::projectName ; }

  const String getApplicationVersion() override { return ProjectInfo::versionString ; }

  bool moreThanOneInstanceAllowed()    override { return true ; }


  class MainWindow : public DocumentWindow
  {
  public:

//     MainWindow() : DocumentWindow(APP::APP_NAME , GUI::WINDOW_BG_COLOR , GUI::TITLEBAR_BTNS)
    MainWindow() : DocumentWindow(APP::APP_NAME , GUI::WINDOW_BG_COLOR , DocumentWindow::allButtons)
    {
      // main content component
      this->mainContent = new MainContent() ;
      setContentOwned(this->mainContent , true) ;

      // this top-level desktop window
      Image icon_image = ImageCache::getFromMemory(BinaryData::audioxgeneric_png    ,
                                                   BinaryData::audioxgeneric_pngSize) ;
      setIcon(icon_image) ; getPeer()->setIcon(icon_image) ;

      setUsingNativeTitleBar(false) ;
      setTitleBarHeight(GUI::TITLEBAR_H) ;
      centreWithSize(getWidth() , getHeight()) ;
      setResizable(true , false) ;
      setVisible(true) ;
    }

    ~MainWindow() { this->mainContent = nullptr ; }

    void closeButtonPressed() override
    {
      JUCEApplication::getInstance()->systemRequestedQuit() ;
    }


  private:

    ScopedPointer<MainContent> mainContent ;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
  } ;


private:

    std::unique_ptr<MainWindow> mainWindow ;
} ;


START_JUCE_APPLICATION(AudioTagTooApplication)