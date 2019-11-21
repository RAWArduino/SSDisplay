/*
    This sample explores the brightness feature.
    It shows a "8.8.8." text whose brightness starts weak and becomes strong over time.
*/

#include <SSDisplay.hpp>

using RAW::Display::SSDisplay;

// A counter for tuning brightness.
byte count=1;

// For counter increment
unsigned long lastTime=0;

// pin numbers for digits
byte digits[]={41,39,35};

/* pin numbers for segments. If the display has decimal point, this array size must be 8.
   The first pin is the decimal point, second pin is A segment, third is B segment and so son.
*/ 
byte segments[]={45,43,33,31,47,27,37,29};

const byte size_of_digits=sizeof(digits)/sizeof(byte);
const byte size_of_segments=sizeof(segments)/sizeof(byte);

// Creates a common-cathode display with 3 digits and 7 segments plus decimal point.
// Read the docs for details.
SSDisplay display(size_of_digits, digits, size_of_segments, segments, true);

void setup(){
    // Write something
    display.write("8.8.8.");
    display.setBrightness(count);
}

void loop(){
    // Set brightness every 200 milliseconds.
    if(millis()-lastTime>200){
        count=count>99 ? 1 : count+1;
        // brightness tuning
        display.setBrightness(count);
        lastTime=millis();
    }

    // Calling the update method.
    display.update();
}