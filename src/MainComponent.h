#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <melatonin_inspector/melatonin_inspector.h>

#include "Params.h"
#include "gui/GlobalLAF.h"
#include "components/NetStatus.h"

class Routing;       // forward declaration (see .cpp)
class SettingsPanel; // forward declaration (see .cpp)

class MainComponent final : public juce::Component
{
public:
  //==============================================================================
  MainComponent();
  ~MainComponent() override;

  //==============================================================================
  void paint(juce::Graphics &) override;
  void resized() override;

  // BACKEND
  ParamsFile params;
  std::unique_ptr<Routing> routing;

  // CHILD COMPONENTS
  NetStatus netStatus;
  std::unique_ptr<SettingsPanel> settingsPanel;

private:
  //==============================================================================

  // FRONTEND
  GLobalLAF globalLAF;

#ifdef JUCE_DEBUG
  melatonin::Inspector inspector;
#endif
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
