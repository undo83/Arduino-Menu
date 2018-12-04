
#include "Arduino_Menu.h"
/*********************************************************************************************************
 * 
** Output functions
*                          
** Description:             Output related functions
* 
* 
*********************************************************************************************************/

  /*********************************************************************************************************
  ** outputStart()
  ** Description:             Each time new things have to be displayed we have to prepare the various
  *                           outputs.
  *********************************************************************************************************/
  void Arduino_Menu::outputStart(){
    #if defined AM_PLUGINS_SERIAL
      outputStartToSerial();
    #endif
    
    #if defined AM_PLUGINS_LIQUIDCRYSTAL
      outputStartToLiquidCrystal();
    #endif
  
    #if defined AM_PLUGINS_OLED_SSD1306
      outputStartToOledSSD1306();
    #endif
  }

  /*********************************************************************************************************
  ** outputFinish()
  ** Description:             Some outputs require actions to be performed at the end.
  *********************************************************************************************************/
  void Arduino_Menu::outputFinish(){
    #if defined AM_PLUGINS_SERIAL
      outputFinishToSerial();
    #endif
    
    #if defined AM_PLUGINS_LIQUIDCRYSTAL
      outputFinishToLiquidCrystal();
    #endif
  
    #if defined AM_PLUGINS_OLED_SSD1306
      outputFinishToOledSSD1306();
    #endif
  }


  /*********************************************************************************************************
  ** outputPrint()
  ** Description:             Some outputs require actions to be performed at the end.
  *********************************************************************************************************/
  void Arduino_Menu::outputPrint(String str)
  {    
    #if defined AM_PLUGINS_SERIAL
      outputPrintToSerial(str);
    #endif
    
    #if defined AM_PLUGINS_LIQUIDCRYSTAL
      outputPrintToLiquidCrystal(str);
    #endif
  
    #if defined AM_PLUGINS_OLED_SSD1306
      outputPrintToOledSSD1306(str);
    #endif
  }
  
  /*********************************************************************************************************
  ** outputPrintln()
  ** Description:             Some outputs require actions to be performed at the end.
  *********************************************************************************************************/
  void Arduino_Menu::outputPrintln(String str)
  {
    
    #if defined AM_PLUGINS_SERIAL
      outputPrintlnToSerial(str);
    #endif
    
    #if defined AM_PLUGINS_LIQUIDCRYSTAL
      outputPrintlnToLiquidCrystal(str);
    #endif
  
    #if defined AM_PLUGINS_OLED_SSD1306
      outputPrintlnToOledSSD1306(str);
    #endif
  }

  /*********************************************************************************************************
  ** outputPrintItem(String title, bool selected, bool active)
  ** Description:             Some outputs require actions to be performed at the end.
  *********************************************************************************************************/
  void Arduino_Menu::outputPrintItem(String title, bool selected, bool active){
    
    #if defined AM_PLUGINS_SERIAL
      outputPrintItemToSerial(title, selected, active);
    #endif
    
    #if defined AM_PLUGINS_LIQUIDCRYSTAL
      outputPrintItemToLiquidCrystal(title, selected, active);
    #endif
  
    #if defined AM_PLUGINS_OLED_SSD1306
      outputPrintItemToOledSSD1306(title, selected, active);
    #endif
  }
