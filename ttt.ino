/*
 * Ideea e sa ai la fiecare meniu o valoare. Toate aceste valori vor fi stocate in EEPROM pe langa alte valori globale gen current_temp, current 
 * rh s.a.m.d.
 * meniurile care nu au nicio valoare vor stoca 0 pentru a mentine pozitia ca sa stii de unde citesti de exemplu [32]...
 * environmentul este dat de un switch
 * valorile default din meniu vor fi salvate direct intr-un array in eeprom fara a mai incarca array-ul meniului.
 *
switch(function)
{
  case "back":
  case "listItems":
    env = 0;
  break;

  case "changeTPName0":
    env = 1;
  break;
}


*/
 
#include <EEPROM.h>
#include "globals.h";
#include "output.h";
#include "input.h";
#include "setup.h";
#include "menu.h";



int temperature = 0;
 /* environment:  0 - children menu items display; 
                  1 - list points;
                  2 - change range;
                  3 - integer input;
                  4 - alphanumeric input;
                  */

void setup() {

  output.setup();
  //Config my_config = menu.returnDefaultConfig();
  
  
  menu.configLoad();
  //menu.configSaveDefault();
  //globals.saveConfig();
  //globals.loadConfig();
/*
  for(int i=0;i<sizeof target_points / sizeof target_points[0];i++)
  {
    output.println(target_points[i].title);
  }
*/

  menu.setCurrentMenuId(0);
  menu.setSelectedMenuId(0);
  menu.listChildren(menu.current_menu_id);
}

void loop() {

 // temperature = random(100);
  //sprintf(items[2].title,"%s %i","Temperature:",temperature);

  //items[2].title[sizeof(items[2].title)] = '\0';
  
  //menu.changeSelection(1);
  //menu.listChildren(menu.current_menu_id);
/*
  input.listen();
  menu.menuAnswer();
*/
  delay(100);
}
