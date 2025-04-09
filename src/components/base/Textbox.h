#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../../util/colors.h"
#include "../../util/fonts.h"

class Textbox : public juce::TextEditor
{
public:
  Textbox()
  {
    setLookAndFeel(&laf);

    // PROPERTIES
    auto pfs = getProperties()["font-size"];
    auto FONT_SIZE = pfs.isDouble() ? (float)pfs : 16.0f;

    // DEFAULTS
    setColour(juce::TextEditor::backgroundColourId, juce::Colour().withAlpha(0.0f));
    setColour(juce::TextEditor::outlineColourId, tw::ZINC_700);
    setColour(juce::TextEditor::focusedOutlineColourId, tw::ZINC_500);
    setColour(juce::TextEditor::ColourIds::textColourId, tw::ZINC_100);

    setFont(fonts::Atkinson400().withHeight(FONT_SIZE));

    setJustification(juce::Justification::centredLeft);
  }
  ~Textbox()
  {
    setLookAndFeel(nullptr);
  }

private:
  class LAF : public juce::LookAndFeel_V4
  {
    // PARAMS
    const int BORDER_RADIUS = 8;
    const int BORDER_WIDTH = 1;

  public:
    void drawTextEditorOutline(juce::Graphics &g, int width, int height, juce::TextEditor &textEditor) override
    {
      // set color
      if (textEditor.hasKeyboardFocus(true) && !textEditor.isReadOnly())
        g.setColour(textEditor.findColour(juce::TextEditor::focusedOutlineColourId));
      else
        g.setColour(textEditor.findColour(juce::TextEditor::outlineColourId));

      // draw
      g.drawRoundedRectangle(juce::Rectangle<int>(0, 0, width, height).reduced(1).toFloat(), BORDER_RADIUS, BORDER_WIDTH);
    }

    void fillTextEditorBackground(juce::Graphics &g, int width, int height, juce::TextEditor &textEditor) override
    {
      g.setColour(textEditor.findColour(juce::TextEditor::backgroundColourId));

      if (!textEditor.isEnabled())
        g.setColour(juce::Colours::white.withAlpha(0.2f));
      g.fillRoundedRectangle(juce::Rectangle<int>(0, 0, width, height).toFloat(), BORDER_RADIUS);
    }
  };
  LAF laf;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Textbox)
};
