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


#include "Constants/AppConstants.h"
#include "Constants/GuiConstants.h"
#include "Controllers/JuceBoilerplate.h"
#include "Trace/TraceMain.h"
#include "Views/Alert.h"
#include "Views/MainContent.h"


class JuceBoilerplateApplication : public JUCEApplication , private MultiTimer
{
public:

  JuceBoilerplateApplication() {}

  void initialise(const String& cli_args) override
  {
DEBUG_TRACE_INIT_VERSION

    this->mainWindow.reset(new MainWindow()) ;

    if (JuceBoilerplate::Initialize(this->mainWindow.get() , this->mainWindow->mainContent.get()))
    {
#ifdef JUCE_LINUX
      // create desktop launch file
      if (APP::DesktopFile().loadFileAsString() != APP::DesktopFileText())
        APP::DesktopFile().replaceWithText(APP::DesktopFileText()) ;

      // create desktop icon
      if (!APP::IconFile().existsAsFile())
      {
        PNGImageFormat    image_format = PNGImageFormat() ;
        Image             icon_image   = ImageCache::getFromMemory(BinaryData::audioxgeneric_png    ,
                                                                   BinaryData::audioxgeneric_pngSize) ;
        FileOutputStream* icon_stream  = new FileOutputStream(APP::IconFile()) ;

        if (!icon_stream->failedToOpen())
          image_format.writeImageToStream(icon_image , *icon_stream) ;
        delete icon_stream ;
      }
#endif // JUCE_LINUX

      // start main loop timers
      startTimers() ;
    }
    else if (Alert::AreAnyPending()) { setApplicationReturnValue(255) ; startTimers() ; }
    else                             { setApplicationReturnValue(255) ; quit() ;        }
  }

  void startTimers()
  {
DEBUG_QUIT_BEFORE_MAIN_LOOP // NOTE: may call quit()

    for (int timer_n = 0 ; timer_n < APP::N_TIMERS ; ++timer_n)
      startTimer(APP::TIMER_IDS[timer_n] , APP::TIMER_IVLS[timer_n]) ;
  }

  void stopTimers()
  {
    for (int timer_n = 0 ; timer_n > APP::N_TIMERS ; ++timer_n)
      stopTimer(APP::TIMER_IDS[timer_n]) ;
  }

  void shutdown() override
  {
DEBUG_TRACE_SHUTDOWN_IN

    stopTimers() ; JuceBoilerplate::Teardown() ;

    this->mainWindow = nullptr ;

DEBUG_TRACE_SHUTDOWN_OUT
  }

  void systemRequestedQuit()                          override { quit() ;                  }
  const String getApplicationName()                   override { return APP::APP_NAME ;    }
  const String getApplicationVersion()                override { return APP::APP_VERSION ; }
  bool moreThanOneInstanceAllowed()                   override { return true ;             }
  void anotherInstanceStarted(const String& cli_args) override {                           }


  class MainWindow : public DocumentWindow
  {
  public:

    MainWindow() : DocumentWindow(APP::APP_NAME , GUI::WINDOW_BG_COLOR , GUI::TITLEBAR_BTNS)
    {
      // main content component
      this->mainContent.reset(new MainContent()) ;
      setContentOwned(this->mainContent.get() , true) ;

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


    std::unique_ptr<MainContent> mainContent ;


  private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
  } ;


private:

  void timerCallback(int timer_id) override
  {
DEBUG_QUIT_AFTER_MAIN_LOOP // NOTE: may call quit()

      JuceBoilerplate::HandleTimer(timer_id) ;
  }


  std::unique_ptr<MainWindow> mainWindow ;
} ;


START_JUCE_APPLICATION(JuceBoilerplateApplication)
