#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../../util/colors.h"

#include "Textbox.h"
#include "Label.h"

class TextboxWithLabel : public juce::Component
{
public:
  TextboxWithLabel()
  {
    //
  }

  void paint(juce::Graphics &g) override {}
  void resized() override {}

  TextboxWithLabel &setLabelText(juce::String text)
  {
    label.setText(text, juce::dontSendNotification);
    return *this;
  }

private:
  Label label;
  Textbox textbox;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TextboxWithLabel)
};
