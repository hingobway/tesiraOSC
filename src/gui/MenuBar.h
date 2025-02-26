#pragma once

#include <functional>
#include <juce_gui_basics/juce_gui_basics.h>

class MenuBar : juce::MenuBarModel
{
public:
  MenuBar();
  ~MenuBar();

  juce::StringArray getMenuBarNames();
  juce::PopupMenu getMenuForIndex(int topLevelMenuIndex, const juce::String &menuName);
  void menuItemSelected(int menuItemID, int topLevelMenuIndex);
  void menuBarActivated(bool isActive);

private:
  struct MenuItem
  {
    juce::String name;
    juce::PopupMenu menu;
  };

  juce::Array<MenuItem> menuItems;
};
