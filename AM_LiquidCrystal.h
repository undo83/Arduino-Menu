#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void Arduino_Menu::setupLiquidCrystal(){
  lcd.begin(16, 2);    
  lcd.home();
}

uint8_t Arduino_Menu::inputListenFromKeypad(){
  short adc_key_in  = 0;
  
  if(millis() - _timer > AM_INPUT_PRESS_MILLIS)
  {            
      _timer = millis();
      adc_key_in = analogRead(0);      // read the value from the sensor 

     if (adc_key_in > 1000) return 0; // We make this the 1st option for speed reasons since it will be the most likely result

     if (adc_key_in < 50)   return 114; //right  
     if (adc_key_in < 150)  return 97;  //up
     if (adc_key_in < 300)  return 122; //down
     if (adc_key_in < 450)  return 99; //cancel/left
     if (adc_key_in < 700)  return 101;  //enter/select
  } 
  return 0;
}
/*********************************************************************************************************
 * 
** Output functions
*                          
** Description:             Output related functions
* 
* 
*********************************************************************************************************/

/*********************************************************************************************************
** outputStartToLiquidCrystal()
** Description:             When we initialize the Serial output we have to clear the screen by printing
*                           50 empty lines.
*********************************************************************************************************/
void Arduino_Menu::outputStartToLiquidCrystal(){  
    lcd.clear();
    lcd.home();
}

/*********************************************************************************************************
** outputFinishToLiquidCrystal()
** Description:             Serial output set of instructions after everything is shown.
*********************************************************************************************************/  
void Arduino_Menu::outputFinishToLiquidCrystal(){  
}

/*********************************************************************************************************
** outputPrintItemToLiquidCrystal(String title, bool selected, bool active)
** Description:             Print item to Serial
*********************************************************************************************************/  
void Arduino_Menu::outputPrintItemToLiquidCrystal(String title, bool selected, bool active, bool line){
  if(active) lcd.print(">");  
  lcd.print(title);    
  if(selected) lcd.print("*");
  if(line) 
    lcd.setCursor(0,_line);
}
