#include "Arduino.h"
#include "Arduino_Menu.h";

Arduino_Menu menu;

void setup() {

  menu.setup();
    
  //change navigation pointer
  menu.navChangeActive(1);
  
  //initialize output
  menu.outputStart();
    
  //list menu items
  menu.navListItems(menu.navGetCurrentMenuId());
    
  //finish output
  menu.outputFinish();
}

void loop() {

  menu.inputListen();
  
  
  
  

  delay(100);
}
