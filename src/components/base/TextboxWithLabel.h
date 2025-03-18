#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../../util/colors.h"

#include "Textbox.h"
#include "Label.h"

class TextboxWithLabel : public juce::Component
{
  const int GAP = 2;
  const int TEXTBOX_HEIGHT = 30;

public:
  TextboxWithLabel()
  {
    textbox.setTextToShowWhenEmpty("placeholder", tw::ZINC_400);
    label.setText("label", juce::dontSendNotification);

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
