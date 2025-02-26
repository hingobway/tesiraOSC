#include "MenuBar.h"

MenuBar::MenuBar() : menuItems{}
{
  juce::PopupMenu m;

  // MENUS ------------------------

  // m.addItem("itemname", []() {});
  // menuItems.add({"menuname", m});
  // m.clear();

  // ------------------------------

  juce::MenuBarModel::setMacMainMenu(this, nullptr);
}

MenuBar::~MenuBar()
{
  juce::MenuBarModel::setMacMainMenu(nullptr, nullptr);
}

juce::StringArray MenuBar::getMenuBarNames()
{
  juce::StringArray names{};
  for (const auto &it : this->menuItems)
  {
    names.add(it.name);
  }
  return names;
}

juce::PopupMenu MenuBar::getMenuForIndex(int topLevelMenuIndex, const juce::String &menuName)
{
  juce::ignoreUnused(menuName);

  return this->menuItems[topLevelMenuIndex].menu;
}

void MenuBar::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
  juce::ignoreUnused(menuItemID, topLevelMenuIndex);
}

void MenuBar::menuBarActivated(bool isActive)
{
  juce::ignoreUnused(isActive);
}
