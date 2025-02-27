#include "MainComponent.h"

#include "util/colors.h"

//==============================================================================
MainComponent::MainComponent()
{
  setSize(600, 400);
  setLookAndFeel(&globalLAF);

  b1.setButtonText("GET NUM");
  l1.setText("OUTPUT", juce::dontSendNotification);
  l1.setFont(juce::FontOptions(20.0f));
  l1.setColour(juce::Label::ColourIds::textColourId, tw::ZINC_100);

  b1.onClick = [this]()
  {
    auto num = socket.getSelectedCueNumber(NetSocket::UDP);
    l1.setText("output: " + num, juce::dontSendNotification);
  };

  addAndMakeVisible(b1);
  addAndMakeVisible(l1);
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
  const int bw = 120;
  const int bh = 32;

  const int px = 24;
  const int py = 24;

  b1.setBounds(getWidth() - bw - px, getHeight() - py - bh, bw, bh);

  l1.setBounds(px, py, getWidth() - px * 2, bh);
}
