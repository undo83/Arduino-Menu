
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
  
  char dest[CONFIG_MENU_WIDTH];
  
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
    output.println("---------------");
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
        s.replace(buf, items[i].value);
    }
    
    if(s.length() == 0) s = CONFIG_MENU_EMPTY;
    
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
          Serial.println(   this->active_menu_id);  
           /*my_config.single_selection_settings[0] = this->active_menu_id;
          this->configSave();
          
          output.clearScreen();
          
          this->listChildren(this->current_menu_id);        */
        }/*
        else if(strcmp(items[this->active_menu_id].function, "changeSettingsUnits") == 0)
        {            
           my_config.single_selection_settings[1] = this->active_menu_id;
          this->configSave();
          
          output.clearScreen();
          
          this->listChildren(this->current_menu_id);        
        }
        else if(strcmp(items[this->active_menu_id].function, "changeSettingsCycleEnd") == 0)
        {            
           my_config.single_selection_settings[2] = this->active_menu_id;
          this->configSave();
          
          output.clearScreen();
          
          this->listChildren(this->current_menu_id);        
        }
        else if(strcmp(items[this->active_menu_id].function, "changeCycleStartFrom") == 0)
        {            
          my_config.single_selection_settings[3] = this->active_menu_id;
          this->configSave();
          
          output.clearScreen();
          
          this->listChildren(this->current_menu_id);        
        }
        else if(strcmp(items[this->active_menu_id].function, "changeTPName") == 0)
        {            
          output.clearScreen();
          this->parseTitle(items[items[this->active_menu_id].parent_id].title);
          for(byte i=0;i<CONFIG_MENU_WIDTH;i++)
           this->alphanumeric_buffer[i] = dest[i];
           
          this->changeAlphanumeric();    
        }
        else if(strcmp(items[this->active_menu_id].function, "changeTPT0") == 0 ||
                strcmp(items[this->active_menu_id].function, "changeTPT1") == 0 ||
                strcmp(items[this->active_menu_id].function, "changeTPT2") == 0 ||
                strcmp(items[this->active_menu_id].function, "changeTPT3") == 0 ||
                strcmp(items[this->active_menu_id].function, "changeTPT4") == 0 ||
                strcmp(items[this->active_menu_id].function, "changeTPT5") == 0 
        )
        {            
          output.clearScreen();
          this->parseTitle(items[items[this->active_menu_id].parent_id].title);
          
          this->changeTPT();
          
        }
        */
    }
    /*
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

      //input.action = "menu.enter";
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
          this->alphanumeric_buffer[lastChar] = " ";
          this->alphanumeric_buffer[lastChar+1] = 0;
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
          
        //this->alphanumeric_buffer[lastChar+1] = '\0'; //replace it with a NULL
      }
      
      this->changeAlphanumeric();
    }
    */
  return;
  }

  
  /*

  byte returnPointsSize()
  {
    byte my_size = 0;
    for(byte i=0;i< sizeof my_config.tp / sizeof my_config.tp[0]; i++)
    {
      //if(my_config.tp[i].duration > 0)
        my_size++;
    }
    return my_size;
  }
  
  




  
  void editRange(int min, int max, int &variable, byte direction)
  {
    
    String s;
    
    variable=variable + direction;
    
    if(variable<min) variable = min;
    if(variable>max) variable = max;
    
    output.println(variable);
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

  void changeTPT()
  {
    if(strcmp(items[this->active_menu_id].function, "changeTPT0") == 0)
      //itoa(my_config.tp[0].temperature, this->alphanumeric_buffer, 10);    
    if(strcmp(items[this->active_menu_id].function, "changeTPT1") == 0)
     // itoa(my_config.tp[1].temperature, this->alphanumeric_buffer, 10);
    if(strcmp(items[this->active_menu_id].function, "changeTPT2") == 0)
     // itoa(my_config.tp[2].temperature, this->alphanumeric_buffer, 10);
    if(strcmp(items[this->active_menu_id].function, "changeTPT3") == 0)
      //itoa(my_config.tp[3].temperature, this->alphanumeric_buffer, 10);
    if(strcmp(items[this->active_menu_id].function, "changeTPT4") == 0)
      //itoa(my_config.tp[4].temperature, this->alphanumeric_buffer, 10);
    if(strcmp(items[this->active_menu_id].function, "changeTPT5") == 0)
      //itoa(my_config.tp[5].temperature, this->alphanumeric_buffer, 10);

      env = 2;
    
    this->showTitle();

    //this->alphanumeric_buffer = value;
    
    output.print(this->alphanumeric_buffer);
    output.println(CONFIG_MENU_EDITOR_CURSOR);
    
    output.print(CONFIG_MENU_EDITOR_CONFIRM);
    output.println(CONFIG_MENU_EDITOR_CANCEL);
  }
  
  void changeAlphanumeric()
  {
    env = 1;
    
    this->showTitle();

    //this->alphanumeric_buffer = value;
    
    output.print(this->alphanumeric_buffer);
    output.println(CONFIG_MENU_EDITOR_CURSOR);
    
    output.print(CONFIG_MENU_EDITOR_CONFIRM);
    output.println(CONFIG_MENU_EDITOR_CANCEL);
    
    
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
  void changeNumeric()
  {
    env = 2;
    
    this->showTitle();

    //this->alphanumeric_buffer = value;
    
    output.print(this->alphanumeric_buffer);
    output.println(CONFIG_MENU_EDITOR_CURSOR);
    
    output.print(CONFIG_MENU_EDITOR_CONFIRM);
    output.println(CONFIG_MENU_EDITOR_CANCEL);
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
          //if there are no numeric values inside, return;
          bool numeric_values = false;
          for(byte j=0;j < strlen(inputs[i].alphanumeric);j++)
          {
            if(atoi(inputs[i].alphanumeric[j]) > 0 || inputs[i].alphanumeric[j] == '0')
              numeric_values = true;
          }

          if(!numeric_values) 
            return;
            
          if(input_alphanumeric_position >= strlen(inputs[i].alphanumeric))
            input_alphanumeric_position = 0;

          if(atoi(inputs[i].alphanumeric[input_alphanumeric_position])==0)
          {
            input_alphanumeric_position++;
            this->typeNextNumericCharacter();
          }
          else
          {
              this->alphanumeric_buffer[lastChar-1] = inputs[i].alphanumeric[input_alphanumeric_position];        
              this->alphanumeric_buffer[lastChar] = 0;
          }
          
              
          
        }
      }
    }
  }
  void saveAlphanumericBufferToMyConfig()
  {
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
        switch(env)
        {//title
          case 1:
            for(byte j=0;j<CONFIG_MENU_WIDTH;j++)
             // my_config.tp[i].title[j] = this->alphanumeric_buffer[j];
          break;

          case 2:
             //my_config.tp[i].temperature = atoi(this->alphanumeric_buffer);
          break;

          case 3:
             //my_config.tp[i].rh = atoi(this->alphanumeric_buffer);
          break;

          case 4:
             //my_config.tp[i].duration = atoi(this->alphanumeric_buffer);
          break;
        }
      }
    }
    
    this->alphanumeric_buffer[0] = 0;
  }
  
*/
};



Menu menu;
