#include <avr/io.h>

#include "timer.h"

void timer_init() {
	//Set CTC(Clear timer on compare match)
	TCCR0A |= (1<<WGM01); //Set WGM01 to 1
	TCCR0A &= ~(1<<WGM00); //Set WGM00 to 0

	//Set prescale to 1024
	TCCR0B &= ~(1<<WGM02); //Set WGM02 to 0     
	TCCR0B |= (1<<CS02); //Set CS02 to 1
	TCCR0B &= ~(1<<CS01); //Set CS01 to 0
	TCCR0B &= (1<<CS00); //Set CS00 to 1

	TCNT0 = 0; //Start timer

	//(16000000/((155+1)*1024))
	OCR0A = 155;

}

