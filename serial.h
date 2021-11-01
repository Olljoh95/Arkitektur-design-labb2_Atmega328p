#ifndef SERIAL_H_
#define SERIAL_H_

void uart_init(void);

void uart_executeCommand(char *cmd);

void uart_putchar(unsigned char chr);

void uart_buildCommand(char *cmd);

void uart_putstr(unsigned char *str);

void uart_echo(void);

unsigned char uart_getchar(void);

#endif