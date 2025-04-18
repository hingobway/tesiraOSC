#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../util/fonts.h"

class GLobalLAF : public juce::LookAndFeel_V4
{
public:
  GLobalLAF()
  {
    setDefaultLookAndFeel(this);
  }
  ~GLobalLAF()
  {
    setDefaultLookAndFeel(nullptr);
  }

  juce::Typeface::Ptr getTypefaceForFont(const juce::Font &)
  {
    return fonts::Atkinson400Typeface();
  }

private:
};
