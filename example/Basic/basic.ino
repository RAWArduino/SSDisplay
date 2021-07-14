#include <SSDisplay.hpp>

using RAW::Display::SSDisplay;
using RAW::Display::Warning;

// pin numbers for digits
byte digits[] = {41,39,35};

/* pin numbers for segments. If the display has decimal point, this array must be 8.
The first pin is the decimal point, second pin is A segment, third is B segment and so son.
*/
byte segments[] = {45, 43, 33, 31, 47, 27, 37, 29};

// Creates a common-cathode display with 3 digits and 7 segments plus decimal point.
SSDisplay display(3, digits, 8, segments, true);

void setup()
{
    // adjust the brightness in 20% of capacity.
    Warning wrn=display.setBrightness(20);
    // causing display overflow because display has 3 digits.
    wrn|=display.write("Hello.");
    // is there some warning?
    if(wrn!=Warning::NO_WRN){
        // write Hi.
        display.write("Hi.");
    }
}

void loop()
{
    // Calling the update method.
    display.update();
}