#include "MainComponent.h"

#include "util/colors.h"

//==============================================================================
MainComponent::MainComponent()
{
  setSize(600, 400);
  setLookAndFeel(&globalLAF);
}

MainComponent::~MainComponent()
{
  setLookAndFeel(nullptr);
}

//==============================================================================
void MainComponent::paint(juce::Graphics &g)
{
  g.fillAll(tw::ZINC_900);

  g.setFont(juce::FontOptions(20.0f));
  g.setColour(tw::ZINC_100);

  g.drawText("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
  //
}
