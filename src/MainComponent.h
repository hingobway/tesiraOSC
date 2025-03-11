#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <melatonin_inspector/melatonin_inspector.h>

#include "gui/GlobalLAF.h"

#include "components/NetStatus.h"
#include "components/Button.h"

class Routing; // forward declaration (see .cpp)

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
  NetStatus netStatus;

private:
  //==============================================================================

  // BACKEND
  std::unique_ptr<Routing> routing;

  // FRONTEND
  GLobalLAF globalLAF;

  Button b1;

#ifdef JUCE_DEBUG
  melatonin::Inspector inspector;
#endif
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
