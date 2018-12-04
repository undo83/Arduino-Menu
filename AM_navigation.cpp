
#include "Arduino_Menu.h"
/*********************************************************************************************************
* 
*                          Navigation functions
*                          
* Description:             The functions responsable for menu navigation
* 
* 
*********************************************************************************************************/

  /*********************************************************************************************************
  * navChangeActive(uint8_t direction)
  * Description:             Changes the _active_menu_id variable to the next item that has the same 
  *                          parent_id based on the direction(1 or -1).
  *********************************************************************************************************/
  void Arduino_Menu::navChangeActive(uint8_t direction){
    _active_menu_id = _active_menu_id + direction;
      
    if(_active_menu_id <= 0) _active_menu_id = _total_items-1;
    if(_active_menu_id >= _total_items) _active_menu_id = 0;
  
    if(navGetItem(_active_menu_id).parent_id != _current_menu_id)
      navChangeActive(direction);
  }

  /*********************************************************************************************************
  * navSetTotalItems(uint8_t total)
  * Description:             Sets the maximum number of menu items
  *********************************************************************************************************/
  void Arduino_Menu::navSetTotalItems(uint8_t total){
    _total_items = total;
  }

  /*********************************************************************************************************
  * navParseTitle(char title[AM_MENU_WIDTH])
  * Description:             Shows the menu title
  *********************************************************************************************************/
  void Arduino_Menu::navParseTitle(char title[AM_MENU_WIDTH]){
    String s;
    char buf[AM_MENU_WIDTH];
    char value[16];
    
    s = String(title);
    
    for(uint8_t i=0;i<_total_items;i++)
    {
        buf[0] = 0;
        itoa(i, value, 10);
        strcpy(buf,AM_MENU_PLACEHOLDER);
        strcat(buf,value);
        strcat(buf,AM_MENU_PLACEHOLDER);

        if(s.indexOf(buf)>=0)
        {
          EEPROM.get(i * AM_MENU_WIDTH,_EEPROMbuf);          
          s.replace(buf, _EEPROMbuf);
        }        
    }
    
    if(s.length() == 0) s = AM_MENU_EMPTY;

    
    for(byte j=0;j < AM_MENU_WIDTH; j++)
      _output_buffer[j] = s[j];    
  }

  /*********************************************************************************************************
  * navShowTitle()
  * Description:             Shows the menu title
  *********************************************************************************************************/
  void Arduino_Menu::navShowTitle(){
    
    navParseTitle(navGetItem(_current_menu_id).title);
    
    outputPrintln(_output_buffer);
    
    for(uint8_t i=0;i<AM_MENU_WIDTH;i++)
      outputPrint("-");
      
    outputPrintln("");
  }

  /*********************************************************************************************************
  * navChildrenSize(uint8_t parent_id)
  * Description:             returns the number of children for a parent_id
  *********************************************************************************************************/
  uint8_t Arduino_Menu::navChildrenSize(uint8_t parent_id)
  {
    uint8_t j = 0;
    for(uint8_t i=0;i<_total_items;i++){
      if(navGetItem(i).parent_id == parent_id){
          j++;
      }      
    }
    return j;
  }
  
  /*********************************************************************************************************
  * navCheckSelected(uint8_t id)
  * Description:             returns true if an item is selected
  *********************************************************************************************************/
  bool Arduino_Menu::navCheckSelected(uint8_t id)
  {
    EEPROM.get(id*AM_MENU_WIDTH,_EEPROMbuf);
    if(atoi(_EEPROMbuf) == 1) return true;
    else return false;
  } 
  
  /*********************************************************************************************************
  * navCheckActive(uint8_t id)
  * Description:             returns true if an item is active
  *********************************************************************************************************/
  bool Arduino_Menu::navCheckActive(uint8_t id)
  {
    if(id == _active_menu_id) return true;
    else return false;
  } 
  
  /*********************************************************************************************************
  * navGetCurrentMenuId()
  * Description:             returns the _current_menu_id
  *********************************************************************************************************/
  uint8_t Arduino_Menu::navGetCurrentMenuId()
  {
    return _current_menu_id;
  } 
   
  /*********************************************************************************************************
  * navListItems(uint8_t parent_id)
  * Description:             List the menu items of a parent_id
  *********************************************************************************************************/
  void Arduino_Menu::navListItems(uint8_t parent_id){

    navShowTitle();
    
    uint8_t children_items[navChildrenSize(parent_id)];

    //build children_items array
    uint8_t j = 0;
    uint8_t active_index = 0;
    
    for(uint8_t i=0;i<_total_items;i++){
      if(navGetItem(i).parent_id == parent_id){
        
        if(_active_menu_id == i) active_index = j;
        
        children_items[j] = i;
        j++;
      }
    }

   uint8_t current_page = floor(active_index/AM_MENU_LINES);
   _current_row = 0;
    for(uint8_t i = current_page * AM_MENU_LINES; i < AM_MENU_LINES * (current_page+1); i++)
    {
      if(sizeof children_items / sizeof children_items[0] > i)
      {
        navParseTitle(navGetItem(children_items[i]).title);
        outputPrintItem(_output_buffer, navCheckSelected(children_items[i]), navCheckActive(children_items[i]));
        _current_row++;
      }
    }
    
  }
