#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "../util/colors.h"
#include "../MainComponent.h"
#include "../Params.h"

#include "SettingsTesira.h"
#include "SettingsOSC.h"
#include "base/Button.h"

class SettingsPanel : public juce::Component
{
  const int GAP = 24;

public:
  SettingsPanel(MainComponent *parent_)
      : parent(parent_),
        tesira(parent->params), osc(parent->params)
  {
    button.setButtonText("CONNECT");

    button.onClick = [this]()
    {
      parent->routing->tesira_connect("169.254.3.243", "169.254.3.240");
      for (auto ip : juce::IPAddress::getAllAddresses())
      {
        DBG("ADDRESS: " << ip.toString());
      }
    };

    // parent->params.setParams([](Params &p){
    // });

    addAndMakeVisible(tesira);
    addAndMakeVisible(osc);
    addAndMakeVisible(button);
  }

  void paint(juce::Graphics &) override
  {
  }

  void resized() override
  {
    juce::FlexBox fb;
    juce::FlexBox fb2;

    {
      fb.items.add(juce::FlexItem(tesira).withFlex(1));
      fb.items.add(juce::FlexItem().withWidth(GAP));

      fb2.flexDirection = juce::FlexBox::Direction::column;
      {
        fb2.items.add(juce::FlexItem(osc)
                          .withHeight(osc.minBounds().getHeight()));
        fb2.items.add(juce::FlexItem().withHeight(GAP));
        fb2.items.add(juce::FlexItem(button).withFlex(1));
      }
      fb.items.add(juce::FlexItem(fb2)
                       .withWidth(osc.minBounds().getHeight()));
    }
    fb.performLayout(getLocalBounds());
  }

private:
  MainComponent *parent;

  SettingsTesira tesira;
  SettingsOSC osc;
  Button button;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SettingsPanel)
};
