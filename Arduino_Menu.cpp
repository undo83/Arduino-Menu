
#include "Arduino_Menu.h"
/*
#include "AM_EEPROM.cpp"
#include "AM_controller.cpp"
#include "AM_input.cpp"
#include "AM_navigation.cpp"
#include "AM_output.cpp"
#include "AM_range.cpp"
#include "AM_setup.cpp"
*/
#if defined AM_PLUGINS_SERIAL
  #include "AM_Serial.h"
#endif
#if defined AM_PLUGINS_LIQUIDCRYSTAL
  #include "AM_LiquidCrystal.h"
#endif
#if defined AM_PLUGINS_OLED_SSD1306
  #include "AM_OledSSD1306.h"
#endif
#if defined AM_PLUGINS_UCGLIB
  #include "AM_Ucglib.h"
#endif
#if defined AM_PLUGINS_TFT
  #include "AM_TFT.h"
#endif


Arduino_Menu::Arduino_Menu() {
}


void Arduino_Menu::debug(){
  
}

  
  
