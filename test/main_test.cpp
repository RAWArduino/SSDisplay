#include <unity.h>
#include "../lib/SSDisplay/SSDisplay.hpp"

using RAW::Display::SSDisplay;

uint8_t digits[]={41,39,35};
uint8_t segments[]={45,43,33,31,47,27,37,29};

namespace CC{ //Common Cathode
void all_is_off(){
    uint8_t i;
    for(i=0;i<3;i++)TEST_ASSERT_TRUE(digitalRead(digits[i]));
    for(i=0;i<8;i++)TEST_ASSERT_FALSE(digitalRead(segments[i]));
}

void segments_are_off(){
    for(uint8_t i=0;i<8;i++)TEST_ASSERT_FALSE(digitalRead(segments[i]));
}

void test_for_clean(){
    SSDisplay dsp(3, digits, 8, segments, true);
    dsp.clean();
    all_is_off();
}

void test_write_number_12_with_leading_zeros(){
    SSDisplay dsp(3, digits, 8, segments, true);
    dsp.write(12);
    dsp.update();
    delay(2);
    // first digit should be showing zero
    TEST_ASSERT_FALSE(digitalRead(41));
    TEST_ASSERT_TRUE(digitalRead(39));
    TEST_ASSERT_TRUE(digitalRead(35));

    TEST_ASSERT_TRUE(digitalRead(43));
    TEST_ASSERT_TRUE(digitalRead(33));
    TEST_ASSERT_TRUE(digitalRead(31));
    TEST_ASSERT_TRUE(digitalRead(47));
    TEST_ASSERT_TRUE(digitalRead(27));
    TEST_ASSERT_TRUE(digitalRead(37));
    TEST_ASSERT_FALSE(digitalRead(29));
    dsp.update();
    delay(2);
    // turn off first digit
    all_is_off();
    dsp.update();
    delay(2);
    dsp.update();
    delay(2);

    //second digit should be showing one
    TEST_ASSERT_TRUE(digitalRead(41));
    TEST_ASSERT_FALSE(digitalRead(39));
    TEST_ASSERT_TRUE(digitalRead(35));

    TEST_ASSERT_FALSE(digitalRead(43));
    TEST_ASSERT_TRUE(digitalRead(33));
    TEST_ASSERT_TRUE(digitalRead(31));
    TEST_ASSERT_FALSE(digitalRead(47));
    TEST_ASSERT_FALSE(digitalRead(27));
    TEST_ASSERT_FALSE(digitalRead(37));
    TEST_ASSERT_FALSE(digitalRead(29));
    dsp.update();
    delay(2);
    // turn off second digit
    all_is_off();
    dsp.update();
    delay(2);
    dsp.update();
    delay(2);

    // third digit should be showing two
    TEST_ASSERT_TRUE(digitalRead(41));
    TEST_ASSERT_TRUE(digitalRead(39));
    TEST_ASSERT_FALSE(digitalRead(35));

    TEST_ASSERT_TRUE(digitalRead(43));
    TEST_ASSERT_TRUE(digitalRead(33));
    TEST_ASSERT_FALSE(digitalRead(31));
    TEST_ASSERT_TRUE(digitalRead(47));
    TEST_ASSERT_TRUE(digitalRead(27));
    TEST_ASSERT_FALSE(digitalRead(37));
    TEST_ASSERT_TRUE(digitalRead(29));
    dsp.update();
    delay(2);
    // turn off third digit
    all_is_off();
}

void test_write_number_12_without_leading_zeros(){
    SSDisplay dsp(3, digits, 8, segments, true);
    dsp.suppressLeadingZeros();
    dsp.write(12);
    dsp.update();
    delay(2);
    // first digit should be off
    TEST_ASSERT_FALSE(digitalRead(41));
    TEST_ASSERT_TRUE(digitalRead(39));
    TEST_ASSERT_TRUE(digitalRead(35));
    segments_are_off();
    dsp.update();
    delay(2);
    all_is_off();
    dsp.update();
    delay(2);

    dsp.update();
    delay(2);
    //second digit should be showing one
    TEST_ASSERT_TRUE(digitalRead(41));
    TEST_ASSERT_FALSE(digitalRead(39));
    TEST_ASSERT_TRUE(digitalRead(35));

    TEST_ASSERT_FALSE(digitalRead(43));
    TEST_ASSERT_TRUE(digitalRead(33));
    TEST_ASSERT_TRUE(digitalRead(31));
    TEST_ASSERT_FALSE(digitalRead(47));
    TEST_ASSERT_FALSE(digitalRead(27));
    TEST_ASSERT_FALSE(digitalRead(37));
    TEST_ASSERT_FALSE(digitalRead(29));
    dsp.update();
    delay(2);
    // turn off second digit
    all_is_off();
    dsp.update();
    delay(2);
    
    dsp.update();
    delay(2);
    // third digit should be showing two
    TEST_ASSERT_TRUE(digitalRead(41));
    TEST_ASSERT_TRUE(digitalRead(39));
    TEST_ASSERT_FALSE(digitalRead(35));

    TEST_ASSERT_TRUE(digitalRead(43));
    TEST_ASSERT_TRUE(digitalRead(33));
    TEST_ASSERT_FALSE(digitalRead(31));
    TEST_ASSERT_TRUE(digitalRead(47));
    TEST_ASSERT_TRUE(digitalRead(27));
    TEST_ASSERT_FALSE(digitalRead(37));
    TEST_ASSERT_TRUE(digitalRead(29));
    dsp.update();
    delay(2);
    // turn off third digit
    all_is_off();
}

} // End CC

namespace CA{ //Common Anode
void all_is_off(){
    uint8_t i;
    for(i=0;i<3;i++)TEST_ASSERT_FALSE(digitalRead(digits[i]));
    for(i=0;i<8;i++)TEST_ASSERT_TRUE(digitalRead(segments[i]));
}

void segments_are_off(){
    for(uint8_t i=0;i<8;i++)TEST_ASSERT_TRUE(digitalRead(segments[i]));
}

void test_for_clean(){
    SSDisplay dsp(3, digits, 8, segments, false);
    dsp.clean();
    all_is_off();
}

void test_write_number_12_with_leading_zeros(){
    SSDisplay dsp(3, digits, 8, segments, false);
    dsp.write(12);
    dsp.update();
    delay(2);
    // first digit should be showing zero
    TEST_ASSERT_TRUE(digitalRead(41));
    TEST_ASSERT_FALSE(digitalRead(39));
    TEST_ASSERT_FALSE(digitalRead(35));

    TEST_ASSERT_FALSE(digitalRead(43));
    TEST_ASSERT_FALSE(digitalRead(33));
    TEST_ASSERT_FALSE(digitalRead(31));
    TEST_ASSERT_FALSE(digitalRead(47));
    TEST_ASSERT_FALSE(digitalRead(27));
    TEST_ASSERT_FALSE(digitalRead(37));
    TEST_ASSERT_TRUE(digitalRead(29));
    dsp.update();
    delay(2);
    // turn off first digit
    all_is_off();
    dsp.update();
    delay(2);
    dsp.update();
    delay(2);

    //second digit should be showing one
    TEST_ASSERT_FALSE(digitalRead(41));
    TEST_ASSERT_TRUE(digitalRead(39));
    TEST_ASSERT_FALSE(digitalRead(35));

    TEST_ASSERT_TRUE(digitalRead(43));
    TEST_ASSERT_FALSE(digitalRead(33));
    TEST_ASSERT_FALSE(digitalRead(31));
    TEST_ASSERT_TRUE(digitalRead(47));
    TEST_ASSERT_TRUE(digitalRead(27));
    TEST_ASSERT_TRUE(digitalRead(37));
    TEST_ASSERT_TRUE(digitalRead(29));
    dsp.update();
    delay(2);
    // turn off second digit
    all_is_off();
    dsp.update();
    delay(2);
    dsp.update();
    delay(2);

    // third digit should be showing two
    TEST_ASSERT_FALSE(digitalRead(41));
    TEST_ASSERT_FALSE(digitalRead(39));
    TEST_ASSERT_TRUE(digitalRead(35));

    TEST_ASSERT_FALSE(digitalRead(43));
    TEST_ASSERT_FALSE(digitalRead(33));
    TEST_ASSERT_TRUE(digitalRead(31));
    TEST_ASSERT_FALSE(digitalRead(47));
    TEST_ASSERT_FALSE(digitalRead(27));
    TEST_ASSERT_TRUE(digitalRead(37));
    TEST_ASSERT_FALSE(digitalRead(29));
    dsp.update();
    delay(2);
    // turn off third digit
    all_is_off();
}

void test_write_number_12_without_leading_zeros(){
    SSDisplay dsp(3, digits, 8, segments, false);
    dsp.suppressLeadingZeros();
    dsp.write(12);
    dsp.update();
    delay(2);
    // first digit should be off
    TEST_ASSERT_TRUE(digitalRead(41));
    TEST_ASSERT_FALSE(digitalRead(39));
    TEST_ASSERT_FALSE(digitalRead(35));
    segments_are_off();
    dsp.update();
    delay(2);
    all_is_off();
    dsp.update();
    delay(2);

    dsp.update();
    delay(2);
    //second digit should be showing one
    TEST_ASSERT_FALSE(digitalRead(41));
    TEST_ASSERT_TRUE(digitalRead(39));
    TEST_ASSERT_FALSE(digitalRead(35));

    TEST_ASSERT_TRUE(digitalRead(43));
    TEST_ASSERT_FALSE(digitalRead(33));
    TEST_ASSERT_FALSE(digitalRead(31));
    TEST_ASSERT_TRUE(digitalRead(47));
    TEST_ASSERT_TRUE(digitalRead(27));
    TEST_ASSERT_TRUE(digitalRead(37));
    TEST_ASSERT_TRUE(digitalRead(29));
    dsp.update();
    delay(2);
    // turn off second digit
    all_is_off();
    dsp.update();
    delay(2);
    
    dsp.update();
    delay(2);
    // third digit should be showing two
    TEST_ASSERT_FALSE(digitalRead(41));
    TEST_ASSERT_FALSE(digitalRead(39));
    TEST_ASSERT_TRUE(digitalRead(35));

    TEST_ASSERT_FALSE(digitalRead(43));
    TEST_ASSERT_FALSE(digitalRead(33));
    TEST_ASSERT_TRUE(digitalRead(31));
    TEST_ASSERT_FALSE(digitalRead(47));
    TEST_ASSERT_FALSE(digitalRead(27));
    TEST_ASSERT_TRUE(digitalRead(37));
    TEST_ASSERT_FALSE(digitalRead(29));
    dsp.update();
    delay(2);
    // turn off third digit
    all_is_off();
}

} // End CA

void test_delete_SSDisplay_pointer(){
    SSDisplay* pdsp=new SSDisplay(3, digits, 8, segments, true);
    pdsp->write("aus");
    delete pdsp;
}

void setup(){
    UNITY_BEGIN();
    RUN_TEST(CC::test_for_clean);
    RUN_TEST(CC::test_write_number_12_with_leading_zeros);
    RUN_TEST(CC::test_write_number_12_without_leading_zeros);
    RUN_TEST(CA::test_for_clean);
    RUN_TEST(CA::test_write_number_12_with_leading_zeros);
    RUN_TEST(CA::test_write_number_12_without_leading_zeros);
    RUN_TEST(test_delete_SSDisplay_pointer);
    UNITY_END();
}

void loop(){}