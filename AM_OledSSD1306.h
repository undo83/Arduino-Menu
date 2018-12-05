#include <SPI.h>
#include <Wire.h>

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>


// OLED display TWI address
#define OLED_ADDR   0x3C
#define OLED_RESET  -1 // Reset pin # (or -1 if sharing Arduino reset pin)

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// reset pin not used on 4-pin OLED module
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// 128 x 64 pixel display
#if (SSD1306_LCDHEIGHT != 64)
  #error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

/*********************************************************************************************************
** setupOledSSD1306()
** Description:             Setup the OLED display
*********************************************************************************************************/
void Arduino_Menu::setupOledSSD1306(){    
   //SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever    
  }
    
  outputStartToOledSSD1306();
  outputPrintlnToOledSSD1306("Initializing...");  
  outputFinishToOledSSD1306();
}

/*********************************************************************************************************
** outputToOledSSD1306Start()
** Description:             Before we display new things on the OLED we clear the display and set the
*                           standard colors and set the cursor to 0.
*********************************************************************************************************/
void Arduino_Menu::outputStartToOledSSD1306(){
    display.clearDisplay();
    display.setTextColor(WHITE,BLACK);
    display.setTextSize(1);
    display.setCursor(0,0);
}


/*********************************************************************************************************
** outputToOledSSD1306Finish()
** Description:             This is where we actually display all the outputs that we have generated.
*********************************************************************************************************/
void Arduino_Menu::outputFinishToOledSSD1306(){
  display.display();
}

/*********************************************************************************************************
** outputPrintToSerial(String str)
** Description:             Print string to OLED SSD 1306
*********************************************************************************************************/  
void Arduino_Menu::outputPrintToOledSSD1306(String str){
  display.print(str);
}

/*********************************************************************************************************
** outputPrintlnToSerial(String str)
** Description:            Println string to OLED SSD 1306
*********************************************************************************************************/  
void Arduino_Menu::outputPrintlnToOledSSD1306(String str){
  display.println(str);
}

/*********************************************************************************************************
** outputPrintItemToOledSSD1306(String title, bool selected, bool active)
** Description:             Print item to OLED SSD 1306
*********************************************************************************************************/  
void Arduino_Menu::outputPrintItemToOledSSD1306(String title, bool selected, bool active, bool line){
  if(active) display.setTextColor(BLACK,WHITE);
  outputPrintToOledSSD1306(title);    
  if(selected) outputPrintToOledSSD1306("*");
  display.setTextColor(WHITE,BLACK);
  if(line) outputPrintlnToOledSSD1306("");
}
