/*!
 * @file Arduino_Menu.h
 *
 * This is part of Arduino-Menu library for arduino based microcontrollers
 * 
 * This is a general purpose menu system that can be used to change parameters,
 * to navigate and display your settings.
 * 
 * Written by Lamba Alexandru for RS Media Software, with
 * contributions from the open source community.
 *
 * BSD license, all text above, and the splash screen header file,
 * must be included in any redistribution.
 *
 */
#ifndef _Arduino_Menu_H_
#define _Arduino_Menu_H_

#include "Arduino.h"
#include <EEPROM.h>
/*********************************************************************************************************
** Global definitions
** Description:             
*********************************************************************************************************/
#define AM_PLUGINS_SERIAL
//#define AM_PLUGINS_LIQUIDCRYSTAL
#define AM_PLUGINS_OLED_SSD1306

#define AM_ENV_STATES           4
#define AM_INPUTS               5
#define AM_INPUT_PRESS_MILLIS   200
#define AM_MENU_WIDTH           20
#define AM_MENU_LINES           2
#define AM_MENU_PLACEHOLDER     "%"
#define AM_MENU_EMPTY           "Empty"
#define AM_MENU_EDITOR_CURSOR   "_"
#define AM_MENU_EDITOR_CONFIRM  "Confirm "
#define AM_MENU_EDITOR_CANCEL   "Cancel "
#define AM_MENU_EDITOR_DELAY    2000
#define AM_MENU_EDITOR_STYLE    0 /*0 - change letter using up/down arrows, right arrow moves to the next character; 1 - Use interval in which the same letter changes.*/

#define AM_ENV_NAV              0
#define AM_ENV_TYPE_ALPHANUM    1
#define AM_ENV_TYPE_NUMERIC     2
#define AM_ENV_RANGE            3

#define AM_INPUT_NULL           0

#define AM_INPUT_NAV_UP         1
#define AM_INPUT_NAV_DOWN       2
#define AM_INPUT_NAV_ENTER      3
#define AM_INPUT_NAV_BACK       4

#define AM_INPUT_EDIT_TYPE_UP     1
#define AM_INPUT_EDIT_TYPE_DOWN   2
#define AM_INPUT_EDIT_TYPE_NEXT   3
#define AM_INPUT_EDIT_TYPE_DELETE 4
#define AM_INPUT_EDIT_CONFIRM     5

#define AM_INPUT_RANGE_UP       1
#define AM_INPUT_RANGE_DOWN     2
#define AM_INPUT_RANGE_CANCEL   3
#define AM_INPUT_RANGE_CONFIRM  4

#define AM_INPUT_TYPE_ALPHANUM  " abcdefghijklmnopqrstuvxyz0123456789."
#define AM_INPUT_TYPE_NUMERIC   "0123456789."

//define the default menu functions
#define AM_ITEM_FUNCTION_LISTITEMS            1
#define AM_ITEM_FUNCTION_BACK                 2
#define AM_ITEM_FUNCTION_SET_SINGLE_OPTION    3
#define AM_ITEM_FUNCTION_SET_MULTIPLE_OPTION  4
#define AM_ITEM_FUNCTION_SET_ALPHANUMERIC     5
#define AM_ITEM_FUNCTION_SET_NUMERIC          6
#define AM_ITEM_FUNCTION_SELECT_RANGE         7

//define the custom menu functions
#define AM_ITEM_FUNCTION_START_CYCLE          8

typedef struct {
  uint8_t action;
  uint8_t sequence; 
} Behavior;

typedef struct {  
  uint8_t id;
  Behavior beh[AM_ENV_STATES];
} Input;

typedef struct {
  uint8_t parent_id;
  char* title;
  uint8_t function;    
  char* params;
} Item;

typedef struct
{
  float v,m,M,s;
} Range;

class Arduino_Menu {
  


private:
  //environment variables
  uint8_t _env;  

  //menu navigation variables
  uint8_t _active_menu_id = 0, _current_menu_id = 0, _current_row = 0;
  uint8_t _action;
  uint8_t _total_items;

  //input variables
  uint8_t _incoming_byte=0;
  Input _inputs[AM_INPUTS];
  char _alphanumeric_buffer[AM_MENU_WIDTH];
  int8_t _alphanumeric_position=0;
  int8_t _editor_env = 0;
  uint8_t _input_pin;
  unsigned long _timer = 0;

  //output variables  
  char _output_buffer[AM_MENU_WIDTH];
  
  //EEPROM variables
  char _EEPROMbuf[AM_MENU_WIDTH];

  //range related variables
  Range _r;
  
public:
  Arduino_Menu();

/*********************************************************************************************************
**                          Setup functions
** Description:             Setup related functions
*********************************************************************************************************/
  void setup();
  void debug();
  
  #if defined AM_PLUGINS_SERIAL 
    void setupSerial(); 
  #endif
  
  #if defined AM_PLUGINS_LIQUIDCRYSTAL
    void setupLiquidCrystal(); 
  #endif

  #if defined AM_PLUGINS_OLED_SSD1306
    void setupOledSSD1306();
  #endif
/*********************************************************************************************************
**                          Input functions
** Description:             Input related functions
*********************************************************************************************************/
  void inputListen();
  void inputSetBehavior(uint8_t index, uint8_t env, uint8_t action, uint8_t sequence);
  void inputSetId(uint8_t index, uint8_t id);
  Input inputGet(uint8_t id);
  
  #if defined AM_PLUGINS_SERIAL 
    uint8_t inputListenFromSerial(); 
  #endif
  
  #if defined AM_PLUGINS_LIQUIDCRYSTAL 
    uint8_t inputListenFromKeypad();
  #endif


/*********************************************************************************************************
**                          controller functions
** Description:             controller related functions
*********************************************************************************************************/
  void controller();
  void controllerNavUpDown(int8_t direction);
  void controllerNavBack();
  void controllerNavListItems();
  
  void controllerSetSingleOption();
  void controllerSetMultipleOption();
  void controllerSelectRange();
  void controllerSetAlphaNumeric();

  void controllerEditType();
  void controllerEditTypeUp();
  void controllerEditTypeDown();
  void controllerEditCancel();
  void controllerEditTypeNext();
  void controllerEditDelete();
  void controllerEditConfirm();
  void controllerEditShowType();
  void controllerEditTypeChangeEnv(int8_t direction);
  
  void controllerEditRangeUp();
  void controllerEditRangeDown();
  void controllerEditRangeCancel();
  void controllerEditRangeConfirm();
  
/*********************************************************************************************************
**                          Output functions
** Description:             Output related functions
*********************************************************************************************************/
  void outputStart();
  void outputFinish();
  void outputPrint(String str);
  void outputPrintln(String str);
  void outputPrintItem(String title, bool selected, bool active, bool line);
  
  
  #if defined AM_PLUGINS_SERIAL 
    void outputStartToSerial();
    void outputFinishToSerial();
    void outputPrintToSerial(String str);
    void outputPrintlnToSerial(String str);
    void outputPrintItemToSerial(String title, bool selected, bool active, bool line);
  #endif

  #if defined AM_PLUGINS_LIQUIDCRYSTAL
    void outputStartToLiquidCrystal();
    void outputFinishToLiquidCrystal();
    void outputPrintToLiquidCrystal(String str);
    void outputPrintlnToLiquidCrystal(String str);
    void outputPrintItemToLiquidCrystal(String title, bool selected, bool active, bool line);
  #endif
  
  #if defined AM_PLUGINS_OLED_SSD1306
    void outputStartToOledSSD1306();
    void outputFinishToOledSSD1306();
    void outputPrintToOledSSD1306(String str);
    void outputPrintlnToOledSSD1306(String str);
    void outputPrintItemToOledSSD1306(String title, bool selected, bool active, bool line);
  #endif
  
/*********************************************************************************************************
** EEPROM functions
** Description:             The functions that manage the EEPROM memory
*********************************************************************************************************/
  void EEPROMSaveDefault();
  void EEPROMCheck();
  
/*********************************************************************************************************
* 
* 
* Menu Navigation functions
* 
* Description:             The functions used for the menu navigation
* 
* 
*********************************************************************************************************/
  void navChangeActive(int8_t direction);
  Item navGetItem(uint8_t id);
  void navSetTotalItems(uint8_t total);
  void navListItems(uint8_t parent_id);
  void navParseTitle(char title[AM_MENU_WIDTH]);
  void navShowTitle();
  uint8_t navChildrenSize(uint8_t parent_id);
  bool navCheckSelected(uint8_t id);
  bool navCheckActive(uint8_t id);
  uint8_t navGetCurrentMenuId();



/*********************************************************************************************************
* 
* 
* Range functions
* 
* Description:             Functions related to the Range environment
* 
* 
*********************************************************************************************************/
  Range rangeParse(char value[AM_MENU_WIDTH], char* query);
  void rangeShow(Range range);
  
};

extern Arduino_Menu menu;

 
#endif
