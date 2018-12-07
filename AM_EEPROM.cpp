
#include "Arduino_Menu.h"
/*********************************************************************************************************
* 
* EEPROM functions
* 
* 
* Description:             The functions that manage the EEPROM memory
* 
* 
*********************************************************************************************************/

  /*********************************************************************************************************
  ** void EEPROMCheck()
  ** Description:             Checks if the EEPROM memory is written, otherwise writes the defaults.
  *********************************************************************************************************/
  void Arduino_Menu::EEPROMCheck()
  {    
    EEPROM.get(0, _EEPROMbuf);
    if(strcmp(_EEPROMbuf, "init") != 0)
    { 
      
      EEPROMSaveDefault();      
    }    
  }
  
  /*********************************************************************************************************
  ** Function name:           EEPROMSaveDefault
  ** Description:             Saves the default menu parameters in the EEPROM memory
  *  Moved to AM_setup.h to make it easier for the users to set things up
  *********************************************************************************************************/  
  
