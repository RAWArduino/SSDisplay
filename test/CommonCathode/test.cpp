#include <unity.h>
#include <SSDisplay.hpp>

using RAW::Display::SSDisplay;
using RAW::Display::Warning;

uint8_t digits[]={41,39,35};
uint8_t segments[]={45,43,33,31,47,27,37,29};

void all_is_off(){
    uint8_t i;
    for(i=0;i<3;i++)TEST_ASSERT_TRUE(digitalRead(digits[i]));
    for(i=0;i<8;i++)TEST_ASSERT_FALSE(digitalRead(segments[i]));
}

void only_dot_is_on(){
    TEST_ASSERT_TRUE(digitalRead(45));
    for(uint8_t i=1;i<8;i++)TEST_ASSERT_FALSE(digitalRead(segments[i]));
}

void segments_are_off(){
    for(uint8_t i=0;i<8;i++)TEST_ASSERT_FALSE(digitalRead(segments[i]));
}

void next(SSDisplay& dsp){
    dsp.update();
    delay(2);
}

void only_two_dashes(SSDisplay& dsp){
    next(dsp);
    TEST_ASSERT_FALSE(digitalRead(39));
    TEST_ASSERT_TRUE(digitalRead(35));
    
    TEST_ASSERT_FALSE(digitalRead(45));
    TEST_ASSERT_FALSE(digitalRead(43));
    TEST_ASSERT_FALSE(digitalRead(33));
    TEST_ASSERT_FALSE(digitalRead(31));
    TEST_ASSERT_FALSE(digitalRead(47));
    TEST_ASSERT_FALSE(digitalRead(27));
    TEST_ASSERT_FALSE(digitalRead(37));
    TEST_ASSERT_TRUE(digitalRead(29));
    next(dsp);
    all_is_off();
    next(dsp);

    next(dsp);
    TEST_ASSERT_TRUE(digitalRead(39));
    TEST_ASSERT_FALSE(digitalRead(35));
    
    TEST_ASSERT_FALSE(digitalRead(45));
    TEST_ASSERT_FALSE(digitalRead(43));
    TEST_ASSERT_FALSE(digitalRead(33));
    TEST_ASSERT_FALSE(digitalRead(31));
    TEST_ASSERT_FALSE(digitalRead(47));
    TEST_ASSERT_FALSE(digitalRead(27));
    TEST_ASSERT_FALSE(digitalRead(37));
    TEST_ASSERT_TRUE(digitalRead(29));
    next(dsp);
    all_is_off();
    next(dsp);
}

void test_for_clean(){
    SSDisplay dsp(3, digits, 8, segments, true);
    dsp.clean();
    all_is_off();
}

void test_float_display_overflow(){
    SSDisplay dsp(2,digits+1,8,segments,true);
    Warning wrn=dsp.write(-5.73f,2);
    TEST_ASSERT_TRUE((wrn&Warning::PRECISION_OUT_OF_RANGE)&&(wrn&Warning::DISPLAY_OVERFLOW));
    only_two_dashes(dsp);
}

void test_int_display_overflow(){
    SSDisplay dsp(2,digits+1,8,segments,true);
    TEST_ASSERT_EQUAL(Warning::DISPLAY_OVERFLOW,dsp.write(100));
    only_two_dashes(dsp);
}

void test_text_display_overflow(){
    SSDisplay dsp(2,digits+1,8,segments,true);
    TEST_ASSERT_EQUAL(Warning::DISPLAY_OVERFLOW, dsp.write("abc"));
    only_two_dashes(dsp);
}

void test_write_number_12_with_leading_zeros(){
    SSDisplay dsp(3, digits, 8, segments, true);
    TEST_ASSERT_EQUAL(Warning::NO_WRN,dsp.write(12));
    next(dsp);
    // first digit should be showing zero
    TEST_ASSERT_FALSE(digitalRead(41));
    TEST_ASSERT_TRUE(digitalRead(39));
    TEST_ASSERT_TRUE(digitalRead(35));

    TEST_ASSERT_FALSE(digitalRead(45));
    TEST_ASSERT_TRUE(digitalRead(43));
    TEST_ASSERT_TRUE(digitalRead(33));
    TEST_ASSERT_TRUE(digitalRead(31));
    TEST_ASSERT_TRUE(digitalRead(47));
    TEST_ASSERT_TRUE(digitalRead(27));
    TEST_ASSERT_TRUE(digitalRead(37));
    TEST_ASSERT_FALSE(digitalRead(29));
    next(dsp);
    // turn off first digit
    all_is_off();
    next(dsp);
    next(dsp);

    //second digit should be showing one
    TEST_ASSERT_TRUE(digitalRead(41));
    TEST_ASSERT_FALSE(digitalRead(39));
    TEST_ASSERT_TRUE(digitalRead(35));

    TEST_ASSERT_FALSE(digitalRead(45));
    TEST_ASSERT_FALSE(digitalRead(43));
    TEST_ASSERT_TRUE(digitalRead(33));
    TEST_ASSERT_TRUE(digitalRead(31));
    TEST_ASSERT_FALSE(digitalRead(47));
    TEST_ASSERT_FALSE(digitalRead(27));
    TEST_ASSERT_FALSE(digitalRead(37));
    TEST_ASSERT_FALSE(digitalRead(29));
    next(dsp);
    // turn off second digit
    all_is_off();
    next(dsp);
    next(dsp);

    // third digit should be showing two
    TEST_ASSERT_TRUE(digitalRead(41));
    TEST_ASSERT_TRUE(digitalRead(39));
    TEST_ASSERT_FALSE(digitalRead(35));

    TEST_ASSERT_FALSE(digitalRead(45));
    TEST_ASSERT_TRUE(digitalRead(43));
    TEST_ASSERT_TRUE(digitalRead(33));
    TEST_ASSERT_FALSE(digitalRead(31));
    TEST_ASSERT_TRUE(digitalRead(47));
    TEST_ASSERT_TRUE(digitalRead(27));
    TEST_ASSERT_FALSE(digitalRead(37));
    TEST_ASSERT_TRUE(digitalRead(29));
    next(dsp);
    // turn off third digit
    all_is_off();
}

void test_write_number_12_without_leading_zeros(){
    SSDisplay dsp(3, digits, 8, segments, true);
    dsp.suppressLeadingZeros();
    TEST_ASSERT_EQUAL(Warning::NO_WRN,dsp.write(12));
    next(dsp);
    // first digit should be off
    TEST_ASSERT_FALSE(digitalRead(41));
    TEST_ASSERT_TRUE(digitalRead(39));
    TEST_ASSERT_TRUE(digitalRead(35));
    segments_are_off();
    next(dsp);
    all_is_off();
    next(dsp);

    next(dsp);
    //second digit should be showing one
    TEST_ASSERT_TRUE(digitalRead(41));
    TEST_ASSERT_FALSE(digitalRead(39));
    TEST_ASSERT_TRUE(digitalRead(35));

    TEST_ASSERT_FALSE(digitalRead(45));
    TEST_ASSERT_FALSE(digitalRead(43));
    TEST_ASSERT_TRUE(digitalRead(33));
    TEST_ASSERT_TRUE(digitalRead(31));
    TEST_ASSERT_FALSE(digitalRead(47));
    TEST_ASSERT_FALSE(digitalRead(27));
    TEST_ASSERT_FALSE(digitalRead(37));
    TEST_ASSERT_FALSE(digitalRead(29));
    next(dsp);
    // turn off second digit
    all_is_off();
    next(dsp);
    
    next(dsp);
    // third digit should be showing two
    TEST_ASSERT_TRUE(digitalRead(41));
    TEST_ASSERT_TRUE(digitalRead(39));
    TEST_ASSERT_FALSE(digitalRead(35));

    TEST_ASSERT_FALSE(digitalRead(45));
    TEST_ASSERT_TRUE(digitalRead(43));
    TEST_ASSERT_TRUE(digitalRead(33));
    TEST_ASSERT_FALSE(digitalRead(31));
    TEST_ASSERT_TRUE(digitalRead(47));
    TEST_ASSERT_TRUE(digitalRead(27));
    TEST_ASSERT_FALSE(digitalRead(37));
    TEST_ASSERT_TRUE(digitalRead(29));
    next(dsp);
    // turn off third digit
    all_is_off();
}

void test_three_dots(){
    SSDisplay dsp(3, digits, 8, segments, true);
    TEST_ASSERT_EQUAL(Warning::NO_WRN, dsp.write(" . . ."));
    
    next(dsp);
    TEST_ASSERT_FALSE(digitalRead(41));
    TEST_ASSERT_TRUE(digitalRead(39));
    TEST_ASSERT_TRUE(digitalRead(35));
    only_dot_is_on();
    next(dsp);
    all_is_off();
    next(dsp);

    next(dsp);
    TEST_ASSERT_TRUE(digitalRead(41));
    TEST_ASSERT_FALSE(digitalRead(39));
    TEST_ASSERT_TRUE(digitalRead(35));
    only_dot_is_on();
    next(dsp);
    all_is_off();
    next(dsp);

    next(dsp);
    TEST_ASSERT_TRUE(digitalRead(41));
    TEST_ASSERT_TRUE(digitalRead(39));
    TEST_ASSERT_FALSE(digitalRead(35));
    only_dot_is_on();
    next(dsp);
    all_is_off();
    next(dsp);

}

void test_two_digits_dots_disabled(){
    SSDisplay dsp(2,digits+1,7,segments+1, true);
    TEST_ASSERT_EQUAL(Warning::NO_WRN, dsp.write(" . ."));
    
    next(dsp);
    TEST_ASSERT_FALSE(digitalRead(39));
    TEST_ASSERT_TRUE(digitalRead(35));
    segments_are_off();
    next(dsp);
    all_is_off();
    next(dsp);

    next(dsp);
    TEST_ASSERT_TRUE(digitalRead(39));
    TEST_ASSERT_FALSE(digitalRead(35));
    segments_are_off();
    next(dsp);
    all_is_off();
    next(dsp);
}

void test_float_round(){
    SSDisplay dsp(2,digits+1,8,segments, true);
    TEST_ASSERT_EQUAL(Warning::NO_WRN, dsp.write(0.56f,1));

    next(dsp);
    TEST_ASSERT_FALSE(digitalRead(39));
    TEST_ASSERT_TRUE(digitalRead(35));
    // should be "0."
    TEST_ASSERT_TRUE(digitalRead(45));
    TEST_ASSERT_TRUE(digitalRead(43));
    TEST_ASSERT_TRUE(digitalRead(33));
    TEST_ASSERT_TRUE(digitalRead(31));
    TEST_ASSERT_TRUE(digitalRead(47));
    TEST_ASSERT_TRUE(digitalRead(27));
    TEST_ASSERT_TRUE(digitalRead(37));
    TEST_ASSERT_FALSE(digitalRead(29));
    next(dsp);
    all_is_off();
    next(dsp);

    next(dsp);
    TEST_ASSERT_TRUE(digitalRead(39));
    TEST_ASSERT_FALSE(digitalRead(35));
    // should be 6
    TEST_ASSERT_FALSE(digitalRead(45));
    TEST_ASSERT_TRUE(digitalRead(43));
    TEST_ASSERT_FALSE(digitalRead(33));
    TEST_ASSERT_TRUE(digitalRead(31));
    TEST_ASSERT_TRUE(digitalRead(47));
    TEST_ASSERT_TRUE(digitalRead(27));
    TEST_ASSERT_TRUE(digitalRead(37));
    TEST_ASSERT_TRUE(digitalRead(29));
    next(dsp);
    all_is_off();
    next(dsp);
}

void when_fractional_is_zero_precision_is_forced_to_one(){
    SSDisplay dsp(3,digits,8,segments, true);
    TEST_ASSERT_EQUAL(Warning::PRECISION_FORCED_TO_ONE, dsp.write(2.0f,2));

    next(dsp);
    TEST_ASSERT_FALSE(digitalRead(41));
    TEST_ASSERT_TRUE(digitalRead(39));
    TEST_ASSERT_TRUE(digitalRead(35));

    segments_are_off();
    next(dsp);
    all_is_off();
    next(dsp);

    next(dsp);
    TEST_ASSERT_TRUE(digitalRead(41));
    TEST_ASSERT_FALSE(digitalRead(39));
    TEST_ASSERT_TRUE(digitalRead(35));

    TEST_ASSERT_TRUE(digitalRead(45));
    TEST_ASSERT_TRUE(digitalRead(43));
    TEST_ASSERT_TRUE(digitalRead(33));
    TEST_ASSERT_FALSE(digitalRead(31));
    TEST_ASSERT_TRUE(digitalRead(47));
    TEST_ASSERT_TRUE(digitalRead(27));
    TEST_ASSERT_FALSE(digitalRead(37));
    TEST_ASSERT_TRUE(digitalRead(29));
    next(dsp);
    all_is_off();
    next(dsp);

    next(dsp);
    TEST_ASSERT_TRUE(digitalRead(41));
    TEST_ASSERT_TRUE(digitalRead(39));
    TEST_ASSERT_FALSE(digitalRead(35));

    TEST_ASSERT_FALSE(digitalRead(45));
    TEST_ASSERT_TRUE(digitalRead(43));
    TEST_ASSERT_TRUE(digitalRead(33));
    TEST_ASSERT_TRUE(digitalRead(31));
    TEST_ASSERT_TRUE(digitalRead(47));
    TEST_ASSERT_TRUE(digitalRead(27));
    TEST_ASSERT_TRUE(digitalRead(37));
    TEST_ASSERT_FALSE(digitalRead(29));
    next(dsp);
    all_is_off();
    next(dsp);

}


void setup(){
    UNITY_BEGIN();
    RUN_TEST(test_for_clean);
    RUN_TEST(test_float_display_overflow);
    RUN_TEST(test_int_display_overflow);
    RUN_TEST(test_text_display_overflow);
    RUN_TEST(test_write_number_12_with_leading_zeros);
    RUN_TEST(test_write_number_12_without_leading_zeros);
    RUN_TEST(test_three_dots);
    RUN_TEST(test_two_digits_dots_disabled);
    RUN_TEST(test_float_round);
    RUN_TEST(when_fractional_is_zero_precision_is_forced_to_one);
    UNITY_END();
}

void loop(){}