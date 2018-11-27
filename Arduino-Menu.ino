#include <EEPROM.h>
#include "globals.h";
#include "output.h";
#include "input.h";
#include "menu.h";


void setup() {
  output.setup();
  
  menu.EEPROMCheck();
  //menu.EEPROMSaveDefault();

  menu.setCurrentMenuId(0);
  menu.setSelectedMenuId(0);
  menu.listItems(menu.current_menu_id);
}

void loop() {

  input.listen();
  menu.menuAnswer();

  delay(100);
}
