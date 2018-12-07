
#include "Arduino_Menu.h"
/*********************************************************************************************************
** Input functions
*                          
** Description:             Input related functions
* 
* 
* 
*********************************************************************************************************/

  /*********************************************************************************************************
  ** inputListen()
  ** Description:             The function waits for inputs from the various sources and loads the value
  *                           into _incoming_byte. If not 0, the controller() function will react to the input.
  *********************************************************************************************************/
  void Arduino_Menu::inputListen(){
    #if defined AM_PLUGINS_SERIAL
      _incoming_byte = inputListenFromSerial();
    #endif
    #if defined AM_PLUGINS_LIQUIDCRYSTAL
      if(_incoming_byte==0)
        _incoming_byte = inputListenFromKeypad();
    #endif
    
    controller();
  }
  
  /*********************************************************************************************************
  ** inputSetId()
  ** Description:             Each input should have an unique id. Based on the environment it is used in it
  *                           can perform various actions. 
  *********************************************************************************************************/
  void Arduino_Menu::inputSetId(uint8_t index, uint8_t id){
    _inputs[index].id = id;
  }
  
  /*********************************************************************************************************
  ** inputSetAction()
  ** Description:             Each input can perform various actions based on the environment used in. In
  *                           type environments the input follows a sequence of letters or numbers to make
  *                           the user type various characters. When we define our inputs we set the
  *                           behavior for each of them.
  *********************************************************************************************************/
  void Arduino_Menu::inputSetAction(uint8_t index, uint8_t env, uint8_t action){      
    _inputs[index].action[env] = action;
    
  }
  
  /*********************************************************************************************************
  ** inputGet()
  ** Description:             Return the input based on its id
  *********************************************************************************************************/
  Input Arduino_Menu::inputGet(uint8_t id){
    if(id==0) return Input {0,{0,0,0,0}};
    
    for(uint8_t i = 0; i< sizeof _inputs / sizeof _inputs[0]; i++)
      if(_inputs[i].id == id)
        return _inputs[i];

    
    return Input {0,{0,0,0,0}};
  }

  
