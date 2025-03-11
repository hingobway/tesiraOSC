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

  setSize(600, 400);
  setLookAndFeel(&globalLAF);

  b1.setButtonText("CONNECT");
  b1.onClick = [this]() { //
    routing->tesira_connect("", "");
  };

  // stacking order
  addAndMakeVisible(netStatus);
  addAndMakeVisible(b1);
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

  auto ipcb = netStatus.getTextBounds();
  netStatus.setBounds(px, getHeight() - py - ipcb.getHeight(), ipcb.getWidth(), ipcb.getHeight());
}
