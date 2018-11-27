
class Menu {


private:


  
  bool checkSelected(byte id)
  {
    EEPROM.get(id*CONFIG_MENU_WIDTH,EEPROMbuf);
    if(atoi(EEPROMbuf) == 1) return true;
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
  
  char EEPROMbuf[CONFIG_MENU_WIDTH];
  char alphanumeric_buffer[CONFIG_MENU_WIDTH];
  byte input_pin = 0;
  byte input_alphanumeric_position = 0;
  
  Range r;
  
  char dest[CONFIG_MENU_WIDTH];
  
  unsigned long timer = 0;//millis();
  
  //Config my_config[sizeof items/sizeof items[0]];

  void EEPROMSaveDefault()
  {
      /*                      DEFAULTS              */
      EEPROM.put(0,"init");
      EEPROM.put(CONFIG_MENU_WIDTH*18,"1");
      EEPROM.put(CONFIG_MENU_WIDTH*21,"1");
      EEPROM.put(CONFIG_MENU_WIDTH*25,"1");
      EEPROM.put(CONFIG_MENU_WIDTH*28,"1");
      EEPROM.put(CONFIG_MENU_WIDTH*35,"Fermentation");
      EEPROM.put(CONFIG_MENU_WIDTH*36,"22");
      EEPROM.put(CONFIG_MENU_WIDTH*37,"75");
      EEPROM.put(CONFIG_MENU_WIDTH*38,"100");
      EEPROM.put(CONFIG_MENU_WIDTH*40,"Curing 1");
      EEPROM.put(CONFIG_MENU_WIDTH*41,"13");
      EEPROM.put(CONFIG_MENU_WIDTH*42,"80");
      EEPROM.put(CONFIG_MENU_WIDTH*43,"100");
      EEPROM.put(CONFIG_MENU_WIDTH*45,"Curing 2");
      EEPROM.put(CONFIG_MENU_WIDTH*46,"15");
      EEPROM.put(CONFIG_MENU_WIDTH*47,"75");
      EEPROM.put(CONFIG_MENU_WIDTH*48,"24");    
  }

  void EEPROMCheck()
  {    
    EEPROM.get(0,EEPROMbuf);
    if(strcmp(EEPROMbuf, "init") != 0)
    { 
      Serial.println("Not initialized. Initializing now...");       
      this->EEPROMSaveDefault();
      
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
    this->changeSelection(true);
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

        if(s.indexOf(buf)>=0)
        {
          EEPROM.get(i*CONFIG_MENU_WIDTH,EEPROMbuf);
          s.replace(buf, EEPROMbuf);
        }        
    }
    
    if(s.length() == 0) s = CONFIG_MENU_EMPTY;

    
    //if(s.indexOf("v=")!=-1)

    
    for(byte j=0;j < CONFIG_MENU_WIDTH; j++)
      dest[j] = s[j];      
  }
  
  void changeSelection(bool direction)
  {
    byte n_items = sizeof items / sizeof items[0];
    
    
      if(direction) this->active_menu_id++;
      else this->active_menu_id--;
      
      if(this->active_menu_id <= 0) this->active_menu_id = n_items-1;
      if(this->active_menu_id >= n_items) this->active_menu_id = 0;

    if(items[this->active_menu_id].parent_id != this->current_menu_id)
      this->changeSelection(direction);
      

  }


  void menuAnswer()
  {
    if(input.action == "menu.changeSelectionDown")
    {
        
      input.action = "";
      this->changeSelection(true);
      
      output.clearScreen();
      
      this->listChildren(this->current_menu_id);
    }
    
    if(input.action == "menu.changeSelectionUp")
    {
        input.action = "";
        this->changeSelection(false);

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
          this->changeSelection(true);
          
          output.clearScreen();
          
          this->listChildren(this->current_menu_id);        
        }    
        
     else if(strcmp(items[this->active_menu_id].function, "listEEPROM") == 0)
    {
      input.action = "";
      output.clearScreen();
      int t=0;
      char c[22];
      for(byte i=0;i<sizeof items/sizeof items[0];i++)
      {
        EEPROM.get(i*CONFIG_MENU_WIDTH,c);
        Serial.println(c);
       // t+= sizeof(c);
      }
    }    
        else if(strcmp(items[this->active_menu_id].function, "back") == 0)
        {            
          this->current_menu_id = items[this->current_menu_id].parent_id;
          this->active_menu_id = 0;
          this->changeSelection(true);

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
              //my_config[i].value = "0";
              EEPROM.put(CONFIG_MENU_WIDTH*i, '0');
            }

            if(i == this->active_menu_id)
              //my_config[i].value = "1";
              EEPROM.put(CONFIG_MENU_WIDTH*i, '1');
              
          }
          
          //this->configSave(i, my_config[i].value);

          this->current_menu_id = items[this->active_menu_id].parent_id;

          output.clearScreen();
          
          this->listChildren(this->current_menu_id); 
        }
        else if(strcmp(items[this->active_menu_id].function, "setMultipleOption") == 0)
        {
          EEPROM.get(this->active_menu_id*CONFIG_MENU_WIDTH,EEPROMbuf);
          if(EEPROMbuf[0] == '0')
            EEPROM.put(CONFIG_MENU_WIDTH*this->active_menu_id, '1');
          else
            EEPROM.put(CONFIG_MENU_WIDTH*this->active_menu_id, '0');
          
          //this->configSave(this->active_menu_id, my_config[this->active_menu_id].value);

          this->current_menu_id = items[this->active_menu_id].parent_id;

          output.clearScreen();
          
          this->listChildren(this->current_menu_id); 
        }
        else if(strcmp(items[this->active_menu_id].function, "selectRange") == 0)
        {
          this->current_menu_id = this->active_menu_id;

          EEPROM.get(this->active_menu_id*CONFIG_MENU_WIDTH,EEPROMbuf);
          r = this->parseRange(EEPROMbuf, items[this->active_menu_id].params);
          
          output.clearScreen();

          //input.range_value = r.v;
          
          this->showRange(r);

        }
        else if(strcmp(items[this->active_menu_id].function, "setAlphaNumeric") == 0)
        {            
          output.clearScreen();
          EEPROM.get(this->active_menu_id*CONFIG_MENU_WIDTH,EEPROMbuf);
          this->parseTitle(EEPROMbuf);
          for(byte i=0;i<CONFIG_MENU_WIDTH;i++)
           this->alphanumeric_buffer[i] = dest[i];

          env = 1; 
          this->changeAlphanumeric();    
        }
        else if(strcmp(items[this->active_menu_id].function, "setNumeric") == 0)
        {            
          output.clearScreen();
          EEPROM.get(this->active_menu_id*CONFIG_MENU_WIDTH,EEPROMbuf);
          //char* c = EEPROMGet(this->active_menu_id);
          this->parseTitle(EEPROMbuf);
          for(byte i=0;i<CONFIG_MENU_WIDTH;i++)
           this->alphanumeric_buffer[i] = EEPROMbuf[i];
           
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
          
      //this->configSave();
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
      
      input.action = "";
      output.clearScreen();

      if(r.v+r.s<=r.M) r.v+= r.s;
      else
        r.v = r.M;
      
      this->showRange(r);
    }
    
    if(input.action == "menu.range.down")
    {
      this->current_menu_id = this->active_menu_id;
      //r = this->parseRange(my_config[this->active_menu_id].value);  
      
      input.action = "";
      output.clearScreen();

      if(r.v-r.s>=r.m) r.v-= r.s;
      else
        r.v = r.m;
      
      
      this->showRange(r);
    }
    
    if(input.action == "menu.range.confirm")
    {
      char buffloat[CONFIG_MENU_WIDTH];
      String(r.v).toCharArray(buffloat,CONFIG_MENU_WIDTH);
      EEPROM.put(CONFIG_MENU_WIDTH*this->active_menu_id, buffloat);
      
      input.action = "";
      
      env = 0;
      this->current_menu_id = items[this->active_menu_id].parent_id;
      output.clearScreen();
      this->listChildren(items[this->active_menu_id].parent_id); 
    }
    
    if(input.action == "menu.range.cancel")
    {
      input.action = "";
      
      env = 0;

      this->current_menu_id = items[this->active_menu_id].parent_id;
      output.clearScreen();
      this->listChildren(items[this->active_menu_id].parent_id); 
    }
  return;
  }

  void showRange(Range range)
  {
    //setting the Range environment
    env = 3;
    
    this->showTitle();
    
    float percent = 0;
    
    percent = range.v*(CONFIG_MENU_WIDTH-2)/(range.M-range.m);
    
    for(byte i=0;i<(CONFIG_MENU_WIDTH-String(range.v).length())/2;i++)
    {
      output.print(" ");        
    }
    output.println(String(range.v));
    
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
    
    this->showTitle();
    
    output.print(this->alphanumeric_buffer);
    output.println(CONFIG_MENU_EDITOR_CURSOR);
    
    output.print(CONFIG_MENU_EDITOR_CONFIRM);
    output.println(CONFIG_MENU_EDITOR_CANCEL);
    
    
  }
  void saveAlphanumericBufferToMyConfig()
  {
    //char* c = EEPROMGet(this->active_menu_id);
        switch(env)
        {//title
          case 1:
            //for(byte j=0;j<strlen(this->alphanumeric_buffer);j++)
              //c[j] = this->alphanumeric_buffer[j];
              EEPROM.put(CONFIG_MENU_WIDTH*this->active_menu_id, this->alphanumeric_buffer);
              
            //my_config[this->active_menu_id].value[strlen(this->alphanumeric_buffer)] = '\0';
          break;

          case 2:
            //for(byte j=0;j<strlen(this->alphanumeric_buffer);j++)
              //my_config[this->active_menu_id].value[j] = this->alphanumeric_buffer[j];
            // my_config[this->active_menu_id].value[strlen(this->alphanumeric_buffer)] = '\0';
            EEPROM.put(CONFIG_MENU_WIDTH*this->active_menu_id, this->alphanumeric_buffer);
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

  Range parseRange(char value[CONFIG_MENU_WIDTH], char* query)
  {
    Range range;
    // r = this->parseRange(EEPROMbuf, items[this->active_menu_id].params);
    //if(String(query).indexOf("v=") != -1) range.v = String(query).substring(String(query).indexOf("v=")+2).toFloat();
    range.v = String(value).toFloat();
    if(String(query).indexOf("m=") != -1) range.m = String(query).substring(String(query).indexOf("m=")+2).toFloat();
    if(String(query).indexOf("M=") != -1) range.M = String(query).substring(String(query).indexOf("M=")+2).toFloat();
    if(String(query).indexOf("s=") != -1) range.s = String(query).substring(String(query).indexOf("s=")+2).toFloat();

    return range;
  }

  

};



Menu menu;
