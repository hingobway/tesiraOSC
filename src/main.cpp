#include "MainComponent.h"

#include "gui/Tray.h"
#include "util/colors.h"

//==============================================================================
class TTApplication final : public juce::JUCEApplication
{
public:
  //==============================================================================
  TTApplication()
  {
  }

  const juce::String getApplicationName() override { return JUCE_APPLICATION_NAME_STRING; }
  const juce::String getApplicationVersion() override { return JUCE_APPLICATION_VERSION_STRING; }
  bool moreThanOneInstanceAllowed() override { return true; }

  //==============================================================================
  void initialise(const juce::String &commandLine) override
  {
    juce::ignoreUnused(commandLine);
    mainWindow.reset(new MainWindow(getApplicationName()));
  }

  void shutdown() override
  {
    // Add your application's shutdown code here..

    mainWindow = nullptr; // (deletes our window)
  }

  //==============================================================================
  void systemRequestedQuit() override
  {
    // This is called when the app is being asked to quit: you can ignore this
    // request and let the app carry on running, or call quit() to allow the app to close.
    quit();
  }

  void anotherInstanceStarted(const juce::String &commandLine) override
  {
    // When another instance of the app is launched while this one is running,
    // this method is invoked, and the commandLine parameter tells you what
    // the other instance's command-line arguments were.
    juce::ignoreUnused(commandLine);
  }

  //==============================================================================
  /*
      This class implements the desktop window that contains an instance of
      our MainComponent class.
  */
  class MainWindow final : public juce::DocumentWindow
  {
  public:
    explicit MainWindow(juce::String name)
        : DocumentWindow(name, tw::ZINC_900, allButtons),

          //  init system tray menu with quit button
          tray([]()
               { getInstance()->systemRequestedQuit(); })
    {
      setUsingNativeTitleBar(true);
      setContentOwned(new MainComponent(), true);

      setResizable(false, false);
      centreWithSize(getWidth(), getHeight());

      setVisible(true);
    }

    void closeButtonPressed() override
    {
      juce::Process::hide();
    }

    /* Note: Be careful if you override any DocumentWindow methods - the base
       class uses a lot of them, so by overriding you might break its functionality.
       It's best to do all your work in your content component instead, but if
       you really have to override any DocumentWindow methods, make sure your
       subclass also calls the superclass's method.
    */

  private:
    Tray tray;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
  };

private:
  std::unique_ptr<MainWindow> mainWindow;
};

//==============================================================================
START_JUCE_APPLICATION(TTApplication)
