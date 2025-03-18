#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "../util/colors.h"

class SettingsPanel : public juce::Component
{
public:
  SettingsPanel()
  {
  }

  void paint(juce::Graphics &g) override
  {
    g.fillAll(tw::RED_500.withAlpha(.5f));
  }

  void resized() override
  {
  }

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SettingsPanel)
};
