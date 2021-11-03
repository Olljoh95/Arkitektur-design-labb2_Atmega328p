#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "timer.h"
#include "led.h"

volatile float dutyCycle = 0; //Global variable for regulation of led on-off period

void timer0_init() {
	DDRD = (1 << PORTD6); //Enable led on digital pin 6(using 220ohm resistor)

	//Clear OC0A on Compare match, set OC0A at bottom(non-inverting mode)
	TCCR0A |= (1<<COM0A1); //Set COM0A1 to 1
	TCCR0A &= ~(1<<COM0A0); //Set COM0A0 to 0
	//Set Fast PWM in (Timer/Counter Control Register A, Mode 3)
	TCCR0A |= (1<<WGM00); //Set WGM00 to 1	
	TCCR0A |= (1<<WGM01); //Set WGM01 to 1

	OCR0A = (dutyCycle/100)*255; //Representation of time led is on


	//Set prescale to 64 in register(Timer/Counter Control Register B)
	TCCR0B &= ~(1<<WGM02); //Set WGM02 to 0
	TCCR0B &= (1<<CS02); //Set CS02 to 0
	TCCR0B &= (1<<CS01); //Set CS01 to 1
	TCCR0B |= (1<<CS00); //and CS00 to 1

	TCNT0 = 255; //Start timer, TOP-value
}

void pwmLoop(void) {
	uint16_t pwmSpeed = 50; //variable for adjusting PWM-speed

	dutyCycle--; //The direction of led-fade, -- for fading downwards, ++ for upwards
	_delay_ms(5); //wait a little bit
	OCR0A = (dutyCycle/100)*pwmSpeed;  //Equation for creating a fraction to regulate duty-cycle
}