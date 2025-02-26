#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

#include "gui/Tray.h"
#include "gui/GlobalLAF.h"

class MainComponent final : public juce::Component
{
public:
  //==============================================================================
  MainComponent();
  ~MainComponent() override;

  //==============================================================================
  void paint(juce::Graphics &) override;
  void resized() override;

private:
  //==============================================================================

  GLobalLAF globalLAF;
  Tray trayIcon;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
