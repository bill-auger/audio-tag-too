#include "GuiConstants.h"


// MainWindow
const uint8  GUI::BORDERS_W       = 2 ;
const uint8  GUI::TITLEBAR_H      = 24 ;
const uint16 GUI::WINDOW_W        = 768 - BORDERS_W ;              // jucer 766
const uint16 GUI::WINDOW_H        = 768 - BORDERS_W - TITLEBAR_H ; // jucer 742
const Colour GUI::WINDOW_BG_COLOR = Colour(0xFF404040) ;
const int    GUI::TITLEBAR_BTNS   = DocumentWindow::allButtons ;
