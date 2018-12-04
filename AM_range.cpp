
#include "Arduino_Menu.h"
/*********************************************************************************************************
 * 
** Range functions
*                          
** Description:             Range related functions
* 
* 
*********************************************************************************************************/ 
  
  
  /*********************************************************************************************************
  * rangeParse(char value[AM_MENU_WIDTH], char* query)
  * Description:              Parse a query structured like: m=1.00;M=100.00;s=1.00 where m is the minimum, 
  *                           M is the maximum and s is the step value                          
  *********************************************************************************************************/
  Range Arduino_Menu::rangeParse(char value[AM_MENU_WIDTH], char* query)
  {
    Range range;
    range.v = String(value).toFloat();
    if(String(query).indexOf("m=") != -1) range.m = String(query).substring(String(query).indexOf("m=")+2).toFloat();
    if(String(query).indexOf("M=") != -1) range.M = String(query).substring(String(query).indexOf("M=")+2).toFloat();
    if(String(query).indexOf("s=") != -1) range.s = String(query).substring(String(query).indexOf("s=")+2).toFloat();

    return range;
  }
  
  /*********************************************************************************************************
  * rangeParse(char value[AM_MENU_WIDTH], char* query)
  * Description:              Parse a query structured like: m=1.00;M=100.00;s=1.00 where m is the minimum, 
  *                           M is the maximum and s is the step value                          
  *********************************************************************************************************/
  void Arduino_Menu::rangeShow(Range range)
  {    
    float percent = 0;
    
    _env = AM_ENV_RANGE;

    navShowTitle();
    
    percent = range.v * (AM_MENU_WIDTH-2)/(range.M-range.m);
    
    for(uint8_t i=0; i<(AM_MENU_WIDTH - String(range.v).length())/2;i++)
    {
      outputPrint(" ");        
    }
    outputPrintln(String(range.v));
    
    outputPrint("[");
    
    for(uint8_t i=0;i<AM_MENU_WIDTH-2;i++)
    {
      if( i < percent )
        outputPrint("=");
      else 
        outputPrint(" ");
    }
    outputPrint("]");
  }
