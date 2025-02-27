#include "Tray.h"

#include <BinaryData.h>

Tray::Tray(std::function<void()> quit)
{
  auto img = juce::ImageFileFormat::loadFrom(BinaryData::tray_png, BinaryData::tray_pngSize);
  this->setIconImage(img, img);

  menu.addItem(
      "Show Window", []()
      {
        juce::Process::setDockIconVisible(true);
        juce::Process::makeForegroundProcess(); });
  menu.addSeparator();
  menu.addItem("Quit", quit);
}

void Tray::mouseDown(const juce::MouseEvent &)
{
  this->showDropdownMenu(menu);
}
