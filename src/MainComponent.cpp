#include "MainComponent.h"
#include "Routing.h"

#include "util/colors.h"
#include "util/fonts.h"

//==============================================================================
MainComponent::MainComponent()
#ifdef JUCE_DEBUG
    : inspector(*this, false)
#endif
{
  routing.reset(new Routing(this));

  setSize(518, 275);

  setLookAndFeel(&globalLAF);

  // stacking order
  addAndMakeVisible(netStatus);
  addAndMakeVisible(settingsPanel);
}

MainComponent::~MainComponent()
{
  setLookAndFeel(nullptr);
}

//==============================================================================
void MainComponent::paint(juce::Graphics &g)
{
  g.fillAll(tw::ZINC_900);
}

void MainComponent::resized()
{
  const int GAP = 24;

  juce::FlexBox fb{};
  fb.flexDirection = juce::FlexBox::Direction::column;
  {
    fb.items.add(juce::FlexItem(settingsPanel).withFlex(1));
    fb.items.add(juce::FlexItem().withHeight(GAP));
    fb.items.add(juce::FlexItem(netStatus).withHeight(netStatus.minBounds().getHeight()));
  }
  fb.performLayout(getLocalBounds().reduced(GAP));
}
