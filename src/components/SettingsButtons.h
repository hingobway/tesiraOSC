#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../util/colors.h"

#include "base/IconButton.h"

class SettingsButtons : public juce::Component
{
  const int GAP = 12;

public:
  SettingsButtons()
      : restart(IconButton::Icons::Restart, "Restart"),
        lockUnlock(IconButton::Icons::LockUnlock, "LockUnlock")
  {
    // config
    lockUnlock.setClickingTogglesState(true);

    // HANDLERS

    // button.onClick = [this]()
    // {
    //   auto &ips = parent->params.get().tesira;
    //   parent->routing->tesira_connect(ips.remoteAddress, ips.localAddress, ips.port);
    // };

    // stacking order
    addAndMakeVisible(restart);
    addAndMakeVisible(lockUnlock);
  }

  void paint(juce::Graphics &) override {}

  void resized() override
  {
    juce::FlexBox fb;
    fb.flexDirection = juce::FlexBox::Direction::row;
    {
      fb.items.add(juce::FlexItem(restart).withFlex(1));
      fb.items.add(juce::FlexItem().withWidth(GAP));
      fb.items.add(juce::FlexItem(lockUnlock).withFlex(1));
    }
    fb.performLayout(getLocalBounds());
  }

private:
  IconButton restart;
  IconButton lockUnlock;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SettingsButtons)
};
