#include "SSDisplay.hpp"

using RAW::Display::SSDisplay;

uint8_t digits[]={41,39,35};
uint8_t segs[]={45,43,33,31,47,27,37,29};

// Instance for a common cathode, three-digits and seven-segments display
SSDisplay display(3,digits,8,segs, true);
unsigned long lastTime=0L;

enum Event{MAX_INTEGER_POSITIVE=0,
           MAX_INTEGER_NEGATIVE,
           MAX_FLOAT_NEGATIVE,
           MAX_FLOAT_POSITIVE,
           INTEGER_OVERFLOW,
           ONLY_THREE_DOTS,
           FLOAT_OVERFLOW,
           TEXT_ONE,
           INTEGER_UNDERFLOW,
           TEXT_TWO,
           FLOAT_UNDERFLOW,
           ONLY_FIRST_DOT,
           MIN_INTEGER,
           MIN_FLOAT,
           TEXT_THREE,
           TEXT_FOUR,
           TEXT_NOTHING,
           TEXT_TRAILING_DOTS
};

uint8_t evt=0;

void setup() {
  display.suppressLeadingZeros();
  display.setBrightness(30);
  display.setBlinkInterval(100);
  display.lightUp();
  // blink
  display.write(123);
  lastTime=millis();
  while(millis()-lastTime < 1000)display.update();
  display.blink(3);
  lastTime=millis();
  while(millis()-lastTime < 4000)display.update();
}

void loop() {
  if(millis()-lastTime > 1000){
    switch(evt){
      case MAX_INTEGER_POSITIVE:
        display.write(999);
        break;

      case MAX_INTEGER_NEGATIVE:
        display.write(-99);
        break;

      case MAX_FLOAT_NEGATIVE:
        display.write(-9.9f);
        break;

      case MAX_FLOAT_POSITIVE:
        display.write(99.9f);
        break;

      case INTEGER_OVERFLOW:
        display.write(1000);
        break;

      case ONLY_THREE_DOTS:
        display.write(" . . .");
        break;

      case INTEGER_UNDERFLOW:
        display.write(-100);
        break;

      case FLOAT_OVERFLOW:
        display.write(1000.f);
        break;

      case FLOAT_UNDERFLOW:
        display.write(-100.f);
        break;

      case ONLY_FIRST_DOT:
        display.write(" .");
        break;

      case TEXT_ONE:
        display.write("s.o.s.");
        break;
      
      case TEXT_TWO:
        display.write("aus");
        break;
      
      case TEXT_THREE:
        display.write("HhH");
        break;
      
      case TEXT_FOUR:
        display.write("O n");
        break;

      case TEXT_NOTHING:
        display.write("");
        break;

      case TEXT_TRAILING_DOTS:
        display.write("I.s.s...");
        break;

      case MIN_FLOAT:
        display.write(.01f);
        break;

      case MIN_INTEGER:
        display.write(1);
        break;

    }

    evt=(evt+1)%18;
    lastTime=millis();

  }

  display.update();
}