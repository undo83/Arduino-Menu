
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
  ** inputSetBehavior()
  ** Description:             Each input can perform various actions based on the environment used in. In
  *                           type environments the input follows a sequence of letters or numbers to make
  *                           the user type various characters. When we define our inputs we set the
  *                           behavior for each of them.
  *********************************************************************************************************/
  void Arduino_Menu::inputSetBehavior(uint8_t index, uint8_t env, uint8_t action, uint8_t sequence){      
    _inputs[index].beh[env].action = action;
    _inputs[index].beh[env].sequence = sequence;
  }
  
  /*********************************************************************************************************
  ** inputGet()
  ** Description:             Return the input based on its id
  *********************************************************************************************************/
  Input Arduino_Menu::inputGet(uint8_t id){
    for(uint8_t i = 0; i< sizeof _inputs / sizeof _inputs[0]; i++)
      if(_inputs[i].id == id)
        return _inputs[i];

    Input temp;
    return temp;    
  }

  
