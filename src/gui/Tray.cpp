#include "Tray.h"

#include <BinaryData.h>

Tray::Tray(juce::DocumentWindow &win_, std::function<void()> quit) : win(win_)
{
  auto img = juce::ImageFileFormat::loadFrom(BinaryData::tray_png, BinaryData::tray_pngSize);
  this->setIconImage(img, img);

  menu.addItem(
      "Show Window", [this]()
      {
        win.setVisible(true);
        juce::Process::setDockIconVisible(true); });
  menu.addSeparator();
  menu.addItem("Quit", quit);
}

void Tray::mouseDown(const juce::MouseEvent &)
{
  this->showDropdownMenu(menu);
}
