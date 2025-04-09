#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../Params.h"
#include "../util/colors.h"
#include "../Routing.h"

#include "base/IconButton.h"

class SettingsButtons : public juce::Component
{
  const int GAP = 12;

public:
  SettingsButtons(ParamsFile &p_, Routing &r_)
      : params(p_), routing(r_),

        restart(IconButton::Icons::Restart, "Restart"),
        lockUnlock(IconButton::Icons::LockUnlock, "LockUnlock")
  {
    // config
    lockUnlock.setClickingTogglesState(true);

    // HANDLERS
    lockUnlock.onClick = [this]()
    {
      auto isLocked = !lockUnlock.getToggleState();
      // update params file
      params.set([isLocked](Params &p)
                 { p.isLocked = isLocked; });

      //  run lock commands
      routing.system_lock(isLocked);
    };
    restart.onClick = [this]()
    {
      routing.system_lock(true, true);
    };

    // bind lock unlock
    lockUnlock.setToggleState(!params.get().isLocked, juce::sendNotification);

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
  ParamsFile &params;
  Routing &routing;

  IconButton restart;
  IconButton lockUnlock;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SettingsButtons)
};
