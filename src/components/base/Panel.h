#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../../util/colors.h"
#include "PanelTitle.h"

class Panel : public juce::Component
{

  const juce::Colour BG_COLOR = tw::ZINC_800;

public:
  Panel()
  {
    addAndMakeVisible(title);
  }

  void paint(juce::Graphics &g) override
  {
    g.setColour(BG_COLOR);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), BORDER_RADIUS);
  }

  void resized() override
  {
  }

protected:
  int PAD = 16;
  int GAP = 12;
  int BORDER_RADIUS = 16;

  PanelTitle title;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Panel)
};
