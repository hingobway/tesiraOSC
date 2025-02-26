#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

#include "MenuBar.h"

class Tray : juce::SystemTrayIconComponent
{
public:
  Tray();

  void mouseDown(const juce::MouseEvent &) override;

private:
  MenuBar menubar;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Tray)
};
