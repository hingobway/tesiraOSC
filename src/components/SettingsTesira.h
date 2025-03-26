#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../Params.h"
#include "../util/colors.h"
#include "base/Panel.h"
#include "base/TextboxWithLabel.h"

class SettingsTesira : public Panel
{
  const int PORT_WIDTH = 72;

public:
  SettingsTesira(ParamsFile &p_) : params(p_)
  {
    // config
    title.setText("TESIRA");
    port.setLabelText("port");
    port.getTextbox().setInputRestrictions(6, "0123456789");
    remoteAddress.setLabelText("remote address");
    remoteAddress.setPlaceholder("192.168.0.XX");
    localAddress.setLabelText("bind to local address");
    localAddress.setPlaceholder("192.168.0.XX");

    // BINDS

    // bind port
    auto portNum = params.get().tesira.port;
    port.getTextbox().setText(portNum > 0 ? juce::String(portNum) : "");
    port.getTextbox().onTextChange = [this]()
    {
      params.set([this](Params &p) { //
        auto newPort = port.getTextbox().getText().getIntValue();
        p.tesira.port = newPort > 0 ? newPort : 0;
      });
    };

    // bind remote address
    remoteAddress.getTextbox().setText(params.get().tesira.remoteAddress);
    remoteAddress.getTextbox().onTextChange = [this]()
    {
      params.set([this](Params &p) { //
        p.tesira.remoteAddress = remoteAddress.getTextbox().getText().toStdString();
      });
    };

    // bind local address
    localAddress.getTextbox().setText(params.get().tesira.localAddress);
    localAddress.getTextbox().onTextChange = [this]()
    {
      params.set([this](Params &p) { //
        p.tesira.localAddress = localAddress.getTextbox().getText().toStdString();
      });
    };

    // stacking order
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
