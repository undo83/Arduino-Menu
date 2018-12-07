#include "Arduino_Menu.h"

/*********************************************************************************************************
 * 
** Arduino_Menu Setup 
*                          
** Description:             This is where you set up your menu items, default configuration and inputs.
* 
* 
*********************************************************************************************************/ 
void Arduino_Menu::setup(){
  
  #if defined AM_PLUGINS_SERIAL 
    setupSerial(); 
  #endif

  #if defined AM_PLUGINS_LIQUIDCRYSTAL
    setupLiquidCrystal();
  #endif

  #if defined AM_PLUGINS_OLED_SSD1306
    setupOledSSD1306();
  #endif

  #if defined AM_PLUGINS_UCGLIB
    setupUcglib();
  #endif

  #if defined AM_PLUGINS_TFT
    setupTFT();
  #endif

  EEPROMCheck();
  //EEPROMSaveDefault();
  
  /* Set default input behaviors */
  /*up*/
  inputSetId(0, 97);
  inputSetAction(0, AM_ENV_NAV, AM_INPUT_NAV_UP);
  inputSetAction(0, AM_ENV_TYPE_ALPHANUM, AM_INPUT_EDIT_TYPE_UP);
  inputSetAction(0, AM_ENV_TYPE_NUMERIC, AM_INPUT_EDIT_TYPE_UP);
  inputSetAction(0, AM_ENV_RANGE, AM_INPUT_RANGE_UP);
  
  /*down*/
  inputSetId(1, 122);
  inputSetAction(1, AM_ENV_NAV, AM_INPUT_NAV_DOWN);
  inputSetAction(1, AM_ENV_TYPE_ALPHANUM, AM_INPUT_EDIT_TYPE_DOWN);
  inputSetAction(1, AM_ENV_TYPE_NUMERIC, AM_INPUT_EDIT_TYPE_DOWN);
  inputSetAction(1, AM_ENV_RANGE, AM_INPUT_RANGE_DOWN);
  
  /*left*/
  inputSetId(2, 99);
  inputSetAction(2, AM_ENV_NAV, AM_INPUT_NAV_BACK);
  inputSetAction(2, AM_ENV_TYPE_ALPHANUM, AM_INPUT_EDIT_TYPE_DELETE);
  inputSetAction(2, AM_ENV_TYPE_NUMERIC, AM_INPUT_EDIT_TYPE_DELETE);
  inputSetAction(2, AM_ENV_RANGE, AM_INPUT_RANGE_CANCEL);
  
  /*right*/
  inputSetId(3, 114);
  inputSetAction(3, AM_ENV_NAV, AM_INPUT_NULL);
  inputSetAction(3, AM_ENV_TYPE_ALPHANUM, AM_INPUT_EDIT_TYPE_NEXT);
  inputSetAction(3, AM_ENV_TYPE_NUMERIC, AM_INPUT_EDIT_TYPE_NEXT);
  inputSetAction(3, AM_ENV_RANGE, AM_INPUT_NULL);
  
  /*select*/
  inputSetId(4, 101);
  inputSetAction(4, AM_ENV_NAV, AM_INPUT_NAV_ENTER);
  inputSetAction(4, AM_ENV_TYPE_ALPHANUM, AM_INPUT_EDIT_CONFIRM);
  inputSetAction(4, AM_ENV_TYPE_NUMERIC, AM_INPUT_EDIT_CONFIRM);
  inputSetAction(4, AM_ENV_RANGE, AM_INPUT_RANGE_CONFIRM);

  navSetTotalItems(66);
}

/*********************************************************************************************************
* navGetItem(uint8_t id)
* Description:             Returns the menu item that has this id.
*********************************************************************************************************/
Item Arduino_Menu::navGetItem(byte id){    
         
    switch(id)
    {
      case 0: default: return   {-1, "Home", AM_ITEM_FUNCTION_LISTITEMS};break;
      
      /*                    HOME                      */
      case 1: return {0, "Target points", AM_ITEM_FUNCTION_LISTITEMS};break;
      case 2: return {0, "Cycle", AM_ITEM_FUNCTION_LISTITEMS};break;
      case 3: return {0, "Settings", AM_ITEM_FUNCTION_LISTITEMS};break;
       
       
      /*         TARGET POINTS  */
      case 4: return {1, "%35%", AM_ITEM_FUNCTION_LISTITEMS};break;
      case 5: return {1, "%40%", AM_ITEM_FUNCTION_LISTITEMS};break;
      case 6: return {1, "%45%", AM_ITEM_FUNCTION_LISTITEMS};break;
      case 7: return {1, "%50%", AM_ITEM_FUNCTION_LISTITEMS};break;
      case 8: return {1, "%55%", AM_ITEM_FUNCTION_LISTITEMS};break;
      case 9: return {1, "%60%", AM_ITEM_FUNCTION_LISTITEMS};break;
      case 10: return           {1, "Back", AM_ITEM_FUNCTION_BACK};break;
       
      /*         CYCLE       */
      case 11: return {2, "Start new cycle", AM_ITEM_FUNCTION_START_CYCLE};break;
      case 12: return {2, "Start from target", AM_ITEM_FUNCTION_LISTITEMS};break;
      case 13: return {2, "Back", AM_ITEM_FUNCTION_BACK};break;
       
      /*         SETTINGS       */
      case 14: return {3, "Status", AM_ITEM_FUNCTION_LISTITEMS};break;
      case 15: return {3, "Units", AM_ITEM_FUNCTION_LISTITEMS};break;
      case 16: return {3, "At cycle end", AM_ITEM_FUNCTION_LISTITEMS};break;
      case 17: return {3, "Back", AM_ITEM_FUNCTION_BACK};break;
       
      /*         STATUS         */
       
      case 18: return {14, "Working", AM_ITEM_FUNCTION_SET_SINGLE_OPTION};break;
      case 19: return {14, "Stopped", AM_ITEM_FUNCTION_SET_SINGLE_OPTION};break;
      case 20: return {14, "Back", AM_ITEM_FUNCTION_BACK};break;
       
      /*         UNITS          */
      case 21: return {15, "Celsius", AM_ITEM_FUNCTION_SET_SINGLE_OPTION};break;
      case 22: return {15, "Fahrenheit", AM_ITEM_FUNCTION_SET_SINGLE_OPTION};break;
      case 23: return {15, "Back", AM_ITEM_FUNCTION_BACK};break;
       
      /*         CYCLE END          */
      case 24: return {16, "Stop", AM_ITEM_FUNCTION_SET_SINGLE_OPTION};break;
      case 25: return {16, "Keep last params", AM_ITEM_FUNCTION_SET_SINGLE_OPTION};break;
      case 26: return {16, "Restart", AM_ITEM_FUNCTION_SET_SINGLE_OPTION};break;
      case 27: return {16, "Back", AM_ITEM_FUNCTION_BACK};break;
       
      /*          START FROM TARGET         */
      case 28: return {12, "%35%", AM_ITEM_FUNCTION_SET_SINGLE_OPTION};break;
      case 29: return {12, "%40%", AM_ITEM_FUNCTION_SET_SINGLE_OPTION};break;
      case 30: return {12, "%45%", AM_ITEM_FUNCTION_SET_SINGLE_OPTION};break;
      case 31: return {12, "%50%", AM_ITEM_FUNCTION_SET_SINGLE_OPTION};break;
      case 32: return {12, "%55%", AM_ITEM_FUNCTION_SET_SINGLE_OPTION};break;
      case 33: return {12, "%60%", AM_ITEM_FUNCTION_SET_SINGLE_OPTION};break;
      case 34: return {12, "Back", AM_ITEM_FUNCTION_BACK};break;
      
      /*          TARGET POINT 0 */
      case 35: return {4, "Set name", AM_ITEM_FUNCTION_SET_ALPHANUMERIC};break;
      case 36: return {4, "Temp: %36% C", AM_ITEM_FUNCTION_SELECT_RANGE, "m=0.00;M=40.00;s=1.00"};break;
      case 37: return {4, "Humidity: %37%%", AM_ITEM_FUNCTION_SELECT_RANGE, "m=0.00;M=100.00;s=1.00"};break;
      case 38: return {4, "Set duration", AM_ITEM_FUNCTION_SET_NUMERIC};break;
      case 39: return {4, "Back", AM_ITEM_FUNCTION_BACK};break;
      
      /*          TARGET POINT 1 */
      case 40: return {5, "Set name", AM_ITEM_FUNCTION_SET_ALPHANUMERIC};break;
      case 41: return {5, "Temperature: %41% C", AM_ITEM_FUNCTION_SELECT_RANGE,"m=0;M=40;s=1"};break;
      case 42: return {5, "Humidity: %42%%", AM_ITEM_FUNCTION_SELECT_RANGE,"m=0;M=100;s=1"};break;
      case 43: return {5, "Set duration", AM_ITEM_FUNCTION_SET_NUMERIC};break;
      case 44: return {5, "Back", AM_ITEM_FUNCTION_BACK};break;
      
      /*          TARGET POINT 2 */
      case 45: return {6, "Set name", AM_ITEM_FUNCTION_SET_ALPHANUMERIC};break;
      case 46: return {6, "Temperature: %46% C", AM_ITEM_FUNCTION_SELECT_RANGE,"m=0;M=40;s=1"};break;
      case 47: return {6, "Humidity: %47%%", AM_ITEM_FUNCTION_SELECT_RANGE,"m=0;M=100;s=1"};break;
      case 48: return {6, "Set duration", AM_ITEM_FUNCTION_SET_NUMERIC};break;
      case 49: return {6, "Back", AM_ITEM_FUNCTION_BACK};break;
      
      /*          TARGET POINT 3 */
      case 50: return {7, "Set name", AM_ITEM_FUNCTION_SET_ALPHANUMERIC};break;
      case 51: return {7, "Temperature: %51% C", AM_ITEM_FUNCTION_SELECT_RANGE,"m=0;M=40;s=1"};break;
      case 52: return {7, "Humidity: %52%%", AM_ITEM_FUNCTION_SELECT_RANGE,"m=0;M=100;s=1"};break;
      case 53: return {7, "Set duration", AM_ITEM_FUNCTION_SET_NUMERIC};break;
      case 54: return {7, "Back", AM_ITEM_FUNCTION_BACK};break;
      
      /*           TARGET POINT 4           */
      case 55: return {8, "Set name", AM_ITEM_FUNCTION_SET_ALPHANUMERIC};break;
      case 56: return {8, "Temperature: %56% C", AM_ITEM_FUNCTION_SELECT_RANGE,"m=0;M=40;s=1"};break;
      case 57: return {8, "Humidity: %57%%", AM_ITEM_FUNCTION_SELECT_RANGE,"m=0;M=100;s=1"};break;
      case 58: return {8, "Set duration", AM_ITEM_FUNCTION_SET_NUMERIC };break;
      case 59: return {8, "Back", AM_ITEM_FUNCTION_BACK};break;
      
      /*                      TARGET POINT 5           */
      case 60: return {9, "Set name", AM_ITEM_FUNCTION_SET_ALPHANUMERIC};break;
      case 61: return {9, "Temperature: %61% C", AM_ITEM_FUNCTION_SELECT_RANGE,"m=0;M=40;s=1"};break;
      case 62: return {9, "Humidity: %62%%", AM_ITEM_FUNCTION_SELECT_RANGE,"m=0;M=100;s=1"};break;
      case 63: return {9, "Set duration", AM_ITEM_FUNCTION_SET_NUMERIC};break;
      case 64: return {9, "Back", AM_ITEM_FUNCTION_BACK};break;
      
      //additional configuration parameters
      case 65: return            {-2,"currentTime",AM_INPUT_NULL};break;

    }
      
  }

  

  /*********************************************************************************************************
  ** Function name:           EEPROMSaveDefault
  ** Description:             Saves the default menu parameters in the EEPROM memory
  *********************************************************************************************************/  
  void Arduino_Menu::EEPROMSaveDefault()
  {
      /*                      DEFAULTS              */
      EEPROM.put(0,"init");
      EEPROM.put(AM_MENU_WIDTH*18,"1");
      EEPROM.put(AM_MENU_WIDTH*21,"1");
      EEPROM.put(AM_MENU_WIDTH*25,"1");
      EEPROM.put(AM_MENU_WIDTH*28,"1");
      EEPROM.put(AM_MENU_WIDTH*35,"Fermentation");
      EEPROM.put(AM_MENU_WIDTH*36,"22");
      EEPROM.put(AM_MENU_WIDTH*37,"75");
      EEPROM.put(AM_MENU_WIDTH*38,"100");
      EEPROM.put(AM_MENU_WIDTH*40,"Curing 1");
      EEPROM.put(AM_MENU_WIDTH*41,"13");
      EEPROM.put(AM_MENU_WIDTH*42,"80");
      EEPROM.put(AM_MENU_WIDTH*43,"100");
      EEPROM.put(AM_MENU_WIDTH*45,"Curing 2");
      EEPROM.put(AM_MENU_WIDTH*46,"15");
      EEPROM.put(AM_MENU_WIDTH*47,"75");
      EEPROM.put(AM_MENU_WIDTH*48,"24");    
  }
