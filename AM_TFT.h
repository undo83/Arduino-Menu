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
    //tft.background(0,0,0);
      //tft.fill(0,0,0);
      //tft.rect(10, TFT_LINE_HEIGHT * 2 + 7, 138, TFT_LINE_HEIGHT*10);
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
    //title = "> "+title;
    //tft.background(0,0,0);
    tft.stroke(255, 255, 255);
    tft.rect(6, TFT_LINE_HEIGHT * (_line ) + 7, 148, TFT_LINE_HEIGHT);
  }else{
      
    //tft.background(0,0,0);
    tft.stroke(0, 0, 0);
    tft.fill(0,0,0);
    tft.rect(6, TFT_LINE_HEIGHT * (_line ) + 7, 148, TFT_LINE_HEIGHT);
    tft.stroke(255, 255, 255);
  }
  //tft.text(title);
  
  if(selected) title=String(title+" *");
  title.toCharArray(ch,AM_MENU_WIDTH);
  tft.text(ch, 15, TFT_LINE_HEIGHT * (_line ) + 10);
    
  }
/*********************************************************************************************************
** outputPrintTitleToTFT(String title)
** Description:             Print title to TFT
*********************************************************************************************************/  
void Arduino_Menu::outputPrintTitleToTFT(String title){
  
  tft.stroke(0, 0, 0);
  tft.fill(0,0,0);
  tft.rect(6, 10, 148, TFT_LINE_HEIGHT);

  tft.stroke(255, 255, 255);
  tft.rect(0, TFT_LINE_HEIGHT * 2 , 160, 1);
    
  char ch[AM_MENU_WIDTH];
  
  title.toCharArray(ch,AM_MENU_WIDTH);
  tft.text(ch, 10, 10);
  tft.setTextSize(1);
}
/*********************************************************************************************************
** outputPrintProgressToTFT(float value, float max)
** Description:             Print title to TFT
*********************************************************************************************************/  
void Arduino_Menu::outputPrintProgressToTFT(float value, float max){
  
  tft.stroke(0, 0, 0);
  tft.fill(0,0,0);
  tft.rect(6, TFT_LINE_HEIGHT * 4, 148, TFT_LINE_HEIGHT*2);

  float percent;
  percent = value * 160/max;

  tft.stroke(255, 255, 255);
  tft.fill(0,0,0);
  tft.rect(6, TFT_LINE_HEIGHT * 6 , 148, TFT_LINE_HEIGHT * 2);
  
  tft.fill(255,255,255);
  tft.rect(6, TFT_LINE_HEIGHT * 6 , percent, TFT_LINE_HEIGHT * 2);
    
  char ch[AM_MENU_WIDTH];
  
  String(value).toCharArray(ch,AM_MENU_WIDTH);
  tft.setTextSize(2);
  tft.text(ch, 10, TFT_LINE_HEIGHT * 4);
  tft.setTextSize(1);
}


/*********************************************************************************************************
** outputPrintProgressToTFT(float value, float max)
** Description:             Print title to TFT
*********************************************************************************************************/  
void Arduino_Menu::outputClearToTFT(){
  tft.background(0,0,0);  
}
