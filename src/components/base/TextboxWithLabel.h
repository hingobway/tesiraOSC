#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../../util/colors.h"

#include "Textbox.h"
#include "Label.h"

class TextboxWithLabel : public juce::Component
{
  const int GAP = 2;
  const int TEXTBOX_HEIGHT = 30;
  const juce::Colour COLOR_TEXT_PLACEHOLDER = tw::ZINC_500;

public:
  TextboxWithLabel()
  {
    textbox.setTextToShowWhenEmpty("placeholder", COLOR_TEXT_PLACEHOLDER);
    label.setText("label", juce::dontSendNotification);
    textbox.setIndents(8, 0);

    addAndMakeVisible(label);
    addAndMakeVisible(textbox);
  }

  void paint(juce::Graphics &) override
  {
  }
  void resized() override
  {
    juce::FlexBox fb;

    fb.flexDirection = juce::FlexBox::Direction::column;
    {
      fb.items.add(juce::FlexItem(label).withHeight(label.minBounds().getHeight()));
      fb.items.add(juce::FlexItem().withHeight(GAP));
      fb.items.add(juce::FlexItem(textbox).withFlex(1));
    }
    fb.performLayout(getLocalBounds());
  }

  TextboxWithLabel &setLabelText(juce::String text)
  {
    label.setText(text, juce::dontSendNotification);
    return *this;
  }

  TextboxWithLabel &setPlaceholder(juce::String text)
  {
    textbox.setTextToShowWhenEmpty(text, COLOR_TEXT_PLACEHOLDER);
    return *this;
  }

  Textbox &getTextbox() { return textbox; }

  juce::Rectangle<float> minBounds()
  {
    auto b = label.minBounds();
    return b.withHeight(b.getHeight() + float(GAP + TEXTBOX_HEIGHT));
  }

private:
  Label label;
  Textbox textbox;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TextboxWithLabel)
};
