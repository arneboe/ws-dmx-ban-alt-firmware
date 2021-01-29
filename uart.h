
#ifndef UART_H
#define UART_H

void uartInterrupt()  __interrupt(4) __using(1);

void uartInit();

void uartSendByte(unsigned char dat);

void uartSendString(char *s);


#endif