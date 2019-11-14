#ifndef SSDisplay_hpp
#define SSDisplay_hpp

#include <Arduino.h>
#include <Updatable.hpp>

namespace RAW{
    namespace Display{
        // number from 0 up to 9
        static const uint8_t NUMBERS[10] PROGMEM = {0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B};
        static const uint8_t CHARACTERS[] PROGMEM = {
            0x01, // minus
            0x78, // )|]
            0x63, // °|º degree 
            0x77, // A|a
            0x1F, // B|b
            0x4E, // C|c|[|(
            0x3D, // D|d
            0x4F, // E|e
            0x47, // F|f
            // G|g is 6
            0x17, // h
            0x37, // H
            // I|i is 1
            0x3C, // J|j
            0x0E, // L|l
            0x15, // N|n
            // O|o is 0
            0x67, // P|p
            0x05, // R|r
            // S|s is 5
            0x3E, // U|u
            // Z|z is 2
        };

        /**
         * 7-segments display
         */
        class SSDisplay:public Base::Updatable{
            private:
                unsigned long lastBlinkTime, lastDispTime;
                uint16_t dispOnTime, blinkInterval;
                char integer_template[7];
                char *temp_char;
                bool digOn,segOn;
                const uint8_t digSz,segSz;
                uint8_t currDigit,internalState,blinkAmt,blinkState;
                /**
                * Refresh the display.
                */
                void updateHook() override final;

            protected:
                uint8_t* buffer;
                uint8_t* common;
                uint8_t* segment;

                /**
                 * A hook method for subclass implement.
                 * It's called while display's LEDs are switched on.
                 * @note this method can be used to turn on special characters like colon or apostrophe.
                 */
                virtual void onTurnOn(){}

                /**
                 * A hook method for subclass implement.
                 * It's called while display's LEDs are switched off.
                 * @note this method can be used to turn off special characters like colon or apostrophe.
                 */
                virtual void onTurnOff(){}

            public:
                /**
                 * Constructor
                 * @param dig_sz size of common array.
                 * @param common array of display's common pins (digits). Pins must be placed in order, the leftmost digit is the first.
                 * @param seg_sz size of segment array.
                 * @param segment array of Arduino's pin numbers linked to display's segment pins. The order of pins must be: decimal point (if any),a-segment,b-segment,c-segment and so on.
                 * @param isCommonCathode is Display common cathode?
                 */
                SSDisplay(uint8_t dig_sz, const uint8_t common[], uint8_t seg_sz, const uint8_t segment[], bool isCommonCathode);
                
                ~SSDisplay();
                
                /**
                 * clean buffers and turn off the display.
                 */
                void clean();

                /**
                 * Blink the display.
                 * @param uint8_t amount of blinks.
                 */
                void blink(uint8_t);

                /**
                 * Tuning blink interval.
                 * @param uint16_t a single value to show and hide (in milliseconds). Default is 250.
                 * @note Minimum value is 120
                 */
                void setBlinkInterval(uint16_t);

                /**
                 * Test if all display's segment are working.
                 * @note it uses a busy wait, avoid call it in a loop.
                 */
                void lightUp();

                /**
                 * Suppress leading zeros of integer numbers.
                 */
                void suppressLeadingZeros();

                /**
                 * Tuning display's brightness
                 * @param percent A value between 1% and 100%.
                 * @note Default value is 50%.
                 */
                void setBrightness(uint8_t percent);

                /**
                 * Write an integer into buffer.
                 * Numbers with more digits than the display aren't shown.
                 * @param int an integer number.
                 */
                void write(int);

                /**
                 * Write a float into buffer.
                 * Numbers with more digits than the display aren't shown.
                 * @param float a float number.
                 */
                void write(float);

                /**
                 * Write a string into buffer.
                 * Strings with more characters than the display aren't shown, and the set of characters that can be shown varies according to display's technology.
                 * @note If string's decimal points exceeds the amount of decimal points of the display, the trailing decimal points are truncated.
                 * @param msg a c_string text.
                 */
                void write(const char msg[]);

        };
    }
}

#endif