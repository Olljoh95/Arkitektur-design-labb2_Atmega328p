#include <avr/io.h>
#include<avr/interrupt.h>

#include "timer.h"
#include "led.h"

volatile uint8_t divider = 0; 

void timer_init() {
	DDRD = 0xFF;

	//Set CTC(Clear timer on compare match) in (Timer/Counter Control Register A)
	TCCR0A |= (1<<WGM01); //Set WGM01 to 1
	TCCR0A &= ~(1<<WGM00); //Set WGM00 to 0

	//Set prescale to 1024 in register(Timer/Counter Control Register B)
	TCCR0B &= ~(1<<WGM02); //Set WGM02 to 0
	TCCR0B |= (1<<CS02); //Set CS02 to 1
	TCCR0B &= ~(1<<CS01); //Set CS01 to 0
	TCCR0B &= (1<<CS00); //Set CS00 to 1

	TCNT0 = 0; //Start timer

	//Calculation for getting a time period of 10ms: 
	//(16000000/((155+1)*1024)) = 100.160... hz
	OCR0A = 155; //

	//Set Timer Interrupt Mask Register
	TIMSK0 |= (1<<OCIE0A);  //Set Output Compare Interrupt Enable Match A to 1

	sei();
}

ISR(TIMER0_COMPA_vect) {
	divider++;
}
