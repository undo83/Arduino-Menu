#include <TFT.h>
#include <SPI.h>

TFT tft = TFT(3, 5, 4);

#define TFT_LINE_HEIGHT 12



/*********************************************************************************************************
** setupUcglib()
** Description:             Setup the OLED display
*********************************************************************************************************/
void Arduino_Menu::setupTFT(){    
  tft.begin();
  
  tft.background(0,0,0);
  tft.stroke(255,255,255);
  tft.setTextSize(1);
  tft.setRotation(1);
}

/*********************************************************************************************************
** outputToOledSSD1306Start()
** Description:             Before we display new things on the OLED we clear the display and set the
*                           standard colors and set the cursor to 0.
*********************************************************************************************************/
void Arduino_Menu::outputStartToTFT(){    
    tft.background(0,0,0);
    tft.stroke(255, 255, 255);
}


/*********************************************************************************************************
** outputToOledSSD1306Finish()
** Description:             This is where we actually display all the outputs that we have generated.
*********************************************************************************************************/
void Arduino_Menu::outputFinishToTFT(){
}


/*********************************************************************************************************
** outputPrintItemToOledSSD1306(String title, bool selected, bool active)
** Description:             Print item to OLED SSD 1306
*********************************************************************************************************/  
void Arduino_Menu::outputPrintItemToTFT(String title, bool selected, bool active, bool line){
  
  char ch[AM_MENU_WIDTH];
  
    
  if(active) {
    title = "> "+title;
  }else{
    
    
  }
  //tft.text(title);
  
  if(selected) title=String(title+"*");
  title.toCharArray(ch,AM_MENU_WIDTH);
  tft.text(ch, 20, TFT_LINE_HEIGHT * (_line + 1) + 10);
    
  
  //ucg.setPrintPos(10, UCG_LINE_HEIGHT * (_line + 1));
}
