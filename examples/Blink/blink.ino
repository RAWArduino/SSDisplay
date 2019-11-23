/*
    This example shows what the blink method does.
    It's a simple counter from 0 up to 100, in which odd numbers blink for 2 times.
*/

#include <SSDisplay.hpp>

using RAW::Display::SSDisplay;

// A counter for tuning brightness.
byte count=0;

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
    // Call this method to suppress leading zeros
    display.suppressLeadingZeros();
    
    // if blink interval is 350 milliseconds, we take 700 milliseconds for the total cycle.
    display.setBlinkInterval(400);
    display.write(count);
}

void loop(){
    if(millis()-lastTime>1500){
        count=(count+1)%100;
        display.write(count);
        // This while-statement is for code simplicity.
        // In real application, we must use something like a state machine.
        // Indeed, it's a busy wait.
        lastTime=millis();
        while(millis()-lastTime<350)display.update();
        
        // odd number must blink
        if(count%2!=0)display.blink(2);
        lastTime=millis();
    }
    // Calling the update method.
    display.update();
}