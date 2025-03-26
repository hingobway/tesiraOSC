#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../../util/colors.h"
#include "../../util/fonts.h"

class PanelTitle : public juce::Component
{
  const int GAP = 8;

  const int FONT_SIZE = 20;
  const juce::FontOptions FONT = fonts::Atkinson400();

  enum ColourIds
  {
    borderColourId,
    textColourId,
  };

public:
  PanelTitle()
  {
    setColour(textColourId, tw::ZINC_100);
    setColour(borderColourId, tw::ZINC_700);
  }

  void paint(juce::Graphics &g) override
  {
    auto b = getLocalBounds();

    g.setColour(findColour(textColourId));
    g.setFont(FONT.withHeight((float)FONT_SIZE));
    g.drawText(title, b, juce::Justification::topLeft);

    g.setColour(findColour(borderColourId));
    g.drawHorizontalLine(b.getHeight() - 1, b.getX(), b.getRight());
  }
  void resized() override {}

  PanelTitle &setText(juce::String s)
  {
    title = s;
    repaint();
    return *this;
  }

  juce::Rectangle<float> minBounds()
  {
    juce::AttributedString s;
    s.append(title, FONT.withHeight((float)FONT_SIZE));
    auto b = juce::TextLayout::getStringBounds(s);
    return b.withHeight(b.getHeight() + float(GAP + 1));
  }

private:
  juce::String title;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PanelTitle)
};
