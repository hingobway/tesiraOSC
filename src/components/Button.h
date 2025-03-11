#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../util/colors.h"

class Button : public juce::TextButton
{

public:
  Button()
  {
    setLookAndFeel(&laf);

    setColour(juce::TextButton::ColourIds::textColourOnId, tw::ZINC_100);
    setColour(juce::TextButton::ColourIds::textColourOffId, tw::ZINC_100);
    setColour(juce::TextButton::ColourIds::buttonColourId, tw::ZINC_800);
    setColour(juce::TextButton::ColourIds::buttonOnColourId, tw::SKY_600);
    setColour(juce::ComboBox::outlineColourId, juce::Colour().withAlpha(0.0f));
  }
  ~Button()
  {
    setLookAndFeel(nullptr);
  }

private:
  class LAF : public juce::LookAndFeel_V4
  {
  public:
    void drawButtonBackground(
        juce::Graphics &g,
        juce::Button &button,
        const juce::Colour &backgroundColour,
        bool shouldDrawButtonAsHighlighted,
        bool shouldDrawButtonAsDown)
    {

      auto bounds = button.getLocalBounds().toFloat();
      auto cornerSize = bounds.getHeight() / 2.0f;

      auto baseColour =
          backgroundColour
              .withMultipliedSaturation(button.hasKeyboardFocus(true) ? 1.3f : 0.9f)
              .withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.5f);

      if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
        baseColour = baseColour.contrasting(shouldDrawButtonAsDown ? 0.2f : 0.05f);

      g.setColour(baseColour);
      g.fillRoundedRectangle(bounds, cornerSize);

      g.setColour(button.findColour(juce::ComboBox::outlineColourId));
      g.drawRoundedRectangle(bounds.reduced(0.5f), cornerSize, 1.0f);
    }
  };

  LAF laf;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Button)
};
