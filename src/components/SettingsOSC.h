#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../util/colors.h"
#include "base/Panel.h"
#include "base/TextboxWithLabel.h"

class SettingsOSC : public Panel
{
  const int PORT_WIDTH = 90;

public:
  SettingsOSC()
  {
    title.setText("OSC");
    port.setLabelText("port");

    addAndMakeVisible(port);
  }

  void resized() override
  {
    juce::FlexBox fb;

    fb.flexDirection = juce::FlexBox::Direction::column;
    {
      // title
      fb.items.add(juce::FlexItem(title)
                       .withHeight(title.minBounds().getHeight()));

      fb.items.add(juce::FlexItem().withHeight(GAP));

      // settings
      fb.items.add(juce::FlexItem(port)
                       .withHeight(port.minBounds().getHeight()));
    }

    fb.performLayout(getLocalBounds().reduced(PAD));
  }

  juce::Rectangle<float> minBounds()
  {
    juce::Rectangle<float> b;
    b.setWidth(float(PORT_WIDTH + PAD * 2));
    b.setHeight(title.minBounds().getHeight() + float(GAP) + port.minBounds().getHeight());

    return b;
  }

private:
  TextboxWithLabel port;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SettingsOSC)
};
