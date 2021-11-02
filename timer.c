#include <avr/io.h>

#include "timer.h"
#include "led.h"

volatile uint8_t counter = 0; 

void timer_init() {
	DDRB = 0xff;

	//Set CTC(Clear timer on compare match) in (Timer/Counter Control Register A)
	TCCR0A |= (1<<WGM01); //Set WGM01 to 1
	TCCR0A &= ~(1<<WGM00); //Set WGM00 to 0

	//Calculation for getting a time period of 10ms: 
	//(16000000/((155+1)*1024)) = 100.160... hz
	OCR0A = 156; //The TOP-value for compare matching with TCNT0

	//Set Timer Interrupt Mask Register
	//TIMSK0 = (1<<OCIE0A);  //Set Output Compare Interrupt Enable Match A to 1

	//Set prescale to 1024 in register(Timer/Counter Control Register B)
	TCCR0B &= ~(1<<WGM02); //Set WGM02 to 0
	TCCR0B |= (1<<CS02); //Set CS02 to 1
	TCCR0B &= ~(1<<CS01); //Set CS01 to 0
	TCCR0B |= (1<<CS00); //and CS00 to 1

	TCNT0 = 0; //Start timer
}

void checkCounter(void) {
	
	if(TCNT0 >= OCR0A) { //If statement to check if timer has passed top value
		counter++; //Increment global variable
		counter %= 100; //Modulus 100 for more accurate count
	}
	if (counter == 10) { //If global variable has reached a count of 10, turn on blue light
		blueLight();
	} else {
		led_off();
	}
}
