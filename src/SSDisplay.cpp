#include "SSDisplay.hpp"

using RAW::Display::SSDisplay;
using RAW::Display::Warning;

SSDisplay::SSDisplay(uint8_t dig_sz, const uint8_t common[], uint8_t seg_sz, const uint8_t segment[], bool isCommonCathode):
digSz(dig_sz),segSz(seg_sz),digitOn(digOn),segmentOn(segOn)
{
	uint8_t i;
    buffer=new uint8_t[digSz];
	memset(buffer,0x00,digSz);
	this->common=new uint8_t[digSz];
	memcpy(this->common,common,digSz);
	this->segment=new uint8_t[segSz];
	setBlinkInterval(250);
	setBrightness(50);

	// store segments in reverse order.
	for(i=0;i<segSz;i++)this->segment[segSz-1-i]=segment[i];

	temp_char=new char[digSz+3];
	memset(temp_char,0x00,digSz+2);

	// arduino sprintf doesn't support the * template
	memset(integer_template,'\0',7);
	strcpy(integer_template,"%0");
	itoa(digSz,integer_template+2,10);
	strcat(integer_template,"d");

	// default is common cathode
	digOn=LOW;
	segOn=HIGH;

	if(!isCommonCathode){
		// common anode
		digOn=HIGH;
		segOn=LOW;
	}
	
    for(i=0;i<segSz;i++)pinMode(this->segment[i],OUTPUT);
    for(i=0;i<digSz;i++)pinMode(this->common[i],OUTPUT);

	this->clean();
}


SSDisplay::~SSDisplay(){
	delete[] buffer;
	delete[] temp_char;
	delete[] segment;
	delete[] common;
}

void SSDisplay::suppressLeadingZeros(){
	// arduino sprintf doesn't support the * template
	integer_template[0]='%';
	itoa(digSz,integer_template+1,10);
	strcat(integer_template,"d");
}

Warning SSDisplay::setBrightness(uint8_t percent){
	Warning wrn=NO_WRN;
	if(percent==0 || percent>100){percent=50; wrn=BRIGHTNESS_OUT_OF_RANGE;}
	dispOnTime=percent*20;
	return wrn;
}


Warning SSDisplay::write(const char msg[]){
	this->clean();
	String check=String(msg);
	check.replace(".",""); check.replace(",","");

	if(check.length()<=0 || check.length()>digSz){
		uint8_t MINUS=pgm_read_byte_near(CHARACTERS);
		for(uint8_t i=0;i<digSz;i++)buffer[i]=MINUS;
		
		return DISPLAY_OVERFLOW;
	}
	
	uint8_t digit=0;
	for(uint8_t i=0;i<(2*digSz)&&i<strlen(msg);i++){
		switch((uint8_t)msg[i]){
			case '3':
				buffer[digit++]=pgm_read_byte_near(NUMBERS+3);
				break;
				
			case '4':
				buffer[digit++]=pgm_read_byte_near(NUMBERS+4);
				break;
				
			case '7':
				buffer[digit++]=pgm_read_byte_near(NUMBERS+7);
				break;
			
			case '8':
				buffer[digit++]=pgm_read_byte_near(NUMBERS+8);
				break;
				
			case '9':
				buffer[digit++]=pgm_read_byte_near(NUMBERS+9);
				break;

			case ']':
			case ')':
				buffer[digit++]=pgm_read_byte_near(CHARACTERS+1);
				break;

			case 'a':
			case 'A':
				buffer[digit++]=pgm_read_byte_near(CHARACTERS+2);
				break;
				
			case 'b':
			case 'B':
				buffer[digit++]=pgm_read_byte_near(CHARACTERS+3);
				break;
				
			case 'c':
			case 'C':
			case '[':
			case '(':
				buffer[digit++]=pgm_read_byte_near(CHARACTERS+4);
				break;
				
			case 'd':
			case 'D':
				buffer[digit++]=pgm_read_byte_near(CHARACTERS+5);;
				break;
				
			case 'e':
			case 'E':
				buffer[digit++]=pgm_read_byte_near(CHARACTERS+6);
				break;
				
			case 'f':
			case 'F':
				buffer[digit++]=pgm_read_byte_near(CHARACTERS+7);
				break;
				
			case 'g':
			case 'G':
			case '6':
				buffer[digit++]=pgm_read_byte_near(NUMBERS+6);
				break;
				
			case 'h':
				buffer[digit++]=pgm_read_byte_near(CHARACTERS+8);
				break;
				
			case 'H':
				buffer[digit++]=pgm_read_byte_near(CHARACTERS+9);
				break;
				
			case 'i':
			case 'I':
			case '1':
				buffer[digit++]=pgm_read_byte_near(NUMBERS+1);
				break;

			case 'j':
			case 'J':
				buffer[digit++]=pgm_read_byte_near(CHARACTERS+10);
				break;
				
			case 'l':
			case 'L':
				buffer[digit++]=pgm_read_byte_near(CHARACTERS+11);
				break;
				
			case 'N':
			case 'n':
				buffer[digit++]=pgm_read_byte_near(CHARACTERS+12);
				break;
				
			case 'o':
			case 'O':
			case '0':
				buffer[digit++]=pgm_read_byte_near(NUMBERS);
				break;
			
			case 'p':
			case 'P':
				buffer[digit++]=pgm_read_byte_near(CHARACTERS+13);
				break;
			
			case 'r':
			case 'R':
				buffer[digit++]=pgm_read_byte_near(CHARACTERS+14);
				break;
				
			case 's':
			case 'S':
			case '5':
				buffer[digit++]=pgm_read_byte_near(NUMBERS+5);
				break;
				
			case 'u':
			case 'U':
				buffer[digit++]=pgm_read_byte_near(CHARACTERS+15);
				break;
				
			case 'z':
			case 'Z':
			case '2':
				buffer[digit++]=pgm_read_byte_near(NUMBERS+2);
				break;
			
			case '-':
				buffer[digit++]=pgm_read_byte_near(CHARACTERS);
				break;
				
			case ',':
			case '.':
                buffer[digit-1]=0x80|buffer[digit-1];
				break;
					
			default:
				digit++;
		}
	}

	return NO_WRN;
}


Warning SSDisplay::write(float number, uint8_t prec){
	Warning wrn=NO_WRN;
	if((number<0.0f?-number:number)-abs((int)number)==0.0f){prec=1; wrn=PRECISION_FORCED_TO_ONE;}
	else if(prec==0||prec>=digSz){prec=digSz-1; wrn=PRECISION_OUT_OF_RANGE;}
	dtostrf(number,digSz+1,prec,temp_char);
	return wrn|this->write(temp_char);
}

Warning SSDisplay::write(int number){
	memset(temp_char,'\0',digSz+2);
	sprintf(temp_char,integer_template,number);
    return this->write(temp_char);
}


void SSDisplay::lightUp(){
    for(uint8_t i=0;i<digSz;i++)buffer[i]=0xFF;
	unsigned long time=millis();
	while(millis()-time < 2000)update();
	clean();
}

void SSDisplay::blink(uint8_t amnt){
	blinkAmt=amnt;
	blinkState=0;
    lastBlinkTime=millis();
}

Warning SSDisplay::setBlinkInterval(uint16_t interval){
	Warning wrn=NO_WRN;
	if(interval<120){interval=120; wrn=INTERVAL_OUT_OF_RANGE;}
	blinkInterval=interval;
	return wrn;
}


void SSDisplay::update(){
    if(blinkAmt){
		switch(blinkState){
		case 0:
			for(uint8_t i=0;i<digSz;i++)digitalWrite(common[i], !digOn);
			for(uint8_t i=0;i<segSz;i++)digitalWrite(segment[i], !segOn);
			blinkState=1;
			lastBlinkTime=millis();
			break;

		case 1:
			if(millis()-lastBlinkTime<blinkInterval)return;
			blinkState=2;
			lastBlinkTime=millis();
			break;
		
		case 2:
			if(millis()-lastBlinkTime<blinkInterval)break;
			blinkState=0;
			blinkAmt--;
			lastBlinkTime=millis();
			break;
		
		default:
			break;
		}
	}

	uint8_t j;
	switch (internalState){
	case 1: // Turn on digits
		digitalWrite(common[currDigit], digOn);
		for(j=0;j<segSz;j++){
			digitalWrite(segment[j],
				(!digOn)?(buffer[currDigit]>>j)&0x01 : !((buffer[currDigit]>>j)&0x01)
			);
		}
		onShow();
		internalState=2;
		lastDispTime=micros();
		break;

	case 2: // Turn off digits
		if(micros()-lastDispTime<dispOnTime)return;
		for(j=0;j<segSz;j++)digitalWrite(segment[j], !segOn);
		digitalWrite(common[currDigit], !digOn);
		onHide();
		internalState=3;
		lastDispTime=micros();
		break;

	case 3: // Next digit; goto first state
		if((micros()-lastDispTime)<(2000-dispOnTime))return;
		currDigit=(currDigit+1)%digSz;
		internalState=1;
		break;
	
	default:
		break;
	}

}


void SSDisplay::clean(){
	uint8_t i;
	currDigit=0;
	internalState=1;
	blinkState=blinkAmt=0;
	for(i=0;i<digSz;i++){
		buffer[i]=0x00;
		digitalWrite(common[i], !digOn);
	}

	for(i=0;i<segSz;i++)digitalWrite(segment[i], !segOn);
}