#pragma once

#include <functional>
#include <juce_gui_extra/juce_gui_extra.h>

#include "MenuBar.h"

class Tray : juce::SystemTrayIconComponent
{
public:
  Tray(std::function<void()> quit);

  void mouseDown(const juce::MouseEvent &) override;

private:
  MenuBar menubar;

  juce::PopupMenu menu;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Tray)
};
