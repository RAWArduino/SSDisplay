#### 7-Segment Display (SSDisplay)

# Introduction

Following the proposal of *RAWArduino*, *SSDisplay* is a library to control common-cathode and common-anode 7-segment displays directly from Arduino without any external integrated circuit. At first, it implements the main functionalities of a LED 7-segment display, controlling digits and decimal points exhibition. However, you may extend *SSDisplay* to meet your needs, given that it has similarity with template-method pattern. Thus, you can override the hook methods `onShow()` and `onHide()` to extend its functionalities when LEDs turn on or off, respectively. This is useful if your display has peculiarities like colons or apostrophe.

Keep in mind that the main aim of all *RAWArduino* libraries is prototyping, study and research; allowing fast building at low cost. Furthermore, such a project doesn't use third party libraries and is compliant with *PlatformIO* requirements.
<br/><br/>

# Features

- Brightness adjust 

    &emsp;&emsp; <img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/brightness.gif" width="70"/>
  
- Suppression of leading zeros

    &emsp;&emsp; <img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/leadingZero.png" width="70"/>
  
- Display blink with adjust of interval

   &emsp;&emsp; <img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/blink300.gif" width="70"/> &emsp;&emsp;>>><sup>+200 ms</sup>&emsp;&emsp; <img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/blink500.gif" width="70"/>

- Alphanumeric characters

    |Characters    |A    |B    |C    |D    |E    |F    |G    |H    |h    |I    |J    |L    |N    |O    |P    |R    |S    |U    |Z    |
    |:----         |:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
    |**Exhibition**|<img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/A.png"/>|<img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/B.png"/>|<img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/C.png"/>|<img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/D.png"/>|<img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/E.png"/>|<img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/F.png"/>|<img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/G.png"/>|<img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/H.png"/>|<img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/mh.png"/>|<img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/I.png"/>|<img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/J.png"/>|<img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/L.png"/>|<img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/N.png"/>|<img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/O.png"/>|<img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/P.png"/>|<img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/R.png"/>|<img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/S.png"/>|<img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/U.png"/>|<img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/Z.png"/>|
    
    *Only H letter is case sensitive.*
    <br/><br/>

    |Special Characters|[(   |])   |-    |
    |:---              |:---:|:---:|:---:|
    |**Exhibition**|<img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/C.png"/>|<img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/paren.png"/>|<img src="https://github.com/RAWArduino/SSDisplay/raw/master/docs/images/minus.png"/>|
<br/>

# Basic usage

```c++
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
```

For more examples, see the [example](https://github.com/RAWArduino/SSDisplay/tree/master/example) folder. And look at the [docs](https://rawarduino.github.io/SSDisplay) for more details.
<br/><br/>

# Changelog

For changelogs, see [Releases](https://github.com/RAWArduino/SSDisplay/releases).