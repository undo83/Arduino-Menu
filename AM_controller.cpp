
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
              controllerEditShowType();    
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
          
          case AM_INPUT_EDIT_TYPE_UP:
            switch(_editor_env){
              case 0:
              default:
                controllerEditTypeUp();
              break;
              
              case 1:           
              case 2:
                controllerEditTypeChangeEnv(-1);
              break;
            }            
            controllerEditShowType();
            
          break;
          
          case AM_INPUT_EDIT_TYPE_DOWN:
            switch(_editor_env){
              case 0:
              default:
                controllerEditTypeDown();
              break;
              
              case 1:
              case 2:
                controllerEditTypeChangeEnv(1);
              break;
            }
            controllerEditShowType();
          break;  
          
          case AM_INPUT_EDIT_TYPE_NEXT:
            controllerEditTypeNext();
            controllerEditShowType();
          break;          

          //case AM_INPUT_EDIT_CANCEL:   
            //controllerEditCancel();
          //break;

          case AM_INPUT_EDIT_TYPE_DELETE:            
            controllerEditDelete();
            controllerEditShowType();
          break;

          case AM_INPUT_EDIT_CONFIRM:
            switch(_editor_env){
                case 0:
                default:
                  controllerEditTypeChangeEnv(1);
                  controllerEditShowType();
                break;
                
                case 1:
                  controllerEditConfirm();
                break;
                
                case 2:
                  controllerEditCancel();
                break;
              }
            
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
  * void controllerNavUpDown(int8_t direction)
  * Description:              Navigation Up / Down controller function that moves the _active_menu_id up or down
  *                           one position
  *********************************************************************************************************/
  void Arduino_Menu::controllerNavUpDown(int8_t direction){    
    
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
    
    _editor_env = 0;
    
  }
  /*********************************************************************************************************
  * void Arduino_Menu::controllerEditShowType()
  * Description:              Alphanumeric and Numeric type editor behavior function.
  *********************************************************************************************************/
  void Arduino_Menu::controllerEditShowType(){    
    
    navShowTitle();

    //initialize output
    outputStart(); 
  
    if(_editor_env == 0) outputPrintItem(_alphanumeric_buffer + String(AM_MENU_EDITOR_CURSOR), false, true, true);
    else outputPrintItem(_alphanumeric_buffer, false, false, true);

    if(_editor_env == 1)
      outputPrintItem(AM_MENU_EDITOR_CONFIRM, false, true, false);
    else 
      outputPrintItem(AM_MENU_EDITOR_CONFIRM, false, false, false);

    if(_editor_env == 2)
      outputPrintItem(AM_MENU_EDITOR_CANCEL, false, true, true);
    else 
      outputPrintItem(AM_MENU_EDITOR_CANCEL, false, false, true);
    
    //finish output
    outputFinish();  
  }
  /*********************************************************************************************************
  * void Arduino_Menu::controllerEditTypeUp()
  * Description:              Previous alphanumeric character
  *********************************************************************************************************/
  void Arduino_Menu::controllerEditTypeUp() {

    Serial.println(_incoming_byte);
    
    _incoming_byte = 0;
    
    _alphanumeric_position --;
    
    if(_env==AM_ENV_TYPE_ALPHANUM){          
      if(_alphanumeric_position < 0) 
        _alphanumeric_position = strlen(AM_INPUT_TYPE_ALPHANUM)-1;
    }
    
    if(_env==AM_ENV_TYPE_NUMERIC){
      if(_alphanumeric_position < 0) 
        _alphanumeric_position = strlen(AM_ENV_TYPE_NUMERIC)-1;
    }
    
    if(_env==AM_ENV_TYPE_ALPHANUM){
      _alphanumeric_buffer[strlen(_alphanumeric_buffer)-1] = AM_INPUT_TYPE_ALPHANUM[_alphanumeric_position];        
      _alphanumeric_buffer[strlen(_alphanumeric_buffer)] = 0;      
    }
    
    if(_env==AM_ENV_TYPE_NUMERIC){
      _alphanumeric_buffer[strlen(_alphanumeric_buffer)-1] = AM_INPUT_TYPE_NUMERIC[_alphanumeric_position];        
      _alphanumeric_buffer[strlen(_alphanumeric_buffer)] = 0;
    }
    
    //if(_alphanumeric_position > 0)

  }
  /*********************************************************************************************************
  * void controllerEditTypeDown()
  * Description:              Next alphanumeric character
  *********************************************************************************************************/
  void Arduino_Menu::controllerEditTypeDown() {
        
    _incoming_byte = 0;
    
    _alphanumeric_position++;
    
    if(_env==AM_ENV_TYPE_ALPHANUM){
      if(_alphanumeric_position >= strlen(AM_INPUT_TYPE_ALPHANUM)) 
        _alphanumeric_position = 0;
    }
        
    if(_env==AM_ENV_TYPE_NUMERIC){
      if(_alphanumeric_position >= strlen(AM_ENV_TYPE_NUMERIC)) 
        _alphanumeric_position = 0;
    }
    
    if(_env==AM_ENV_TYPE_ALPHANUM){
      _alphanumeric_buffer[strlen(_alphanumeric_buffer)-1] = AM_INPUT_TYPE_ALPHANUM[_alphanumeric_position];        
      _alphanumeric_buffer[strlen(_alphanumeric_buffer)] = 0;      
    }
    
    if(_env==AM_ENV_TYPE_NUMERIC){
      _alphanumeric_buffer[strlen(_alphanumeric_buffer)-1] = AM_INPUT_TYPE_NUMERIC[_alphanumeric_position];        
      _alphanumeric_buffer[strlen(_alphanumeric_buffer)] = 0;
    }
    
    

  }
  
  /*********************************************************************************************************
  * void controllerEditTypeNext()
  * Description:              Increase buffer with one character
  *********************************************************************************************************/
  void Arduino_Menu::controllerEditTypeNext(){

    if(strlen(_alphanumeric_buffer) < AM_MENU_WIDTH) {
        _alphanumeric_position = 0; 
        _alphanumeric_buffer[strlen(_alphanumeric_buffer)] = ' ';
        _alphanumeric_buffer[strlen(_alphanumeric_buffer)+1] = '\0';
    }
    //controllerEditShowType();
  }
  /*********************************************************************************************************
  * void controllerEditTypeChangeEnv(int8_t direction)
  * Description:              Alphanumeric and Numeric type editor behavior function.
  *********************************************************************************************************/
  void Arduino_Menu::controllerEditTypeChangeEnv(int8_t direction) {
    
      _incoming_byte = 0;

      _editor_env += direction;

      if(_editor_env < 0) _editor_env = 2;
      if(_editor_env > 2) _editor_env = 0;
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
    
    uint8_t last_char = strlen(_alphanumeric_buffer)-1;
    _alphanumeric_buffer[last_char] = '\0';
  }
  
  /*********************************************************************************************************
  * void Arduino_Menu::controllerEditConfirm()
  * Description:              Confirm save action for the alphanumeric editor
  *********************************************************************************************************/     
  void Arduino_Menu::controllerEditConfirm(){

    //set input back to 0
    _incoming_byte = 0;

    //_editor_env++;
    
    if(_editor_env == 1){
      
      _editor_env = 0;
    
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
