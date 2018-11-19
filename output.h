
class Output {


private:

public:

  void setup()
  {
    Serial.begin(115200);
    while (!Serial) continue;

    return;
  }
  
  void print(String str)
  {
    Serial.print(str);

    return;
  }
  void println(String str)
  {
    Serial.println(str);

    return;
  }
  
  void printActiveLine(String title, bool selected)
  {
    Serial.print(">");
    Serial.print(title);
    if(selected) Serial.print("*");
    Serial.println();

    return;
  }
  void printNormalLine(String title, bool selected)
  {
    Serial.print(title);
    if(selected) Serial.print("*");
    Serial.println();

    return;
  }
  

  void clearScreen()
  {
    for(int i=0;i<50;i++)
    {
      Serial.println();
    }
  }

  void str_replace(char *src, char *oldchars, char *newchars) { // utility string function
    char *p = strstr(src, oldchars);
    char buf[CONFIG_MENU_WIDTH];
    do {
      if (p) {
        memset(buf, '\0', strlen(buf));
        if (src == p) {
          strcpy(buf, newchars);
          strcat(buf, p + strlen(oldchars));
        } else {
          strncpy(buf, src, strlen(src) - strlen(p));
          strcat(buf, newchars);
          strcat(buf, p + strlen(oldchars));
        }
        memset(src, '\0', strlen(src));
        strcpy(src, buf);
      }
    } while (p && (p = strstr(src, oldchars)));
  }

};

Output output;
