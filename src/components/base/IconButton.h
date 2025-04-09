#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <BinaryData.h>

#include "../../util/colors.h"

class IconButton : public juce::DrawableButton
{
  static constexpr int SIZE = 20;
  static constexpr int BORDER_RADIUS = 12;

public:
  enum ColourIds
  {
    outlineHighlightColourId
  };

  enum Icons
  {
    LockUnlock,
    Restart
  };

  IconButton(Icons type_, juce::String buttonName)
      : juce::DrawableButton(buttonName, juce::DrawableButton::ButtonStyle::ImageFitted),
        type{type_},
        laf(*this)
  {
    setLookAndFeel(&laf);

    setColour(juce::DrawableButton::backgroundOnColourId, tw::ZINC_800);
    setColour(juce::DrawableButton::backgroundColourId, tw::ZINC_800);
    setColour(ColourIds::outlineHighlightColourId, tw::ZINC_700);

    setMouseCursor(juce::MouseCursor::PointingHandCursor);

    useVariant(type);
  }
  ~IconButton() override
  {
    setLookAndFeel(nullptr);
  }

  IconButton &useVariant(Icons type_)
  {
    type = type_;
    if (type == Icons::LockUnlock)
    {
      svg = juce::Drawable::createFromImageData(BinaryData::IconLock_svg, BinaryData::IconLock_svgSize);
      svgOn = juce::Drawable::createFromImageData(BinaryData::IconUnlock_svg, BinaryData::IconUnlock_svgSize);

      setColour(juce::DrawableButton::backgroundOnColourId, tw::RED_900);
      return *this;
    }
    svgOn = nullptr;

    if (type == Icons::Restart)
    {
      svg = juce::Drawable::createFromImageData(BinaryData::IconRestart_svg, BinaryData::IconRestart_svgSize);
    }

    return *this;
  }

  std::function<void()> onClickSync;

private:
  Icons type;
  std::unique_ptr<juce::Drawable> svg;
  std::unique_ptr<juce::Drawable> svgOn;

  void clicked() override
  {
    if (onClickSync)
      onClickSync();
  }

  class LAF : public juce::LookAndFeel_V4
  {
    IconButton &parent;

  public:
    LAF(IconButton &parent_) : parent{parent_} {}

    void drawDrawableButton(juce::Graphics &g, juce::DrawableButton &button,
                            bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
    {
      juce::ignoreUnused(shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);

      // get state
      bool isOn = button.getToggleState();

      auto bounds = button.getLocalBounds();

      // draw background
      g.setColour(button.findColour(isOn ? juce::DrawableButton::backgroundOnColourId : juce::DrawableButton::backgroundColourId));
      g.fillRoundedRectangle(bounds.toFloat(), (float)BORDER_RADIUS);

      // draw focus outline
      if (shouldDrawButtonAsHighlighted || shouldDrawButtonAsDown)
      {
        g.setColour(juce::Colours::white.withAlpha(0.1f));
        g.drawRoundedRectangle(bounds.reduced(1).toFloat(), (float)(BORDER_RADIUS - 1), 1.0f);
      }

      // draw icon

      // separate on state
      if (parent.svgOn != nullptr && isOn)
      {
        drawIcon(g, *parent.svgOn.get(), bounds);
        return;
      }

      // check for no icon
      if (parent.svg == nullptr)
        return;

      // draw icon
      drawIcon(g, *parent.svg.get(), bounds);
    }

  private:
    static inline void drawIcon(juce::Graphics &g, juce::Drawable &d, juce::Rectangle<int> bounds)
    { //
      int bcx = bounds.getCentreX();
      int bcy = bounds.getCentreY();
      int icx = d.getBounds().getCentreX();
      int icy = d.getBounds().getCentreY();
      d.drawAt(g, float(bcx - icx), float(bcy - icy), 1.0f);
    }
  };
  LAF laf;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IconButton)
};
