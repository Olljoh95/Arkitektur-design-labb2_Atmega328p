#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include <stdio.h>

#include "serial.h"
#include "led.h"
#include "timer.h"

void main (void) {
	LED_init();
	uart_init();
	timer0_init();

	while (1) {
		pwmLoop();
	}
}
