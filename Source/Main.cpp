
#include "Constants/AppConstants.h"
#include "Constants/GuiConstants.h"
#include "Views/MainContent.h"


class JuceBoilerplateApplication : public JUCEApplication
{
public:

  JuceBoilerplateApplication() {}

  void initialise(const String& commandLine) override
  {
    mainWindow.reset(new MainWindow()) ;

    if (! true /*JuceBoilerplate::Init()*/) { setApplicationReturnValue(255) ; quit() ; }
  }

  void shutdown() override { mainWindow = nullptr ; }

  void systemRequestedQuit() override { quit() ; }

  void anotherInstanceStarted(const String& command_line) override {}

  const String getApplicationName()    override { return ProjectInfo::projectName ; }

  const String getApplicationVersion() override { return ProjectInfo::versionString ; }

  bool moreThanOneInstanceAllowed()    override { return true ; }


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


  private:

    std::unique_ptr<MainContent> mainContent ;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
  } ;


private:

    std::unique_ptr<MainWindow> mainWindow ;
} ;


START_JUCE_APPLICATION(JuceBoilerplateApplication)
