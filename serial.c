#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"
#include "led.h"

//Sida 185 megaAVR® Data Sheet
#define FOSC 16000000                        //Clock speed
#define BAUDRATE 38400                      //Baudrate
#define BAUD_PRESCALE FOSC/16/BAUDRATE -1  //calculation for presacling

void uart_init(void) {
    //Baud rate set seperatly
    UBRR0H = (BAUD_PRESCALE >> 8); 
    UBRR0L = BAUD_PRESCALE;

    //UCSR0B = USART Control and Status Register B
    //RXEN = Enable receiver, TXEN0 = enable transmitter
    UCSR0B |= (1<<RXEN0) | (1<<TXEN0);

    //UCSR0C = USART control and status register C
    //I will set character size, parity, and UART/USART Mode, and number of stop bits to 8N1

    UCSR0C &= ~(0 << UMSEL00) | (0 << UMSEL01); // Asynchronous USART/UART mode

    UCSR0C &= ~(0 << UPM00) | (0 << UPM01); //No parity

    UCSR0C &= ~(0 << USBS0); //1 stop bit

    //UCSR0C &= ~(0 << UCSZ02);
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01); //8 bit character size
}

void uart_executeCommand(char *cmd) {
    if(strcmp(cmd, "blue\r\n") == 0) { //compare array content to activate desired led light.
		blueLight();
	}
	else if(strcmp(cmd, "green\r\n") == 0) {
		greenLight();
	}
	else if(strcmp(cmd, "red\r\n") == 0) {
		redLight();
	}
	else {
		led_off(); //If array content cannot be matched to command, turn led off.
	}
}


void uart_putchar(unsigned char chr) {
    while(!(UCSR0A & (1 << UDRE0))) { // while transmission is available
    }
        if(chr == '\n') { //check for prompted newline
        UDR0 = '\r';   //insert carrige return in reciever register
        }
    
    UDR0 = chr; //load data into buffer
}

void uart_buildCommand(char *cmd) {
    int i = 0;
    cmd[i] = uart_getchar(); //Get first character from buffer, insert into array at index 0
    while((cmd[i] != '\r') && (cmd[i] != '\n')) { //While array att index i is not newline and not carrige return...
        uart_putchar(cmd[i]); //Print out buffercontent to terminal.
        i++;
        cmd[i] = uart_getchar();  //Continously feed incremented array index
    }
    cmd[i] = '\r'; //insert carrige return
    i++;
    cmd[i] = '\n'; //insert newline
    cmd[i+1] = '\0'; //break string
}

void uart_putstr(unsigned char *str) {
    int i = 0;                  //variable for iterating string
    while(str[i] != '\0' ) {
        uart_putchar(str[i]);  //transmit character until NULL is reached
        i++;
    }
}


void uart_echo(void) {
    uart_putchar(uart_getchar());  //Send char fetched from getChar function to putChar function
}


unsigned char uart_getchar(void) {
    while(!(UCSR0A & (1 << RXC0)));  //If recieve-buffer is not empty...
    return UDR0;        //return buffer content
}