#include "Tray.h"

#include <juce_graphics/juce_graphics.h>

#include <BinaryData.h>

Tray::Tray()
{
  auto img = juce::ImageFileFormat::loadFrom(BinaryData::tray_png, BinaryData::tray_pngSize);

  this->setIconImage(img, img);
}

void Tray::mouseDown(const juce::MouseEvent &)
{

  juce::PopupMenu menu;
  menu.addItem("Item One", []()
               { DBG("ITEM 1"); });

  this->showDropdownMenu(menu);
}
