
#include "constants.h"


// MainWindow
const int    GUI::BORDERS_W       = 2 ;
const int    GUI::TITLEBAR_H      = 24 ;
const int    GUI::WINDOW_W        = 768 - BORDERS_W ;              // jucer 766
const int    GUI::WINDOW_H        = 768 - BORDERS_W - TITLEBAR_H ; // jucer 742
const Colour GUI::WINDOW_BG_COLOR = Colour(0xff202020) ;
const int    GUI::TITLEBAR_BTNS   = DocumentWindow::minimiseButton | DocumentWindow::closeButton ; // allButtonsallButtons

