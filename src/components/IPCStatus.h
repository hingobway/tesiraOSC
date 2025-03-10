#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../util/colors.h"
#include "../util/fonts.h"

class IPCStatus : public juce::Component
{
public:
  enum Status
  {
    CONNECTED,
    DISCONNECTED
  };

  IPCStatus()
  {
    updateStatus(DISCONNECTED);
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
    return juce::TextLayout::getStringBounds(string);
  }

  void updateStatus(Status status)
  {
    auto height = 16.0f;

    string = juce::AttributedString("");
    string.append("IPC: ", fonts::Atkinson400().withHeight(height), tw::ZINC_400);
    string.append(statusText[status].text, fonts::Atkinson700().withHeight(height), statusText[status].color);
    text.createLayout(string, 300);
    repaint();
  }

private:
  juce::AttributedString string;
  juce::TextLayout text;

  struct StatusData
  {
    std::string text;
    juce::Colour color;
  };
  std::unordered_map<Status, StatusData> statusText{
      {CONNECTED, {"connected", tw::GREEN_600}},
      {DISCONNECTED, {"disconnected", tw::RED_500}},
  };

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IPCStatus)
};
