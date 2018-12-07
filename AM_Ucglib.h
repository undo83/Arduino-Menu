#include <Ucglib.h>
#include <SPI.h>

//Ucglib_ST7735_18x128x160_HWSPI ucg(/*sclk=*/ 7, /*data=*/ 6, /*cd=*/ 5 , /*cs=*/ 3, /*reset=*/ 4);
Ucglib_ST7735_18x128x160_HWSPI ucg(/*cd=*/ 5 , /*cs=*/ 3, /*reset=*/ 4);

#define UCG_LINE_HEIGHT 12



/*********************************************************************************************************
** setupUcglib()
** Description:             Setup the OLED display
*********************************************************************************************************/
void Arduino_Menu::setupUcglib(){    
  delay(1000);
  ucg.begin(UCG_FONT_MODE_SOLID);
  ucg.clearScreen();
  ucg.setRotate90();
  ucg.setFont(ucg_font_courB08_tf);
  
    ucg.setColor(0,255, 255, 255);
    ucg.setColor(1, 0, 0,0);
}

/*********************************************************************************************************
** outputToOledSSD1306Start()
** Description:             Before we display new things on the OLED we clear the display and set the
*                           standard colors and set the cursor to 0.
*********************************************************************************************************/
void Arduino_Menu::outputStartToUcglib(){    
    //ucg.setColor(0, 0, 0, 0);
    //ucg.drawBox(0,0,160,128);
    //ucg.setColor(0,255, 255, 255);
    //ucg.setColor(255, 255, 255);
    //ucg.setColor(1, 255, 0,0);
    //ucg.clearScreen();
    for(uint8_t i = 0; i < AM_MENU_LINES+2;i++)
    {
      
      ucg.setColor(0, 0, 0, 0);
      ucg.drawBox(0,UCG_LINE_HEIGHT * i+2,160, UCG_LINE_HEIGHT);
      ucg.setColor(0,255, 255, 255);
      ucg.setColor(1,0, 0, 0);
    }
    ucg.setColor(0,255, 255, 255);
    ucg.setColor(1, 0, 0,0);
    ucg.setPrintPos(10,UCG_LINE_HEIGHT);
}


/*********************************************************************************************************
** outputToOledSSD1306Finish()
** Description:             This is where we actually display all the outputs that we have generated.
*********************************************************************************************************/
void Arduino_Menu::outputFinishToUcglib(){
}


/*********************************************************************************************************
** outputPrintItemToOledSSD1306(String title, bool selected, bool active)
** Description:             Print item to OLED SSD 1306
*********************************************************************************************************/  
void Arduino_Menu::outputPrintItemToUcglib(String title, bool selected, bool active, bool line){
  

    
  if(active) {
    ucg.setColor(0, 255, 255, 255);
    ucg.drawBox(0,UCG_LINE_HEIGHT * (_line -1 )+2,160, UCG_LINE_HEIGHT);
    
    
    ucg.setColor(0,0, 0, 0);
    ucg.setColor(1,255, 255, 255);
    //outputPrintToUcglib(">");
  }else{
    ucg.setColor(0, 0, 0, 0);
    ucg.drawBox(0,UCG_LINE_HEIGHT * (_line -1 )+2,160, UCG_LINE_HEIGHT);
    ucg.setColor(0,255, 255, 255);
    ucg.setColor(1,0, 0, 0);
    
  }
  ucg.print(title);
  //Serial.println(UCG_LINE_HEIGHT * (_line -1 )+2);
  if(selected) ucg.print("*");
    
    ucg.setColor(0, 255, 255, 255);  
    ucg.setColor(1, 0, 0,0);
    //ucg.setColor(255, 255, 255);
    //ucg.setColor(1, 255, 0,0);
    
  ucg.setPrintPos(10, UCG_LINE_HEIGHT * (_line + 1));
}
/*********************************************************************************************************
** outputPrintItemToOledSSD1306(String title, bool selected, bool active)
** Description:             Print item to OLED SSD 1306
*********************************************************************************************************/  
void Arduino_Menu::outputPrintTitleToUcglib(String title){
  
  ucg.print(title);
  /*  
  if(active) {
    ucg.setColor(0, 255, 255, 255);
    ucg.drawBox(0,UCG_LINE_HEIGHT * (_line -1 )+2,160, UCG_LINE_HEIGHT);
    
    
    ucg.setColor(0,0, 0, 0);
    ucg.setColor(1,255, 255, 255);
    //outputPrintToUcglib(">");
  }else{
    ucg.setColor(0, 0, 0, 0);
    ucg.drawBox(0,UCG_LINE_HEIGHT * (_line -1 )+2,160, UCG_LINE_HEIGHT);
    ucg.setColor(0,255, 255, 255);
    ucg.setColor(1,0, 0, 0);
    
  }
  ucg.print(title);
  //Serial.println(UCG_LINE_HEIGHT * (_line -1 )+2);
  if(selected) ucg.print("*");
    
    ucg.setColor(0, 255, 255, 255);  
    ucg.setColor(1, 0, 0,0);
    //ucg.setColor(255, 255, 255);
    //ucg.setColor(1, 255, 0,0);*/
    
  ucg.setPrintPos(10, UCG_LINE_HEIGHT * (_line + 1));
}
