
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
  }
  if(incoming>0){
    for(uint8_t i = 0; i< sizeof _inputs / sizeof _inputs[0]; i++){
      if(incoming == _inputs[i].id)
        return incoming;
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
** outputPrintToSerial(String str)
** Description:             Serial print string
*********************************************************************************************************/  
void Arduino_Menu::outputPrintToSerial(String str){
  Serial.print(str);
}

/*********************************************************************************************************
** outputPrintlnToSerial(String str)
** Description:             Serial println string
*********************************************************************************************************/  
void Arduino_Menu::outputPrintlnToSerial(String str){
  Serial.println(str);
}

/*********************************************************************************************************
** outputPrintItemToSerial(String title, bool selected, bool active)
** Description:             Print item to Serial
*********************************************************************************************************/  
void Arduino_Menu::outputPrintItemToSerial(String title, bool selected, bool active){
  if(active) outputPrintToSerial(">");  
  outputPrintToSerial(title);    
  if(selected) outputPrintToSerial("*");
  outputPrintlnToSerial("");
}
