
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
    
    _line = 1;
    
    #if defined AM_PLUGINS_SERIAL
      outputStartToSerial();
    #endif
    
    #if defined AM_PLUGINS_LIQUIDCRYSTAL
      outputStartToLiquidCrystal();
    #endif
  
    #if defined AM_PLUGINS_OLED_SSD1306
      outputStartToOledSSD1306();
    #endif
  
    #if defined AM_PLUGINS_UCGLIB
      outputStartToUcglib();
    #endif
  
    #if defined AM_PLUGINS_TFT
      outputStartToTFT();
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
  
    #if defined AM_PLUGINS_UCGLIB
      outputFinishToUcglib();
    #endif
  
    #if defined AM_PLUGINS_TFT
      outputFinishToTFT();
    #endif
  }


  /*********************************************************************************************************
  ** outputPrintItem(String title, bool selected, bool active)
  ** Description:             Some outputs require actions to be performed at the end.
  *********************************************************************************************************/
  void Arduino_Menu::outputPrintItem(String title, bool selected, bool active, bool line){
    
    #if defined AM_PLUGINS_SERIAL
      outputPrintItemToSerial(title, selected, active, line);
    #endif
    
    #if defined AM_PLUGINS_LIQUIDCRYSTAL
      outputPrintItemToLiquidCrystal(title, selected, active, line);
    #endif
  
    #if defined AM_PLUGINS_OLED_SSD1306
      outputPrintItemToOledSSD1306(title, selected, active, line);
    #endif
  
    #if defined AM_PLUGINS_UCGLIB
      outputPrintItemToUcglib(title, selected, active, line);
    #endif
  
    #if defined AM_PLUGINS_TFT
      outputPrintItemToTFT(title, selected, active, line);
    #endif

    if(line) _line++;
  }
