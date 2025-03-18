#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../../util/colors.h"
#include "../../util/fonts.h"

class Label : public juce::Label
{

public:
  Label()
  {
    setLookAndFeel(&laf);

    setColour(juce::Label::ColourIds::textColourId, tw::ZINC_400);
    setFont(fonts::Atkinson400().withHeight(17.5f));
  }
  ~Label()
  {
    setLookAndFeel(nullptr);
  }

  juce::Rectangle<float> minBounds()
  {
    juce::AttributedString s;
    s.append(getText(), getFont());
    return juce::TextLayout::getStringBounds(s);
  }

private:
  class LAF : public juce::LookAndFeel_V4
  {
  public:
    void drawLabel(juce::Graphics &g, juce::Label &label) override
    {
      g.fillAll(label.findColour(juce::Label::backgroundColourId));

      if (!label.isBeingEdited())
      {
        auto alpha = label.isEnabled() ? 1.0f : 0.5f;
        const juce::Font font(getLabelFont(label));

        g.setColour(label.findColour(juce::Label::textColourId).withMultipliedAlpha(alpha));
        g.setFont(font);

        auto textArea = getLabelBorderSize(label).subtractedFrom(label.getLocalBounds());

        g.drawFittedText(
            label.getText(), textArea, label.getJustificationType(),
            juce::jmax(1, (int)((float)textArea.getHeight() / font.getHeight())),
            label.getMinimumHorizontalScale());

        g.setColour(label.findColour(juce::Label::outlineColourId).withMultipliedAlpha(alpha));
      }
      else if (label.isEnabled())
      {
        g.setColour(label.findColour(juce::Label::outlineColourId));
      }

      g.drawRect(label.getLocalBounds());
    }
  };
  LAF laf;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Label)
};
