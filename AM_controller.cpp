
#include "Arduino_Menu.h"
/*********************************************************************************************************
* 
*                          Controller functions
*                          
* Description:             The functions that control the way the menu answers to the user input.
* 
* 
*********************************************************************************************************/

  

  /*********************************************************************************************************
  ** void controller()
  ** Description:             controller related functions
  *********************************************************************************************************/
  void Arduino_Menu::controller(){

    switch (_env)
    {
      /*                    AM_ENV_NAV            */
      case AM_ENV_NAV:
      default:
        switch(inputGet(_incoming_byte).beh[_env].action)
        {
          /*                    CANCEL            */
          case AM_INPUT_NAV_BACK:
              controllerNavBack();
          break;
          
          /*                    UP ARROW            */
          case AM_INPUT_NAV_UP:
              controllerNavUpDown(-1);
          break;
          /*                    DOWN ARROW            */
          case AM_INPUT_NAV_DOWN:
              controllerNavUpDown(1);
          break;

          /*                    ENTER            */
          case AM_INPUT_NAV_ENTER:
          
              /*                    LIST ITEMS            */
            if(navGetItem(_active_menu_id).function == AM_ITEM_FUNCTION_LISTITEMS){
              controllerNavListItems();
            }
            
            /*                    BACK            */
            else if(navGetItem(_active_menu_id).function == AM_ITEM_FUNCTION_BACK){
              controllerNavBack();
            }
            
              /*                    SET SINGLE OPTION            */
            else if(navGetItem(_active_menu_id).function == AM_ITEM_FUNCTION_SET_SINGLE_OPTION){
              controllerSetSingleOption();
            }
              /*                    SET MULTIPLE OPTION            */
            else if(navGetItem(_active_menu_id).function == AM_ITEM_FUNCTION_SET_MULTIPLE_OPTION){
              controllerSetMultipleOption();
            }
              /*                    SELECT RANGE            */
            else if(navGetItem(_active_menu_id).function == AM_ITEM_FUNCTION_SELECT_RANGE){
              controllerSelectRange();
            }
              /*                    SET_ALPHANUMERIC / NUMERIC          */
            else if(navGetItem(_active_menu_id).function == AM_ITEM_FUNCTION_SET_ALPHANUMERIC || navGetItem(_active_menu_id).function == AM_ITEM_FUNCTION_SET_NUMERIC){
              controllerSetAlphaNumeric();              
            }            
          break;
    
          default:
            _incoming_byte = 0;
          break;
        }
      break;
      /*                    AM_ENV_TYPE_ALPHANUM            */
      /*                    AM_ENV_TYPE_NUMERIC            */
      case AM_ENV_TYPE_ALPHANUM:
      case AM_ENV_TYPE_NUMERIC:
        
        switch(inputGet(_incoming_byte).beh[_env].action){
          case AM_INPUT_EDIT_TYPE:            
            controllerEditType();
          break;

          case AM_INPUT_EDIT_CANCEL:   
            controllerEditCancel();
          break;

          case AM_INPUT_EDIT_DELETE:            
            controllerEditDelete();
          break;

          case AM_INPUT_EDIT_CONFIRM:
            controllerEditConfirm();
          break;
                    
          default:
            _incoming_byte = 0;
          break;
        }
      break;
      
      /*                    AM_ENV_RANGE            */
      case AM_ENV_RANGE:
        switch(inputGet(_incoming_byte).beh[_env].action){
          case AM_INPUT_RANGE_UP:            
            controllerEditRangeUp();
          break;
          
          case AM_INPUT_RANGE_DOWN:            
            controllerEditRangeDown();
          break;
          
          case AM_INPUT_RANGE_CANCEL:            
            controllerEditRangeCancel();
          break;
          
          case AM_INPUT_RANGE_CONFIRM:            
            controllerEditRangeConfirm();
          break;
          
          default:
            _incoming_byte = 0;
          break;
        }
      break;
      
      
    }
  }

  
  /*********************************************************************************************************
  * void controllerNavUpDown(uint8_t direction)
  * Description:              Navigation Up / Down controller function that moves the _active_menu_id up or down
  *                           one position
  *********************************************************************************************************/
  void Arduino_Menu::controllerNavUpDown(uint8_t direction){    
    
    //change navigation pointer
    navChangeActive(direction);

    //initialize output
    outputStart();

    //list menu items
    navListItems(_current_menu_id);

    //finish output
    outputFinish();
  }

  /*********************************************************************************************************
  * void Arduino_Menu::controllerNavListItems()
  * Description:              List menu items function. Used also for the "back" functionality.
  *********************************************************************************************************/
  void Arduino_Menu::controllerNavListItems(){
          
     //set input back to 0
    _incoming_byte = 0;
    
    _current_menu_id = _active_menu_id;
        
    _active_menu_id = 0;
    
    //change navigation pointer
    navChangeActive(1);
    
    //initialize output
    outputStart();
    
    //list menu items
    navListItems(_current_menu_id);
    
    //finish output
    outputFinish();
  }
  /*********************************************************************************************************
  * void Arduino_Menu::controllerNavBack()
  * Description:              Go up one level.
  *********************************************************************************************************/
  void Arduino_Menu::controllerNavBack(){
          
     //set input back to 0
    _incoming_byte = 0;

    if(navGetItem(_current_menu_id).parent_id >= 0) {
      _current_menu_id = navGetItem(_current_menu_id).parent_id;
        
      _active_menu_id = 0;
      
      //change navigation pointer
      navChangeActive(1);
    }
    
    //initialize output
    outputStart();
    
    //list menu items
    navListItems(_current_menu_id);
    
    //finish output
    outputFinish();
  }

  /*********************************************************************************************************
  * void controllerSetSingleOption()
  * Description:              Set single option behavior function.
  *********************************************************************************************************/
  void Arduino_Menu::controllerSetSingleOption(){
          
     //set input back to 0
    _incoming_byte = 0;
    
    //all the options with the same parent_id get 0, the selected one gets 1
    for(uint8_t i=0; i< _total_items;i++)  {
      if(navGetItem(i).parent_id == navGetItem(_active_menu_id).parent_id && i != _active_menu_id)
        EEPROM.put(AM_MENU_WIDTH * i, '0');
      
      if(i == _active_menu_id)
        EEPROM.put(AM_MENU_WIDTH * i, '1');
    }

    _current_menu_id = navGetItem(_active_menu_id).parent_id;

    //initialize output
    outputStart();
    
    //list menu items
    navListItems(_current_menu_id);
    
    //finish output
    outputFinish();  
  }

  /*********************************************************************************************************
  * void controllerSetMultipleOption()
  * Description:              Set multiple option behavior function.
  *********************************************************************************************************/
  void Arduino_Menu::controllerSetMultipleOption(){ 
          
     //set input back to 0
    _incoming_byte = 0;
       
    EEPROM.get(_active_menu_id * AM_MENU_WIDTH, _EEPROMbuf);
    if(_EEPROMbuf[0] != '1')
      EEPROM.put(AM_MENU_WIDTH * _active_menu_id, '1');
    else
      EEPROM.put(AM_MENU_WIDTH * _active_menu_id, '0');
  
    _current_menu_id = navGetItem(_active_menu_id).parent_id;
  
    //initialize output
    outputStart();
    
    //list menu items
    navListItems(_current_menu_id);
    
    //finish output
    outputFinish();  
  }

  /*********************************************************************************************************
  * void controllerSelectRange()
  * Description:              Select Range behavior function.
  *********************************************************************************************************/
  void Arduino_Menu::controllerSelectRange(){
          
     //set input back to 0
    _incoming_byte = 0;
    
    _current_menu_id = _active_menu_id;

    EEPROM.get(_active_menu_id * AM_MENU_WIDTH, _EEPROMbuf);
    
    _r = rangeParse(_EEPROMbuf, navGetItem(_active_menu_id).params);
    
    //initialize output
    outputStart();    

    //display the range screen
    rangeShow(_r);
    
    //finish output
    outputFinish();  
  }
  
  /*********************************************************************************************************
  * void controllerSetAlphaNumeric()
  * Description:              Alphanumeric and Numeric type editor behavior function.
  *********************************************************************************************************/
  void Arduino_Menu::controllerSetAlphaNumeric(){
          
     //set input back to 0
    _incoming_byte = 0;
    
    //set the environment to alphanumeric type
    if( navGetItem(_active_menu_id).function == AM_ITEM_FUNCTION_SET_ALPHANUMERIC)
      _env = AM_ENV_TYPE_ALPHANUM;
    else
      _env = AM_ENV_TYPE_NUMERIC;
      

    //load the value from the EEPROM
    EEPROM.get(_active_menu_id * AM_MENU_WIDTH, _EEPROMbuf);

    
    navParseTitle(_EEPROMbuf);
    
    for(byte i=0;i<AM_MENU_WIDTH;i++)
      _alphanumeric_buffer[i] = _output_buffer[i];

    navShowTitle();

    //initialize output
    outputStart(); 
  
    outputPrint(_alphanumeric_buffer);
    outputPrintln(AM_MENU_EDITOR_CURSOR);
    
    outputPrint(AM_MENU_EDITOR_CONFIRM);
    outputPrintln(AM_MENU_EDITOR_CANCEL);
    
    //finish output
    outputFinish();  
  }
  
  /*********************************************************************************************************
  * void controllerEditType()
  * Description:              Alphanumeric and Numeric type editor behavior function.
  *********************************************************************************************************/
  void Arduino_Menu::controllerEditType()
  {    
    uint8_t last_char = strlen(_alphanumeric_buffer);
    
    if(last_char < AM_MENU_WIDTH) {
      //if we repeat the last input
      if(_incoming_byte != _input_pin){                       
        _alphanumeric_position = 0; 
        _alphanumeric_buffer[last_char] = ' ';
        _alphanumeric_buffer[last_char+1] = '\0';
      }
      else {
        if(millis() - _timer > AM_MENU_EDITOR_DELAY)
        {            
          _alphanumeric_position = 0; 
          _alphanumeric_buffer[last_char] = ' ';
          _alphanumeric_buffer[last_char+1] = '\0';
        }
        _timer = millis();
      }
      _input_pin = _incoming_byte;

         
      //set input back to 0
      _incoming_byte = 0;
      
      //alphanumeric
      if(_env==AM_ENV_TYPE_ALPHANUM)
      { 
        char * ch;
        if(last_char < AM_MENU_WIDTH){
        switch(inputGet(_input_pin).beh[_env].sequence){
          case 0: default: ch = AM_INPUT_TYPE_0;break;
          case 1: ch = AM_INPUT_TYPE_1;break;
          case 2: ch = AM_INPUT_TYPE_1;break;
          case 3: ch = AM_INPUT_TYPE_1;break;
          case 4: ch = AM_INPUT_TYPE_1;break;          
        }

        if(_alphanumeric_position >= strlen(ch))
          _alphanumeric_position = 0;

        _alphanumeric_buffer[last_char-1] = ch[_alphanumeric_position];        
        _alphanumeric_buffer[last_char] = 0;
            
        _alphanumeric_position++;
        }
      }
      //numeric
      if(_env==AM_ENV_TYPE_NUMERIC)
      {
        char * ch;
        if(last_char < AM_MENU_WIDTH)
        {
          
          switch(inputGet(_input_pin).beh[_env].sequence){
            case 0: default: ch = AM_INPUT_TYPE_0;break;
            case 1: ch = AM_INPUT_TYPE_1;break;
            case 2: ch = AM_INPUT_TYPE_1;break;
            case 3: ch = AM_INPUT_TYPE_1;break;
            case 4: ch = AM_INPUT_TYPE_1;break;          
          }
          //find the used input            
          if(_alphanumeric_position>strlen(ch)) {
            _alphanumeric_position = 0;
          }
    
              
          uint8_t cycle = 0;
          while(String(ch[_alphanumeric_position]).toInt()==0 && ch[_alphanumeric_position] != '0' && cycle < 2)
          {
            _alphanumeric_position++;
            if(_alphanumeric_position>strlen(ch))
            {
              _alphanumeric_position = 0;
              cycle++;
            }
          }

          if(ch[_alphanumeric_position] == '0' || String(ch[_alphanumeric_position]).toInt()!=0)
          {
            if(_alphanumeric_buffer[last_char-1]==ch[_alphanumeric_position])
            {
              _alphanumeric_buffer[last_char] = ch[_alphanumeric_position];
              _alphanumeric_buffer[last_char+1] = '\0';
            }
            else
            {
              _alphanumeric_buffer[last_char-1] = ch[_alphanumeric_position];        
              _alphanumeric_buffer[last_char] = '\0';
            }
          }
        }
      }
    }
    else
      _incoming_byte = 0;

    

    navShowTitle();

    //initialize output
    outputStart(); 
  
    outputPrint(_alphanumeric_buffer);
    outputPrintln(AM_MENU_EDITOR_CURSOR);
    
    outputPrint(AM_MENU_EDITOR_CONFIRM);
    outputPrintln(AM_MENU_EDITOR_CANCEL);
    
    //finish output
    outputFinish();  
  }
  
  /*********************************************************************************************************
  * void controllerEditCancel()
  * Description:              Cancel action for the alphanumeric editor
  *********************************************************************************************************/     
  void Arduino_Menu::controllerEditCancel(){

    //set input back to 0
    _incoming_byte = 0;

    //set environment back to navigation
    _env = AM_ENV_NAV;
    
    //initialize output
    outputStart();
    
    //list menu items
    navListItems(navGetItem(_active_menu_id).parent_id);
    
    //finish output
    outputFinish();
  }
  
  /*********************************************************************************************************
  * void controllerEditDelete()
  * Description:              Delete action for the alphanumeric editor
  *********************************************************************************************************/        
  void Arduino_Menu::controllerEditDelete(){

    //set input back to 0
    _incoming_byte = 0;
    
    byte last_char = strlen(_alphanumeric_buffer)-1;
    _alphanumeric_buffer[last_char] = '\0';
       
    //initialize output
    outputStart();   
    
    //show menu title
    navShowTitle();
  
    outputPrint(_alphanumeric_buffer);
    outputPrintln(AM_MENU_EDITOR_CURSOR);
    
    outputPrint(AM_MENU_EDITOR_CONFIRM);
    outputPrintln(AM_MENU_EDITOR_CANCEL);
    
    //finish output
    outputFinish();
  }
  
  /*********************************************************************************************************
  * void controllerEditConfirm()
  * Description:              Confirm save action for the alphanumeric editor
  *********************************************************************************************************/     
  void Arduino_Menu::controllerEditConfirm(){

    //set input back to 0
    _incoming_byte = 0;

    //save the value to the EEPROM memory
    EEPROM.put(AM_MENU_WIDTH * _active_menu_id, _alphanumeric_buffer);

    //set the buffer back to null
    _alphanumeric_buffer[0] = 0;
    
    //set environment back to navigation
    _env = AM_ENV_NAV;
    
    //initialize output
    outputStart();
    
    //list menu items
    navListItems(navGetItem(_active_menu_id).parent_id);
    
    //finish output
    outputFinish();
  }
            
  /*********************************************************************************************************
  * void controllerEditRangeUp()
  * Description:              Increase range value for the range editor.
  *********************************************************************************************************/        
  void Arduino_Menu::controllerEditRangeUp(){
    
    //set input back to 0
    _incoming_byte = 0;
    
    _current_menu_id = _active_menu_id;
    
    //initialize output
    outputStart();

    //when range value reaches maximum, it takes the max value, otherwise increases with step
    if( _r.v + _r.s <= _r.M) _r.v += _r.s;
    else
      _r.v = _r.M;

    //display the range screen
    rangeShow(_r);
    
    //finish output
    outputFinish();
  }
            
  /*********************************************************************************************************
  * void controllerEditRangeDown()
  * Description:              Decrease range value for the range editor.
  *********************************************************************************************************/        
  void Arduino_Menu::controllerEditRangeDown(){
    
    //set input back to 0
    _incoming_byte = 0;
    
    _current_menu_id = _active_menu_id;
    
    //initialize output
    outputStart();

    //when range value reaches minimum, it takes the min value, otherwise decreases with step
    if( _r.v - _r.s >= _r.m) _r.v -= _r.s;
    else
      _r.v = _r.m;

    //display the range screen
    rangeShow(_r);
    
    //finish output
    outputFinish();    
  }
            
  /*********************************************************************************************************
  * void controllerEditRangeCancel()
  * Description:              Cancel action for the range editor.
  *********************************************************************************************************/        
  void Arduino_Menu::controllerEditRangeCancel(){
    
    //set input back to 0
    _incoming_byte = 0;    
    
    //set environment back to navigation
    _env = AM_ENV_NAV;

    _current_menu_id = navGetItem(_active_menu_id).parent_id;
    
    //initialize output
    outputStart();
    
    //list menu items
    navListItems(_current_menu_id);
    
    //finish output
    outputFinish();
  }
            
  /*********************************************************************************************************
  * void controllerEditRangeConfirm()
  * Description:              Confirm action for the range editor
  *********************************************************************************************************/        
  void Arduino_Menu::controllerEditRangeConfirm(){
    
    //set input back to 0
    _incoming_byte = 0;    
    
    //set environment back to navigation
    _env = AM_ENV_NAV;

    //set current menu id
    _current_menu_id = navGetItem(_active_menu_id).parent_id;
    
    char buffloat[AM_MENU_WIDTH];
    String(_r.v).toCharArray(buffloat,AM_MENU_WIDTH);

    //save the new range value to the EEPROM memory
    EEPROM.put(AM_MENU_WIDTH * _active_menu_id, buffloat);
    
    //initialize output
    outputStart();
    
    //list menu items
    navListItems(_current_menu_id);
    
    //finish output
    outputFinish();
  }
