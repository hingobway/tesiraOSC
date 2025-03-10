#pragma once

#include <juce_core/juce_core.h>

namespace Obj
{
  using Ptr = juce::DynamicObject::Ptr;
}
#define JSON_OBJ(name) Obj::Ptr name = new juce::DynamicObject();

#define JSNIL juce::var()
