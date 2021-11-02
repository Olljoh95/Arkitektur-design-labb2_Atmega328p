#include <avr/io.h>

#include "timer.h"
#include "led.h"

volatile uint8_t counter = 0; 

void timer_init() {
	//Set Fast PWM in (Timer/Counter Control Register A)	
	TCCR0A |= (1<<WGM01); //Set WGM01 to 1
	TCCR0A &= (1<<WGM00); //Set WGM00 to 1
	//Clear OC0A on Compare match, set OC0A at bottom(non-inverting mode)
	//TCCR0A &= ~(1<<COM0A0); //Set COM0A0 to 0
	TCCR0A &= (1<<COM0A1); //Set COM0A1 to 1
	
	//(16000000/((254+1)*64)) = 980.3921568627451 Hz
	//OCR0A = 254; //The TOP-value for compare matching with TCNT0

	//Set prescale to 64 in register(Timer/Counter Control Register B)
	TCCR0B &= ~(1<<WGM02); //Set WGM02 to 0
	TCCR0B &= ~(1<<CS02); //Set CS02 to 0
	TCCR0B |= (1<<CS01); //Set CS01 to 1
	TCCR0B &= (1<<CS00); //and CS00 to 1

	TCNT0 = 0; //Start timer
}

void checkCounter(void) {
	if(TCNT0 >= 255) { //If statement to check if timer has passed top value
		counter++; //Increment global variable
		counter %= 100; //Modulus 100 for more accurate count
	}
	if (counter == 10) { //If global variable has reached a count of 10, turn on blue light
		blueLight();
	} else {
		led_off();
	}
}