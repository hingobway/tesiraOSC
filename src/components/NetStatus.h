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
            {IPC, NetStatusSingle().setName("IPC").setStatus(DISCONNECTED)},
            {OSC, NetStatusSingle().setName("OSC").setStatus(DISCONNECTED)},
            {TESIRA, NetStatusSingle().setName("TESIRA").setStatus(DISCONNECTED)},
        }
  {
    // doTextLayout();
  }

  void paint(juce::Graphics &g) override
  {
    auto b = getLocalBounds().toFloat();

    float x_start = 0;
    for (auto &[type, text] : status)
    {
      text.getTextLayout().draw(g, b.withTrimmedLeft(x_start));
      x_start += text.getTextBounds().getWidth();
    }
  }

  void resized() override
  {
  }

  juce::Rectangle<float> minBounds()
  {
    juce::Rectangle<float> b{};
    for (auto &[type, text] : status)
    {
      auto tb = text.getTextBounds();
      b.setHeight(juce::jmax(b.getHeight(), tb.getHeight()));
      b.setWidth(b.getWidth() + tb.getWidth());
    }
    return b;
  }

  void updateStatus(StatusType type, Status ns)
  {
    status[type].setStatus(ns);
    repaint();
  }

  Status getStatus(StatusType type)
  {
    return status[type].getStatus();
  }

private:
  class NetStatusSingle
  {
  public:
    // SETTERS

    NetStatusSingle &setName(juce::String name_)
    {
      name = name_;
      renderFullString();
      return *this;
    }

    NetStatusSingle &setStatus(Status status_)
    {
      status = status_;
      renderFullString();
      return *this;
    }

    // GETTERS

    juce::TextLayout &getTextLayout() { return text; }
    juce::Rectangle<float> getTextBounds()
    {
      juce::Rectangle<float> b{};
      if (!text.getNumLines())
        return b;

      auto w = juce::TextLayout::getStringWidth(renderName()) + (float)STATUS_WIDTH;
      auto h = text.getLine(0).getLineBounds().getHeight();

      b.setBounds(0, 0, w, h);
      return b;
    }

    Status getStatus() { return status; }

  private:
    juce::AttributedString renderName()
    {
      auto tcolor = tw::ZINC_400;
      auto font = fonts::Atkinson400().withHeight(FONT_SIZE);

      juce::AttributedString s{""};
      s.append(name + ": ", font, tcolor);
      return s;
    }

    void renderFullString()
    {
      auto font_b = fonts::Atkinson700().withHeight(FONT_SIZE);

      juce::AttributedString string{""};
      string.append(renderName());
      string.append(currentStatus().text, font_b, currentStatus().color);

      text.createLayout(string, 300.0f);
      text.recalculateSize();
    }

    struct StatusData
    {
      std::string text;
      juce::Colour color;
    };
    std::unordered_map<Status, StatusData> statusData{
        {CONNECTED, {"connected", tw::GREEN_600}},
        {DISCONNECTED, {"disconnected", tw::RED_500}},
    };
    inline StatusData currentStatus() { return statusData[status]; }

    // ---------------------------------------------

    const int STATUS_WIDTH = 118;
    const float FONT_SIZE = 20.0f;

    juce::TextLayout text;

    juce::String name;
    Status status;
  };
  // -------------------------------------------------------

  std::map<StatusType, NetStatusSingle> status;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NetStatus)
};
