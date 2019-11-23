/*
  This is an interactive sample that uses Arduino's default-serial interface.
  You must provide the type of data you want to print followed by pipe and the content itself.
      Ex: type|content
  
  The following types are available:
      f for float numbers. The syntax is 'f' followed by dot and precision.
            Ex: f.1|5.26 //precision equals to one.
      
      d for integer numbers.
            Ex: d|123

      s for strings.
            Ex: s|s.o.s

*/
#include <SSDisplay.hpp>

using RAW::Display::SSDisplay;

uint8_t digits[]={41,39,35};
uint8_t segs[]={45,43,33,31,47,27,37,29};

// Instance for a common cathode, three-digits and seven-segment display
SSDisplay display(3,digits,8,segs, true);

size_t size;
char buffer[10];
float fnumber;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  display.suppressLeadingZeros();
  display.setBrightness(10);
}

void loop() {
  if(Serial.available()>0){
    size=Serial.readBytes(buffer,sizeof(buffer)/sizeof(char));
    buffer[size-1]='\0';
    Serial.println(buffer);
    Serial.println(strlen(buffer),DEC);
    char *ptr;
    ptr=strtok(buffer,"|");
    switch(*ptr){
      case 'f':{
        ptr=strtok(NULL,"|");
        fnumber=atof(ptr);
        ptr=strtok(buffer+1,".|");
        uint8_t prec=atoi(ptr);
        display.write(fnumber,prec);
        }
        break;

      case 'd':{
        Serial.println(ptr);
        ptr=strtok(NULL,"|");
        display.write(atoi(ptr));
        }
        break;

      case 's':{
        ptr=strtok(NULL,"|");
        Serial.println(ptr);
        Serial.println(strlen(ptr),DEC);
        display.write(ptr);
        }
        break;

    }
    
  }
  display.update();
}