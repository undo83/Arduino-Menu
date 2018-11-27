int env = 0;


#define CONFIG_MENU_LINES 3
#define CONFIG_MENU_WIDTH 20

#define CONFIG_MENU_EMPTY "Empty"

#define CONFIG_MENU_EDITOR_CURSOR "_"
#define CONFIG_MENU_EDITOR_CONFIRM "(e) Confirm "
#define CONFIG_MENU_EDITOR_CANCEL  "(c) Cancel "
#define CONFIG_MENU_EDITOR_DELAY 2000 //time between pressing the same key

typedef struct
{
  float v,m,M,s;
} Range;

typedef  struct {
    byte parent_id;
    char* title;
    char* function;    
    char* params;
} Item;

typedef struct {
   short pin;
   char* alphanumeric;
} Input;

const Item items[]= 
{
   
/* 0*/    {-1, "Home", "listItems"},
/*                    HOME                      */
/* 1*/    {0, "Target points", "listItems"},
/* 2*/    {0, "Cycle", "listItems"},
/* 3*/    {0, "Settings", "listItems"},
 
 
/*                    TARGET POINTS             */
/* 4*/    {1, "%35%", "listItems"},
/* 5*/    {1, "%40%", "listItems"},
/* 6*/    {1, "%45%", "listItems"},
/* 7*/    {1, "%50%", "listItems"},
/* 8*/    {1, "%55%", "listItems"},
/* 9*/    {1, "%60%", "listItems"},
/*10*/    {1, "Back", "back"},
 
/*                    CYCLE                  */
/*11*/    {2, "Start new cycle", "startCycle"},
/*12*/    {2, "Start from target", "listItems"},
/*13*/    {2, "Back", "back"},
 
/*                    SETTINGS                  */
/*14*/    {3, "Status", "listItems"},
/*15*/    {3, "Units", "listItems"},
/*16*/    {3, "At cycle end", "listItems"},
/*17*/    {3, "Back", "back"},
 
/*                    STATUS                    */
 
/*18*/    {14, "Working", "setSingleOption"},
/*19*/    {14, "Stopped", "setSingleOption"},
/*20*/    {14, "Back", "back"},
 
/*                    UNITS                     */
/*21*/    {15, "Celsius", "setSingleOption"},
/*22*/    {15, "Fahrenheit", "setSingleOption"},
/*23*/    {15, "Back", "back"},
 
/*                    CYCLE END                     */
/*24*/    {16, "Stop", "setSingleOption"},
/*25*/    {16, "Keep last params", "setSingleOption"},
/*26*/    {16, "Restart", "setSingleOption"},
/*27*/    {16, "Back", "back"},
 
/*                     START FROM TARGET         */
/*28*/    {12, "%35%", "setSingleOption"},
/*29*/    {12, "%40%", "setSingleOption"},
/*30*/    {12, "%45%", "setSingleOption"},
/*31*/    {12, "%50%", "setSingleOption"},
/*32*/    {12, "%55%", "setSingleOption"},
/*33*/    {12, "%60%", "setSingleOption"},
/*34*/    {12, "Back", "back"},
/*                      TARGET POINT 0           */
/*35*/    {4, "Set name", "setAlphaNumeric"},
/*36*/    {4, "Temp: %36%ºC", "selectRange", "m=0.00;M=40.00;s=1.00"},
/*37*/    {4, "Humidity: %37%%", "selectRange", "m=0.00;M=100.00;s=1.00"},
/*38*/    {4, "Set duration", "setNumeric"},
/*39*/    {4, "Back", "back"},

/*                      TARGET POINT 1           */
/*40*/    {5, "Set name", "setAlphaNumeric"},
/*41*/    {5, "Temperature: %41%ºC", "selectRange","m=0;M=40;s=1"},
/*42*/    {5, "Humidity: %42%%", "selectRange","m=0;M=100;s=1"},
/*43*/    {5, "Set duration", "setNumeric"},
/*44*/    {5, "Back", "back"},

/*                      TARGET POINT 2           */
/*45*/    {6, "Set name", "setAlphaNumeric"},
/*46*/    {6, "Temperature: %46%ºC", "selectRange","m=0;M=40;s=1"},
/*47*/    {6, "Humidity: %47%%", "selectRange","m=0;M=100;s=1"},
/*48*/    {6, "Set duration", "setNumeric"},
/*49*/    {6, "Back", "back"},

/*                      TARGET POINT 3           */
/*50*/    {7, "Set name", "setAlphaNumeric"},
/*51*/    {7, "Temperature: %51%ºC", "selectRange","m=0;M=40;s=1"},
/*52*/    {7, "Humidity: %52%%", "selectRange","m=0;M=100;s=1"},
/*53*/    {7, "Set duration", "setNumeric"},
/*54*/    {7, "Back", "back"},

/*                      TARGET POINT 4           */
/*55*/    {8, "Set name", "setAlphaNumeric"},
/*56*/    {8, "Temperature: %56%ºC", "selectRange","m=0;M=40;s=1"},
/*57*/    {8, "Humidity: %57%%", "selectRange","m=0;M=100;s=1"},
/*58*/    {8, "Set duration", "setNumeric" },
/*59*/    {8, "Back", "back"},

/*                      TARGET POINT 5           */
/*60*/    {9, "Set name", "setAlphaNumeric"},
/*61*/    {9, "Temperature: %61%ºC", "selectRange","m=0;M=40;s=1"},
/*62*/    {9, "Humidity: %62%%", "selectRange","m=0;M=100;s=1"},
/*63*/    {9, "Set duration", "setNumeric"},
/*64*/    {9, "Back", "back"},

//additional configuration parameters
          {-2,"currentTime","","0"},
};






const Input inputs[] = 
{
/* 1 */  {49," 1"},
/* 2 */  {50,"abcABC2"},  
/* 3 */  {51,"defDEF3"},
/* 4 */  {52,"ghiGHI4"},
/* 5 */  {53,"jklJKL5"},
/* 6 */  {54,"mnoMNO6"},
/* 7 */  {55,"pqrsPQRS7"},
/* 8 */  {56,"tuvTUV8"},
/* 9 */  {57,"wxyzWXYZ9"},
/* 0 */  {48,".,0"},
/* a */  {97,},         //UP
/* z */  {122,},        //DOWN  
/* x */  {120,""},
/* c */  {99,},
/* e */  {101,}
};
