int env = 0;
int temp = 0;
int rh = 0;


// Tell it where to store your config data in EEPROM
#define CONFIG_EEPROM 1
#define CONFIG_EEPROM_START 32

#define CONFIG_MENU_LINES 3
#define CONFIG_MENU_WIDTH 20

#define CONFIG_MENU_EMPTY "Empty"

#define CONFIG_MENU_EDITOR_CURSOR "_"
#define CONFIG_MENU_EDITOR_CONFIRM "(e) Confirm "
#define CONFIG_MENU_EDITOR_CANCEL  "(c) Cancel "


typedef  struct {
    byte parent_id;
    char* title;
    char* function;
    char* value;
} Item;


const Item items[]= 
{
  
/* 0*/    {-1, "Home", "listItems","init"},
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

/*18*/    {14, "Working", "changeSettingsStatus", "1"},
/*19*/    {14, "Stopped", "changeSettingsStatus"},
/*20*/    {14, "Back", "back"},

/*                    UNITS                     */
/*21*/    {15, "Celsius", "changeSettingsUnits", "1"},
/*22*/    {15, "Fahrenheit", "changeSettingsUnits"},
/*23*/    {15, "Back", "back"},

/*                    CYCLE END                     */
/*24*/    {16, "Stop", "changeSettingsCycleEnd"},
/*25*/    {16, "Keep last params", "changeSettingsCycleEnd", "1"},
/*26*/    {16, "Restart", "changeSettingsCycleEnd"},
/*27*/    {16, "Back", "back"},

/*                     START FROM TARGET         */
/*28*/    {12, "%35%", "changeCycleStartFrom"},
/*29*/    {12, "%40%", "changeCycleStartFrom"},
/*30*/    {12, "%45%", "changeCycleStartFrom"},
/*31*/    {12, "%50%", "changeCycleStartFrom"},
/*32*/    {12, "%55%", "changeCycleStartFrom"},
/*33*/    {12, "%60%", "changeCycleStartFrom"},
/*34*/    {12, "Back", "back"},

/*                      TARGET POINT 0           */
/*35*/    {4, "Set name", "changeTPName", "Fermentation"},
/*36*/    {4, "Set temperature", "changeTPT0", "22"},
/*37*/    {4, "Set RH", "editTPRH", "75"},
/*38*/    {4, "Set duration", "editTPDuration", "100"},
/*39*/    {4, "Back", "back"},

/*                      TARGET POINT 1           */
/*40*/    {5, "Set name", "changeTPName", "Curing 1"},
/*41*/    {5, "Set temperature", "changeTPT2", "13"},
/*42*/    {5, "Set RH", "editTPRH", "80"},
/*43*/    {5, "Set duration", "editTPDuration", "40"},
/*44*/    {5, "Back", "back"},

/*                      TARGET POINT 2           */
/*45*/    {6, "Set name", "changeTPName", "Curing 2"},
/*46*/    {6, "Set temperature", "changeTPT", "12"},
/*47*/    {6, "Set RH", "editTPRH", "75"},
/*48*/    {6, "Set duration", "editTPDuration", "24"},
/*49*/    {6, "Back", "back"},

/*                      TARGET POINT 3           */
/*50*/    {7, "Set name", "changeTPName"},
/*51*/    {7, "Set temperature", "changeTPT"},
/*52*/    {7, "Set RH", "editTPRH"},
/*53*/    {7, "Set duration", "editTPDuration"},
/*54*/    {7, "Back", "back"},

/*                      TARGET POINT 4           */
/*55*/    {8, "Set name", "changeTPName"},
/*56*/    {8, "Set temperature", "changeTPT"},
/*57*/    {8, "Set RH", "editTPRH"},
/*58*/    {8, "Set duration", "editTPDuration"},
/*59*/    {8, "Back", "back"},
/*                      TARGET POINT 5           */
/*60*/    {9, "Set name", "changeTPName"},
/*61*/    {9, "Set temperature", "changeTPT"},
/*62*/    {9, "Set RH", "editTPRH"},
/*63*/    {9, "Set duration", "editTPDuration"},
/*64*/    {9, "Back", "back"},



};
//const byte MENU_SIZE = sizeof items / sizeof items[0];



typedef struct {
   short pin;
   char* alphanumeric;
} Input;


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


typedef  struct {
    byte temperature;
    byte rh;
    int duration; //hours
    char title[CONFIG_MENU_WIDTH];
} Target_Point;


typedef struct
{
  short options[10];
} Multiple;
/*
typedef struct
{
  byte init;
  
  short settings_units;  
  short settings_cycle;
  short cycle_start_from;
  short current_temp;  
  short current_rh;
  short current_moment;
  short status; 
  
  short single_selection_settings[4];
  short short_values_settings[3];
  //short single[7];        //single menu options selected
  //Multiple multiple[10];  //multiple menu options selected
 // short environment[3];   //environment short variables
  
  
  Target_Point tp[6];
  
} Config;*/

typedef struct
{
  char* value;
} Config;

/*

typedef struct {
   int on_time;
   bool on_value_change;
   int on_button_trigger[12];
} setup_refresh;

typedef struct {
   int click;
   int confirmation;
   int homing;
} setup_buttons;


typedef struct {
    char* font;
    int length;
    byte color;
    byte background;
    char* style;
    char* algin;
} setup_tag_properties;



typedef struct {
    int lines;
    int line_length;
    setup_refresh refresh;
    setup_buttons buttons;
    setup_tag_properties tag_properties_normal;
    setup_tag_properties tag_properties_selected;
} menu_setup;


const menu_setup my_setup = 
{
  4,
  20,
  {1000, true, {0,1,2,3,4,5}},                          //Refresh
  {300, 1, 60},                                         //Buttons
  {'Arial', 4, 0xFFFF, 0x0000, 'flat', 'left'},          //Tag Properties - Normal
  {"Arial", 4, 0x0000, 0xFFFF, "flat", "left"}          //Tag Properties - Selected
};
*/
/*
void evalFunction()
{
  
  if(strcmp(pages[current_line_position].function, "showMenuHome") == 0)
  {
    current_page = 0;
    current_line_position = 0;
    changeCurrentLinePosition(1);
    showMenu();
  
  }
  else if(strcmp(pages[current_line_position].function, "showMenuTargetPoints") == 0)
  {
    current_page = 1;
    current_line_position = 0;
    changeCurrentLinePosition(1);
    showMenu();
  }
  else if(strcmp(pages[current_line_position].function, "showMenuCycle") == 0)
  {
    current_page = 17;
    current_line_position = 0;
    changeCurrentLinePosition(1);
    showMenu();
  }
  else if(strcmp(pages[current_line_position].function, "showMenuSettings") == 0)
  {
    current_page = 21;
    current_line_position = 0;
    changeCurrentLinePosition(1);
    showMenu();
  }
  else if(strcmp(pages[current_line_position].function, "editTargetPoint") == 0)
  {
    current_page = 2;
    current_line_position = 0;
    changeCurrentLinePosition(1);
    showMenu();
  }
  else if(strcmp(pages[current_line_position].function, "listTargetPoints") == 0)
  {
    current_page = 13;    
    //current_tp_line_position = 0;
    //changeCurrentTP(1);
    //listTargetPoints();
  }
  else if(strcmp(pages[current_line_position].function, "changeTemperature") == 0)
  {
    env = 1;
    //changePage();
    current_page = 5;
    changeRange(0,40,temperature);
  }
}

void listTargetPoints()
{
  showTitle();

  for(int i=0;i<(sizeof target_points/sizeof target_points[0]);i++)
  {
    Serial.println(target_points[i].name);
  }
}

void changeCurrentLinePosition(int direction)
{
  int number_of_total_lines = sizeof pages / sizeof pages[0];
  current_line_position = current_line_position + direction;
  
  if(current_line_position < 0) current_line_position = number_of_total_lines-1;
  if(current_line_position >= number_of_total_lines) current_line_position = 0;


    if(pages[current_line_position].parent_id != current_page)
    {
      changeCurrentLinePosition(direction);
    }


  
}
*/
/*
void showMenu()
{
  temperature_label = "Temperature: ";// + String(temperature);

  for(int i=0; i<20;i++)
  {
    Serial.println("");
  }

  showTitle();
  
  int sz = sizeof pages / sizeof pages[0];
  for(int i=0; i<sz; i++)
  {
    if(i == current_line_position)
      Serial.print(">");
    
    if(pages[i].parent_id == current_page)
    {
      Serial.println(pages[i].title);
    }
  }

}
*/
/*
void showTitle()
{
  //show title
  Serial.println(pages[current_page].title);
  Serial.println("----------------");
}
*/


/*
void changeRange(int min, int max, int &variable)
{
  String s;
//  showTitle();
  if(incomingByte==97) //up (a)
  {
    variable=variable+1;
  }
  if(incomingByte==122) //down (z)
  {
    variable=variable-1;
  }
   
  //incomingByte = 0;
  
  if(variable<min) variable = min;
  if(variable>max) variable = max;
  
  Serial.println(variable);
  s = "[";
  for(int i=0;i<my_setup.line_length-2;i++)
  {
    if(i<floor((my_setup.line_length-2)*variable/(max-min)))
      s+="-";
    else
      s+=" ";
  }
  s+="]";
  Serial.println(s);
}
*/
/*

void parseInput()
{
    
  // send data only when you receive data:
  if (Serial.available() > 0) {
    
    // read the incoming byte:
    incomingByte = Serial.read();
    //each button perform different actions based on the environment defined
    //menu navigation
    if(env == 0)
    {
      if(incomingByte==97) //up (a)
        {
        changeCurrentLinePosition(-1);
          showMenu();
          //evalFunction();
        }
        if(incomingByte==122)//DOWN (z)
        {
           changeCurrentLinePosition(1);
            //evalFunction();
           showMenu();
        }
        if(incomingByte==101)//enter (e)
        {
           evalFunction();
        }
    }
    
    //on change range
    else if(env == 1)
    {
        if(incomingByte==97) //up (a)
        {
         // changeValue(temperature,temperature+1);
          //changeCurrentLinePosition(-1);
          //showMenu();
          evalFunction();
        }
        if(incomingByte==122)//DOWN (z)
        {
           // changeValue(temperature,temperature-1);
           //changeCurrentLinePosition(1);
            //evalFunction();
           //showMenu();
           evalFunction();
        }
        
        if(incomingByte==101)//enter (e)
        {
          current_page = pages[current_line_position].parent_id;
          current_line_position = 0;
          changeCurrentLinePosition(1);
          env = 0;
          showMenu();
        }
    }

    incomingByte = 0;
   
  }
  delay(200);
}
*/
