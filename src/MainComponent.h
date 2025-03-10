#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <melatonin_inspector/melatonin_inspector.h>

#include "gui/GlobalLAF.h"

#include "components/IPCStatus.h"

class Network; // forward declaration (see .cpp)

class MainComponent final : public juce::Component
{
public:
  //==============================================================================
  MainComponent();
  ~MainComponent() override;

  //==============================================================================
  void paint(juce::Graphics &) override;
  void resized() override;

  // CHILD COMPONENTS
  IPCStatus ipcStatus;

private:
  //==============================================================================

  // BACKEND
  std::unique_ptr<Network> network;

  // FRONTEND
  GLobalLAF globalLAF;

  juce::TextButton b1;
  juce::Label l1;

#ifdef JUCE_DEBUG
  melatonin::Inspector inspector;
#endif
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
