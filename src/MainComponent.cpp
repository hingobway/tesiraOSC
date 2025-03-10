#include "MainComponent.h"
#include "net/Network.h"

#include "util/colors.h"
#include "util/fonts.h"

//==============================================================================
MainComponent::MainComponent()
#ifdef JUCE_DEBUG
    : inspector(*this, false)
#endif
{
  network.reset(new Network(this));

  setSize(600, 400);
  setLookAndFeel(&globalLAF);

  b1.setButtonText("BUTTON");
  l1.setText("OUTPUT", juce::dontSendNotification);
  l1.setFont(fonts::Atkinson400().withHeight(20.0f));
  l1.setColour(juce::Label::ColourIds::textColourId, tw::ZINC_100);

  b1.onClick = [this]() { //
    network->commandSendTesira("abc def ghi");
  };

  addAndMakeVisible(ipcStatus);

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

  auto ipcb = ipcStatus.getTextBounds();
  ipcStatus.setBounds(px, getHeight() - py - ipcb.getHeight(), ipcb.getWidth(), ipcb.getHeight());
}
