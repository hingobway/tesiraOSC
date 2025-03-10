#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../util/colors.h"
#include "../util/fonts.h"

class NetStatus : public juce::Component
{
public:
  enum Status
  {
    DISCONNECTED,
    CONNECTED
  };
  enum StatusType
  {
    IPC,
    OSC,
    TESIRA
  };

  NetStatus()
      : status{
            {IPC, DISCONNECTED},
            {OSC, DISCONNECTED},
            {TESIRA, DISCONNECTED},
        }
  {
    doTextLayout();
  }

  void doTextLayout()
  {
    auto tsize = 16.0f;
    auto tcolor = tw::ZINC_400;
    auto font = fonts::Atkinson400().withHeight(tsize);
    auto font_b = fonts::Atkinson700().withHeight(tsize);

    juce::AttributedString string{""};
    string.append("IPC: ", font, tcolor);
    string.append(sdata(IPC).text, font_b, sdata(IPC).color);
    string.append("\n");

    string.append("OSC: ", font, tcolor);
    string.append(sdata(OSC).text, font_b, sdata(OSC).color);
    string.append("\n");

    string.append("TESIRA: ", font, tcolor);
    string.append(sdata(TESIRA).text, font_b, sdata(TESIRA).color);

    text.createLayout(string, 300);
    text.recalculateSize();
  }

  void paint(juce::Graphics &g) override
  {
    text.draw(g, getLocalBounds().toFloat());
  }

  void resized() override
  {
  }

  juce::Rectangle<float> getTextBounds()
  {
    float h = 0;
    float w = 0;

    for (auto &line : text)
    {
      auto box = line.getLineBounds();
      if (box.getWidth() > w)
        w = box.getWidth();
      h += box.getHeight();
    }

    return juce::Rectangle<float>(0, 0, w, h);
  }

  void updateStatus(StatusType type, Status ns)
  {

    status[type] = ns;
    doTextLayout();

    repaint();
  }

private:
  juce::TextLayout text;

  std::unordered_map<StatusType, Status> status;

  struct StatusData
  {
    std::string text;
    juce::Colour color;
  };
  std::unordered_map<Status, StatusData> statusData{
      {CONNECTED, {"connected", tw::GREEN_600}},
      {DISCONNECTED, {"disconnected", tw::RED_500}},
  };

  inline StatusData sdata(StatusType s) { return statusData[status[s]]; }

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NetStatus)
};
