#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../Params.h"
#include "../util/colors.h"
#include "base/Panel.h"
#include "base/TextboxWithLabel.h"

class SettingsTesira : public Panel
{
  const int PORT_WIDTH = 64;

public:
  SettingsTesira(ParamsFile &p_) : params(p_)
  {
    title.setText("TESIRA");
    remoteAddress.setLabelText("remote address");
    port.setLabelText("port");
    localAddress.setLabelText("bind to local address");

    addAndMakeVisible(remoteAddress);
    addAndMakeVisible(port);
    addAndMakeVisible(localAddress);
  }

  void resized() override
  {
    juce::FlexBox fb;
    juce::FlexBox fb2;
    juce::FlexBox fb3;

    fb.flexDirection = juce::FlexBox::Direction::column;
    {
      // title
      fb.items.add(juce::FlexItem(title)
                       .withHeight(title.minBounds().getHeight()));

      fb.items.add(juce::FlexItem().withHeight(GAP));

      // row 1
      fb2.flexDirection = juce::FlexBox::Direction::row;
      {
        fb2.items.add(juce::FlexItem(remoteAddress).withFlex(1));
        fb2.items.add(juce::FlexItem().withWidth(GAP));
        fb2.items.add(juce::FlexItem(port).withWidth(PORT_WIDTH));
      }
      fb.items.add(juce::FlexItem(fb2)
                       .withHeight(remoteAddress.minBounds().getHeight()));

      fb.items.add(juce::FlexItem().withHeight(GAP));

      // row 2
      fb3.flexDirection = juce::FlexBox::Direction::row;
      {
        fb3.items.add(juce::FlexItem(localAddress).withFlex(1));
        fb3.items.add(juce::FlexItem().withWidth(GAP + PORT_WIDTH));
      }
      fb.items.add(juce::FlexItem(fb3)
                       .withHeight(localAddress.minBounds().getHeight()));
    }

    fb.performLayout(getLocalBounds().reduced(PAD));
  }

private:
  TextboxWithLabel remoteAddress;
  TextboxWithLabel port;
  TextboxWithLabel localAddress;

  ParamsFile &params;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SettingsTesira)
};
