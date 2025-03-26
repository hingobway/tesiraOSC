#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../Params.h"
#include "../util/colors.h"
#include "base/Panel.h"
#include "base/TextboxWithLabel.h"

class SettingsOSC : public Panel
{
  const int PORT_WIDTH = 72;

public:
  SettingsOSC(ParamsFile &p_) : params(p_)
  {
    // config
    title.setText("OSC");
    port.setLabelText("port")
        .setPlaceholder("57820");
    port.getTextbox().setInputRestrictions(6, "0123456789");

    // bind port
    auto portNum = params.get().osc.port;
    port.getTextbox().setText(portNum > 0 ? juce::String(portNum) : "");
    port.getTextbox().onTextChange = [this]()
    {
      params.set([this](Params &p) { //
        auto newPort = port.getTextbox().getText().getIntValue();
        p.osc.port = newPort > 0 ? newPort : 0;
      });
    };

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
    b.setHeight(title.minBounds().getHeight() + float(GAP + PAD * 2) + port.minBounds().getHeight());

    return b;
  }

private:
  TextboxWithLabel port;

  ParamsFile &params;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SettingsOSC)
};
