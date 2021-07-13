#ifndef SSDisplay_hpp
#define SSDisplay_hpp

#include <Arduino.h>

namespace RAW{
    /**
     * Groups technologies of displays.
     * Some technologies may be LED, LCD and so on.
     */
    namespace Display{
        // number from 0 up to 9
        static const uint8_t NUMBERS[10] PROGMEM = {0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B};
        static const uint8_t CHARACTERS[] PROGMEM = {
            0x01, // minus
            0x78, // )|]
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
         * Enumeration of fixed type for handling warnings.
         * Writer and setter methods return a combination of Warning enumerators that can be verified with bitmask.
         */
        enum Warning:uint8_t{
            NO_WRN=0, ///< No Warning. Allright.
            DISPLAY_OVERFLOW=1, ///< Message doesn't fit into display.
            PRECISION_OUT_OF_RANGE=1<<1, ///< Precision parameter is out of range.
            PRECISION_FORCED_TO_ONE=1<<2, ///< Presicion was forced to one.
            BRIGHTNESS_OUT_OF_RANGE=1<<3, ///< brightness parameter is out of range.
            INTERVAL_OUT_OF_RANGE=1<<4 ///< Blink interval is out of range.
        };

        inline Warning operator|(const Warning& one, const Warning& other){
            return Warning(uint8_t(one)|uint8_t(other));
        }

        inline Warning& operator|=(Warning& one, const Warning& other){
            one=one|other;
            return one;
        }

        inline Warning operator&(const Warning& one, const Warning& other){
            return Warning(uint8_t(one)&uint8_t(other));
        }

        inline Warning& operator&=(Warning& one, const Warning& other){
            one=one&other;
            return one;
        }

        inline Warning operator^(const Warning& one, const Warning& other){
            return Warning(uint8_t(one)^uint8_t(other));
        }

        inline Warning& operator^=(Warning& one, const Warning& other){
            one=one^other;
            return one;
        }

        inline Warning operator~(const Warning& one){
            return Warning(~uint8_t(one));
        }

        

        /**
         * LED 7-segment displays.
         * This class controls LED 7-segment displays, which can be common-cathode or common-anode.
         * @author Kelvin S. Amorim
         */
        class SSDisplay{
            private:
                unsigned long lastBlinkTime, lastDispTime;
                uint16_t dispOnTime, blinkInterval;
                char integer_template[7];
                char *temp_char;
                const uint8_t digSz,segSz;
                uint8_t currDigit,internalState,blinkAmt,blinkState;
                uint8_t* buffer;
                uint8_t* common;
                uint8_t* segment;
                bool digOn, segOn;

            protected:
                const bool &digitOn; ///< It's false for common cathode and true for common anode. Use it to turn on/off a digit.
                const bool &segmentOn; ///< It's true for common cathode and false for common anode. Use it to turn on/off a segment.

                /**
                 * A hook method for subclass to implement.
                 * It's called while display is showing something.
                 * @remark this method can be used to turn on special characters like colon or apostrophe.
                 */
                virtual void onShow(){}

                /**
                 * A hook method for subclass to implement.
                 * It's called while display is showing nothing.
                 * @remark this method can be used to turn off special characters like colon or apostrophe.
                 */
                virtual void onHide(){}

            public:

                /**
                 * Constructor.
                 * @param dig_sz size of common array.
                 * @param common array of display's common pins (digits). Pins must be placed in order, the leftmost digit is the first.
                 * @param seg_sz size of segment array.
                 * @param segment array of Arduino's pin numbers linked to display's segment pins. The order of pins must be: decimal point (if any),a-segment,b-segment,c-segment and so on.
                 * @param isCommonCathode is Display common cathode?
                 * @remark It copies common and segment params.
                 */
                SSDisplay(uint8_t dig_sz, const uint8_t common[], uint8_t seg_sz, const uint8_t segment[], bool isCommonCathode);
                
                virtual ~SSDisplay();
                
                /**
                 * clean buffers and turn off the display.
                 */
                void clean();

                /**
                 * Blink the display.
                 * @param amnt amount of blinks.
                 */
                void blink(uint8_t);

                /**
                 * Tuning blink interval.
                 * @param interval a single value to show and hide (in milliseconds).
                 * @return #INTERVAL_OUT_OF_RANGE whether parameter is less than 120 or #NO_WRN otherwise.
                 * @remark If parameter is less than 120, it sets the interval to default value (250).
                 * @remark Minimum value is 120.
                 */
                Warning setBlinkInterval(uint16_t);

                /**
                 * Test if all display's segment are working.
                 * @remark it uses busy wait, avoid call it in a loop.
                 */
                void lightUp();

                /**
                 * Suppress leading zeros of integer numbers.
                 */
                void suppressLeadingZeros();

                /**
                 * Tuning display's brightness
                 * @param percent A value between 1 and 100, namely, 1% up to 100%.
                 * @return #BRIGHTNESS_OUT_OF_RANGE or #NO_WRN.
                 * @remark If parameter is greater than 100 or less than 1, it sets the brightness to default value (50%).
                 */
                Warning setBrightness(uint8_t);

                /**
                 * Write an integer into buffer.
                 * Numbers with more digits than the display aren't shown.
                 * @param number an integer number.
                 * @return #DISPLAY_OVERFLOW or #NO_WRN.
                 */
                Warning write(int);

                /**
                 * Write a float into buffer.
                 * It always suppresses leading zeros and rounds number.
                 * @param number a float number.
                 * @param prec specifies float-format precision. It must be between 1 and display's amount of digits.
                 * @return #DISPLAY_OVERFLOW|#PRECISION_OUT_OF_RANGE
                 * @return #DISPLAY_OVERFLOW|#PRECISION_FORCED_TO_ONE
                 * @return #DISPLAY_OVERFLOW or #NO_WRN. 
                 * @remark Numbers with more digits than the display aren't shown.
                 * @remark If fractional part is zero, it sets precision to one.
                 */
                Warning write(float, uint8_t);

                /**
                 * Write a string into buffer.
                 * @param msg a c_string text.
                 * @return #DISPLAY_OVERFLOW or #NO_WRN
                 * @remark Strings with more characters than the display aren't shown.
                 * @remark If string's decimal points exceeds the amount of decimal points of the display, the trailing decimal points are truncated.
                 */
                Warning write(const char msg[]);

                /**
                 * Refresh display.
                 */
                void update();

        };
    }
}

#endif