
/*********************************************************************************************************
** Input functions
*                          
** Description:             Input related functions
* 
* 
* 
*********************************************************************************************************/

/*********************************************************************************************************
** setupSerial()
** Description:             Setting up Serial
*********************************************************************************************************/
void Arduino_Menu::setupSerial(){  
  Serial.begin(115200);
}


/*********************************************************************************************************
** inputListenFromSerial()
** Description:             Listens for input from the Serial interface. If the input matches one of the
*                           inputs it is put in the _incoming_byte.
*********************************************************************************************************/
uint8_t Arduino_Menu::inputListenFromSerial(){
  uint8_t incoming = 0;
  if (Serial.available() > 0) {
    
    incoming = Serial.read();
    delay(30);
  }
  
  if(incoming!=0){
    for(uint8_t i = 0; i< sizeof _inputs / sizeof _inputs[0]; i++){
      if(incoming == _inputs[i].id)
      {
        Serial.print("found ");
        Serial.println(incoming);
        return incoming;
      }
    }    
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
** outputStartToSerial()
** Description:             When we initialize the Serial output we have to clear the screen by printing
*                           50 empty lines.
*********************************************************************************************************/
void Arduino_Menu::outputStartToSerial(){  
  for(int i=0;i<50;i++)
  {
    Serial.println();
  }
}

/*********************************************************************************************************
** outputFinishToSerial()
** Description:             Serial output set of instructions after everything is shown.
*********************************************************************************************************/  
void Arduino_Menu::outputFinishToSerial(){
  
}

/*********************************************************************************************************
** outputPrintItemToSerial(String title, bool selected, bool active)
** Description:             Print item to Serial
*********************************************************************************************************/  
void Arduino_Menu::outputPrintItemToSerial(String title, bool selected, bool active, bool line){
  if(active) Serial.print("> ");  
  Serial.print(title);
  if(selected) Serial.print("*");
  if(line) Serial.println("");
}

/*********************************************************************************************************
** outputPrintTitleToSerial(String title)
** Description:             Print title to Serial
*********************************************************************************************************/  
void Arduino_Menu::outputPrintTitleToSerial(String title){
  
  Serial.println(title);
  for(uint8_t i=0;i<AM_MENU_WIDTH;i++)
    Serial.print("-");
  Serial.println();  
}
