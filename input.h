
class InputClass {


private:


public:
     // for incoming serial data
  byte incomingByte;
  char* action;

  void listen()
  {
    if (Serial.available() > 0) {
    
      // read the incoming byte:
      incomingByte = Serial.read();
      
      
      switch (env)
      {
        case 0:          
          this->parseListChildren();
        break;

        case 1:
        case 2:
          this->parseEditor();
        break;
        case 3:
          this->parseRange();
        break;
      }

    }
    return;
  }


  void parseListChildren()
  {
    //output.println(String(incomingByte));
    Serial.println(incomingByte);
    switch (incomingByte)
    {
      // UP ARROW
      case 97:
        this->action = "menu.changeSelectionUp";
      break;

      // DOWN ARROW
      case 122:
        this->action = "menu.changeSelectionDown";
      break;

      //ENTER
      case 101:
        this->action = "menu.enter";
      break;

      default:
      break;
    }
  }

  void parseRange()
  {
    switch (incomingByte)
    {
      // UP ARROW (a)
      case 97:
        this->action = "menu.range.up";
      break;

      // DOWN ARROW
      case 122:
        this->action = "menu.range.down";
      break;

      //ENTER
      case 101:
        this->action = "menu.range.confirm";
      break;

      //CANCEL
      case 99:
        this->action = "menu.range.cancel";
      break;

      default:
      break;
    }
  }

  void parseEditor()
  {
    //output.println(String(incomingByte));
    switch (incomingByte)
    {
      // UP ARROW (a)
      case 97:
        this->action = "menu.editor.delete";
      break;

      // DOWN ARROW
      case 122:
        //this->action = "menu.changeSelectedOptionDown";
      break;

      //ENTER
      case 101:
        this->action = "menu.editor.confirm";
      break;

      //CANCEL
      case 99:
        this->action = "menu.editor.cancel";
      break;

      case 48:
      case 49:
      case 50:
      case 51:
      case 52:
      case 53:
      case 54:
      case 55:
      case 56:
      case 57:
      case 120:
        this->action = "menu.editor.type";
      break;

      default:
      break;
    }
  }

  
  


};



InputClass input;
