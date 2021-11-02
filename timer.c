#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer.h"
#include "led.h"

volatile float dutyCycle = 0; 

void timer_init() {
	DDRD = (1 << PORTD6); //Enable led on digital pin 6(using 220ohm resistor)

	//Clear OC0A on Compare match, set OC0A at bottom(non-inverting mode)
	TCCR0A |= (1<<COM0A1); //Set COM0A1 to 1
	TCCR0A &= ~(1<<COM0A0); //Set COM0A0 to 0
	//Set Fast PWM in (Timer/Counter Control Register A, Mode 3)
	TCCR0A |= (1<<WGM00); //Set WGM00 to 1	
	TCCR0A |= (1<<WGM01); //Set WGM01 to 1
	
	
	TIMSK0 = (1<<TOIE0); //Time overflow interrupt flag to 1

	OCR0A = (dutyCycle/100)*255; //Representation of time led is on

	sei(); //Enable external interrupts

	//Set prescale to 64 in register(Timer/Counter Control Register B)
	TCCR0B &= ~(1<<WGM02); //Set WGM02 to 0
	TCCR0B &= (1<<CS02); //Set CS02 to 0
	TCCR0B &= (1<<CS01); //Set CS01 to 1
	TCCR0B |= (1<<CS00); //and CS00 to 1

	TCNT0 = 0; //Start timer
}

ISR(TIMER0_OVF_vect) {
	uint16_t pwmSpeed = 50; //variable for adjusting PWM-speed, works well at 50
	OCR0A = (dutyCycle/100)*pwmSpeed;  //Equation for creating a fraction to regulate duty-cycle
}

void fadeLedUp(void) {
	dutyCycle++; //Increment dutyCycle to increase led light
	if(dutyCycle > 200) { //when dutyCycle reaches 200...
		dutyCycle = 0;		//reset
	}
}
void fadeLedDown(void) { //same as fadeLedUp, but opposite
	dutyCycle--;
	if(dutyCycle == 0) {
		dutyCycle = 200;
	}
}