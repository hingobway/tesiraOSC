#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

#include "gui/GlobalLAF.h"
#include "net/NetSocket.h"
#include "net/IPC.h"

class MainComponent final : public juce::Component
{
public:
  //==============================================================================
  MainComponent();
  ~MainComponent() override;

  //==============================================================================
  void paint(juce::Graphics &) override;
  void resized() override;

private:
  //==============================================================================

  // BACKEND
  // NetSocket socket;
  IPC ipc;

  // FRONTEND
  GLobalLAF globalLAF;

  juce::TextButton b1;
  juce::Label l1;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
