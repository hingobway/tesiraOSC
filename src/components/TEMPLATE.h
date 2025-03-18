#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../util/colors.h"

class Template : public juce::Component
{
public:
  Template()
  {
    //
  }

  void paint(juce::Graphics &g) override {}
  void resized() override {}

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Template)
};
