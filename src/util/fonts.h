#pragma once

#include <juce_graphics/juce_graphics.h>

#include "BinaryData.h"

namespace fonts
{
  static juce::Typeface::Ptr Atkinson400Typeface()
  {
    static auto font = juce::Typeface::createSystemTypefaceFor(
        BinaryData::AtkinsonHyperlegibleRegular_ttf, BinaryData::AtkinsonHyperlegibleRegular_ttfSize);
    return font;
  }
  inline juce::FontOptions Atkinson400()
  {
    return juce::FontOptions(Atkinson400Typeface());
  }
  
  static juce::Typeface::Ptr Atkinson700Typeface()
  {
    static auto font = juce::Typeface::createSystemTypefaceFor(
        BinaryData::AtkinsonHyperlegibleBold_ttf, BinaryData::AtkinsonHyperlegibleBold_ttfSize);
    return font;
  }
  inline juce::FontOptions Atkinson700()
  {
    return juce::FontOptions(Atkinson700Typeface());
  }
}
