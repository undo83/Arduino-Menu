
class Menu {


private:


  
  bool checkSelected(byte id)
  {

    if(atoi(my_config[id].value) == 1) return true;
    else return false;
    /*
    for(byte i = 0; i< sizeof my_config.single_selection_settings / sizeof my_config.single_selection_settings[0];i++)
    {
       if(my_config.single_selection_settings[i] == id)
        return true;
    }
    
    return false;
    */
  }
  
  byte returnChildrenSize(byte parent_id)
  {
    byte j = 0;
    for(byte i=0;i<sizeof items/sizeof items[0];i++)
    {
      if(items[i].parent_id == parent_id)
      {
          j++;
      }      
    }
    return j;
  }
  
public:

  byte current_menu_id = 0;
  byte active_menu_id = 0;
  byte current_page = 0;
  
  byte total = 0;
  byte active = 0;

  char alphanumeric_buffer[CONFIG_MENU_WIDTH];
  byte input_pin = 0;
  byte input_alphanumeric_position = 0;
  //float input_range = 0;
  
  char dest[CONFIG_MENU_WIDTH];
  
  unsigned long timer = 0;//millis();
  
  Config my_config[sizeof items/sizeof items[0]];


  void configLoad() {
    //populate my_config with whatever we find in eeprom
    this->configReturn();
    
    //if we don't have init as the first value, we populate the eeprom with default values
    if(my_config[0].value != "init")
    {
      this->configSaveDefault();
    }
  }
  
  void configSaveDefault()
  {
    
    configReturnDefault();
    
    //write default config to eeprom
    configSave();
    
  }

  void configSave() { 
    //write config to eeprom
    for (unsigned int t=0; t<sizeof(my_config); t++)
    {
      EEPROM.write(CONFIG_EEPROM_START + t, *((char*)&my_config + t));
    }
  }


  void configReturn()
  {
    for (unsigned int t=0; t<sizeof(my_config); t++)
        *((char*)&my_config + t) = EEPROM.read(CONFIG_EEPROM_START + t);    
  }

  void configReturnDefault()
  {
    for(byte i=0;i<sizeof items/sizeof items[0];i++)
    {
      my_config[i].value = items[i].value;
    }
  }

  void eepromFlash()
  { 
    for (int i = 0 ; i < EEPROM.length() ; i++) {
      EEPROM.write(i, 0);
    }
  }
  
  void setCurrentMenuId(byte menu_id)
  {
    current_menu_id = menu_id;
    return;
  }

  
  void setSelectedMenuId(byte menu_id)
  {
    active_menu_id = menu_id;
    this->changeSelection(1);
    return;
  }

  
  void listChildren(byte parent_id)
  {
    //Set environment to children list
    env = 0;

    this->showTitle();

    total = this->returnChildrenSize(parent_id);

    byte n_items = this->returnChildrenSize(parent_id);
    
    byte children_items[n_items];

    //build children_items array
    byte j = 0;
    byte active_index = 0;
    for(byte i=0;i<sizeof items/sizeof items[0];i++)
    {
      if(items[i].parent_id == parent_id)
      {
        
        if(active_menu_id == i) active_index = j;
        
        //if it's a placeholder parse it, otherwise load it into the children array
        
        children_items[j] = i;
        j++;

        
      }
      
    }

   
    current_page = floor(active_index/CONFIG_MENU_LINES);
    for(byte i = current_page * CONFIG_MENU_LINES; i < CONFIG_MENU_LINES * (current_page+1); i++)
    {
      if(sizeof children_items / sizeof children_items[0] > i)
      {
        this->parseTitle(items[children_items[i]].title);
        if(children_items[i] == active_menu_id)
        {
          output.printActiveLine(dest, this->checkSelected(children_items[i]));
        }
        else
        {
          output.printNormalLine(dest, this->checkSelected(children_items[i]));
        }
      }
    }
  }


  void showTitle()
  {
    this->parseTitle(items[current_menu_id].title);
    output.println(dest);
    for(byte i=0;i<CONFIG_MENU_WIDTH;i++)
      output.print("-");
    output.println("");  
  }


  void parseTitle(char title[CONFIG_MENU_WIDTH])
  {
    String s;
    char buf[CONFIG_MENU_WIDTH];
    const char *placeholder = "%";
    const char value[16];
    
    s = String(title);
        
    for(byte i=0;i<sizeof items/sizeof items[0];i++)
    {

        buf[0] = 0;
        itoa(i, value, 10);
        strcpy(buf,placeholder);
        strcat(buf,value);
        strcat(buf,placeholder);

        if(items[i].function == "selectRange")
        {
          
          if(String(my_config[i].value).indexOf("v=")!=-1)
          {
            //String();
            s.replace(buf, String(String(my_config[i].value).substring(String(my_config[i].value).indexOf("v=")+2).toFloat()));
          }
          
        }
        else
          s.replace(buf, my_config[i].value);
    }
    
    if(s.length() == 0) s = CONFIG_MENU_EMPTY;

    
    //if(s.indexOf("v=")!=-1)

    
    for(byte j=0;j < CONFIG_MENU_WIDTH; j++)
      dest[j] = s[j];      
  }
  
  void changeSelection(byte direction)
  {
    byte n_items = sizeof items / sizeof items[0];
    
    active_menu_id=active_menu_id+direction;
    

    if(active_menu_id < 0) active_menu_id = n_items-1;
    if(active_menu_id >= n_items) active_menu_id = 0;
  
    if(items[active_menu_id].parent_id != current_menu_id)
    {
      this->changeSelection(direction);
    }
  }


  void menuAnswer()
  {
    if(input.action == "menu.changeSelectionDown")
    {
        
      input.action = "";
      this->changeSelection(1);
      
      output.clearScreen();
      
      this->listChildren(this->current_menu_id);
    }
    
    if(input.action == "menu.changeSelectionUp")
    {
        input.action = "";
        this->changeSelection(-1);

        output.clearScreen();
        
        this->listChildren(this->current_menu_id);
    }
    
    
    if(input.action == "menu.enter")
    {
        input.action = "";

        if(strcmp(items[this->active_menu_id].function, "listItems") == 0)
        {            
          this->current_menu_id = this->active_menu_id;
          this->active_menu_id = 0;
          this->changeSelection(1);
          
          output.clearScreen();
          
          this->listChildren(this->current_menu_id);        
        }        
        else if(strcmp(items[this->active_menu_id].function, "back") == 0)
        {            
          this->current_menu_id = items[this->current_menu_id].parent_id;
          this->active_menu_id = 0;
          this->changeSelection(1);

          output.clearScreen();
          
          this->listChildren(this->current_menu_id);        
        }
        else if(strcmp(items[this->active_menu_id].function, "setSingleOption") == 0)
        {                 
          for(byte i=0; i< sizeof items/sizeof items[0];i++)
          {
            //all the options with the same parent_id get 0, the selected one gets 1
            if(items[i].parent_id == items[this->active_menu_id].parent_id && i != this->active_menu_id)
            {
              my_config[i].value = 0;
            }

            if(i == this->active_menu_id)
              my_config[i].value = "1";
              
          }
          
          this->configSave();

          this->current_menu_id = items[this->active_menu_id].parent_id;

          output.clearScreen();
          
          this->listChildren(this->current_menu_id); 
        }
        else if(strcmp(items[this->active_menu_id].function, "setMultipleOption") == 0)
        {
          if(my_config[this->active_menu_id].value == 0)
            my_config[this->active_menu_id].value = "1";
          else
            my_config[this->active_menu_id].value = 0;
          
          this->configSave();

          this->current_menu_id = items[this->active_menu_id].parent_id;

          output.clearScreen();
          
          this->listChildren(this->current_menu_id); 
        }
        else if(strcmp(items[this->active_menu_id].function, "selectRange") == 0)
        {
          this->current_menu_id = this->active_menu_id;
          
          float v,m,M,s = 0;
          //int percent;
  
          if(String(my_config[this->active_menu_id].value).indexOf("v=") != -1) v = String(my_config[this->active_menu_id].value).substring(String(my_config[this->active_menu_id].value).indexOf("v=")+2).toFloat();
          if(String(my_config[this->active_menu_id].value).indexOf("m=") != -1) m = String(my_config[this->active_menu_id].value).substring(String(my_config[this->active_menu_id].value).indexOf("m=")+2).toFloat();
          if(String(my_config[this->active_menu_id].value).indexOf("M=") != -1) M = String(my_config[this->active_menu_id].value).substring(String(my_config[this->active_menu_id].value).indexOf("M=")+2).toFloat();
          if(String(my_config[this->active_menu_id].value).indexOf("s=") != -1) s = String(my_config[this->active_menu_id].value).substring(String(my_config[this->active_menu_id].value).indexOf("s=")+2).toFloat();


          output.clearScreen();

          input.range_value = v;
          
          this->showRange(v,m,M,s);

        }
        else if(strcmp(items[this->active_menu_id].function, "setAlphaNumeric") == 0)
        {            
          output.clearScreen();
          this->parseTitle(my_config[this->active_menu_id].value);
          for(byte i=0;i<CONFIG_MENU_WIDTH;i++)
           this->alphanumeric_buffer[i] = dest[i];

          env = 1; 
          this->changeAlphanumeric();    
        }
        else if(strcmp(items[this->active_menu_id].function, "setNumeric") == 0)
        {            
          output.clearScreen();
          this->parseTitle(my_config[this->active_menu_id].value);
          for(byte i=0;i<CONFIG_MENU_WIDTH;i++)
           this->alphanumeric_buffer[i] = my_config[this->active_menu_id].value[i];
           
          env = 2;
          this->changeAlphanumeric();    
        }
    }
    
    if(input.action == "menu.editor.delete")
    {
      input.action = "";
      output.clearScreen();

      
      byte lastChar = strlen(this->alphanumeric_buffer)-1;
      this->alphanumeric_buffer[lastChar] = '\0'; //replace it with a NULL
      
      this->changeAlphanumeric();
    }
    
    if(input.action == "menu.editor.confirm")
    {
      input.action = "";
      
      this->saveAlphanumericBufferToMyConfig();
          
      this->configSave();
      env = 0;

      //input.action = "menu.enter";
      output.clearScreen();
      this->listChildren(items[this->active_menu_id].parent_id); 
    }
    
    if(input.action == "menu.editor.cancel")
    {
      input.action = "";
      this->alphanumeric_buffer[0] = 0;
      env = 0;

      output.clearScreen();
      this->listChildren(items[this->active_menu_id].parent_id); 
    }
    if(input.action == "menu.editor.type")
    {
      input.action = "";
      output.clearScreen();
      
      byte lastChar = strlen(this->alphanumeric_buffer);
      if(lastChar < CONFIG_MENU_WIDTH)
      {
        
        //if we repeat the last button
        if(input.incomingByte != input_pin)
        {
                 
          input_alphanumeric_position = 0; 
          this->alphanumeric_buffer[lastChar] = ' ';
          this->alphanumeric_buffer[lastChar+1] = '\0';
        }
        else
        {
          if(millis() - timer > CONFIG_MENU_EDITOR_DELAY)
          {            
            input_alphanumeric_position = 0; 
            this->alphanumeric_buffer[lastChar] = ' ';
            this->alphanumeric_buffer[lastChar+1] = '\0';
          }
          timer = millis();
        }
        input_pin = input.incomingByte;  
        //alphanumeric
        if(env==1)
        { 
          this->typeNextAlphanumericCharacter();
        }
        //numeric
        if(env==2)
        {
          this->typeNextNumericCharacter();
        }
      }
      
      this->changeAlphanumeric();
      
    }

    
    if(input.action == "menu.range.up")
    {
      this->current_menu_id = this->active_menu_id;
        
      float m,M,s = 0;

      //if(String(my_config[this->active_menu_id].value).indexOf("v=") != -1) v = String(my_config[this->active_menu_id].value).substring(String(my_config[this->active_menu_id].value).indexOf("v=")+2).toFloat();
      if(String(my_config[this->active_menu_id].value).indexOf("m=") != -1) m = String(my_config[this->active_menu_id].value).substring(String(my_config[this->active_menu_id].value).indexOf("m=")+2).toFloat();
      if(String(my_config[this->active_menu_id].value).indexOf("M=") != -1) M = String(my_config[this->active_menu_id].value).substring(String(my_config[this->active_menu_id].value).indexOf("M=")+2).toFloat();
      if(String(my_config[this->active_menu_id].value).indexOf("s=") != -1) s = String(my_config[this->active_menu_id].value).substring(String(my_config[this->active_menu_id].value).indexOf("s=")+2).toFloat();


      input.action = "";
      output.clearScreen();

     if(input.range_value+s<=M) input.range_value+= s;
        
      this->showRange(input.range_value,m,M,s);
    }
    
    if(input.action == "menu.range.down")
    {
      this->current_menu_id = this->active_menu_id;
        
      float m,M,s = 0;

      //if(String(my_config[this->active_menu_id].value).indexOf("v=") != -1) v = String(my_config[this->active_menu_id].value).substring(String(my_config[this->active_menu_id].value).indexOf("v=")+2).toFloat();
      if(String(my_config[this->active_menu_id].value).indexOf("m=") != -1) m = String(my_config[this->active_menu_id].value).substring(String(my_config[this->active_menu_id].value).indexOf("m=")+2).toFloat();
      if(String(my_config[this->active_menu_id].value).indexOf("M=") != -1) M = String(my_config[this->active_menu_id].value).substring(String(my_config[this->active_menu_id].value).indexOf("M=")+2).toFloat();
      if(String(my_config[this->active_menu_id].value).indexOf("s=") != -1) s = String(my_config[this->active_menu_id].value).substring(String(my_config[this->active_menu_id].value).indexOf("s=")+2).toFloat();


      input.action = "";
      output.clearScreen();

     if(input.range_value-s>=m) input.range_value-= s;
        
      this->showRange(input.range_value,m,M,s);
    }
    
    if(input.action == "menu.range.confirm")
    {
      input.action = "";
      
      //this->saveAlphanumericBufferToMyConfig();
          
      //this->configSave();
      env = 0;

      //input.action = "menu.enter";
      output.clearScreen();
      this->listChildren(items[this->active_menu_id].parent_id); 
    }
    
    if(input.action == "menu.range.cancel")
    {
      input.action = "";
      input.range_value = 0;
      env = 0;

      output.clearScreen();
      this->listChildren(items[this->active_menu_id].parent_id); 
    }
  return;
  }

  void showRange(float v,float m, float M,float s)
  {
    //setting the Range environment
    env = 3;
    
    this->showTitle();
    
    float percent = 0;
    
    percent = v*(CONFIG_MENU_WIDTH-2)/(M-m);
    
    for(byte i=0;i<(CONFIG_MENU_WIDTH-String(v).length())/2;i++)
    {
      output.print(" ");        
    }
    output.println(String(v));
    
    output.print("[");
    for(byte i=0;i<CONFIG_MENU_WIDTH-2;i++)
    {
      if(i<percent)
        output.print("=");
      else 
        output.print(" ");
    }
    output.print("]");
  }
  void changeAlphanumeric()
  {
    //env = 1;
    
    this->showTitle();

    //this->alphanumeric_buffer = value;
    
    output.print(this->alphanumeric_buffer);
    output.println(CONFIG_MENU_EDITOR_CURSOR);
    
    output.print(CONFIG_MENU_EDITOR_CONFIRM);
    output.println(CONFIG_MENU_EDITOR_CANCEL);
    
    
  }
  void saveAlphanumericBufferToMyConfig()
  {
    //my_config[this->active_menu_id].value[0] = '\0';
    //for(byte j=0;j<CONFIG_MENU_WIDTH;j++)
     // my_config[this->active_menu_id].value[j] = this->alphanumeric_buffer[j];
    //this->my_config[this->active_menu_id].value =this->alphanumeric_buffer;
    /*
    char buf[CONFIG_MENU_WIDTH];
    const char *first = "%tpname";
    const char second[16];
    const char *third = "%";
    for(byte i = 0; i< sizeof my_config.tp / sizeof my_config.tp[0]; i++)
    {
      buf[0] = 0;
      itoa(i, second, 10);
      strcpy(buf,first);
      strcat(buf,second);
      strcat(buf,third);
      if(strcmp(items[items[this->active_menu_id].parent_id].title, buf) == 0)
      {
      }
    }
    
    this->alphanumeric_buffer[0] = 0;
    */
    
        switch(env)
        {//title
          case 1:
            for(byte j=0;j<strlen(this->alphanumeric_buffer);j++)
              my_config[this->active_menu_id].value[j] = this->alphanumeric_buffer[j];
              
            my_config[this->active_menu_id].value[strlen(this->alphanumeric_buffer)] = '\0';
          break;

          case 2:
            for(byte j=0;j<strlen(this->alphanumeric_buffer);j++)
              my_config[this->active_menu_id].value[j] = this->alphanumeric_buffer[j];
             my_config[this->active_menu_id].value[strlen(this->alphanumeric_buffer)] = '\0';
          break;

          case 3:
             //my_config.tp[i].rh = atoi(this->alphanumeric_buffer);
          break;

          case 4:
             //my_config.tp[i].duration = atoi(this->alphanumeric_buffer);
          break;
        }
        this->alphanumeric_buffer[0] = 0;
  }
  void typeNextAlphanumericCharacter()
  {
    
    byte lastChar = strlen(this->alphanumeric_buffer);
    
    if(lastChar < CONFIG_MENU_WIDTH)
    {
        
      //find the used input
      for(byte i=0; i< sizeof inputs / sizeof inputs[0]; i++)
      {
        if(inputs[i].pin == input_pin)
        {
          if(input_alphanumeric_position >= strlen(inputs[i].alphanumeric))
            input_alphanumeric_position = 0;

          this->alphanumeric_buffer[lastChar-1] = inputs[i].alphanumeric[input_alphanumeric_position];        
          this->alphanumeric_buffer[lastChar] = 0;
              
          input_alphanumeric_position++;
        }
      }
    }
  }
  void typeNextNumericCharacter()
  {
    byte lastChar = strlen(this->alphanumeric_buffer);
    
    if(lastChar < CONFIG_MENU_WIDTH)
    {
      //find the used input
      for(byte i=0; i< sizeof inputs / sizeof inputs[0]; i++)
      {
        if(inputs[i].pin == input_pin)
        {

            if(input_alphanumeric_position>strlen(inputs[i].alphanumeric))
            {
              input_alphanumeric_position = 0;
            }

          
          byte cycle = 0;
          while(String(inputs[i].alphanumeric[input_alphanumeric_position]).toInt()==0 && inputs[i].alphanumeric[input_alphanumeric_position] != '0' && cycle < 2)
          {
            input_alphanumeric_position++;
            if(input_alphanumeric_position>strlen(inputs[i].alphanumeric))
            {
              input_alphanumeric_position = 0;
              cycle++;
            }
          }
          //Serial.println(input_alphanumeric_position);
          if(inputs[i].alphanumeric[input_alphanumeric_position] == '0' || String(inputs[i].alphanumeric[input_alphanumeric_position]).toInt()!=0)
          {
            if(this->alphanumeric_buffer[lastChar-1]==inputs[i].alphanumeric[input_alphanumeric_position])
            {
              this->alphanumeric_buffer[lastChar] = inputs[i].alphanumeric[input_alphanumeric_position];
              this->alphanumeric_buffer[lastChar+1] = '\0';
            }
            else
            {
              this->alphanumeric_buffer[lastChar-1] = inputs[i].alphanumeric[input_alphanumeric_position];        
              this->alphanumeric_buffer[lastChar] = '\0';
            }
          }
        }
      }
    }
  }
  

};



Menu menu;
