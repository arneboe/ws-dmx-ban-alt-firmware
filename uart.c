#include "uart.h"
#include <mcs51/lint.h>
#include <mcs51/8051.h>
#include "stc15w.h"
#include "config.h"

//volatile because it is changed by the interrupt
volatile unsigned char busy;

void uartInit()
{
    busy = 0;
    SCON = 0x50; //8-bit variable baud rate
    T2L  =  (65536 - (FOSC/4/BAUD));    //Set the preload value
    T2H  =  (65536 - (FOSC/4/BAUD))>>8;
    AUXR  =  0x14;                //T2 in 1T mode,  and run T2
    AUXR  |= 0x01;              //select T2 as UART1 baud-rate generator
    ES  =  1;                      //enable UART1 interrupt
    EA  =  1;

}

void uartInterrupt()  __interrupt(4) __using(1)
{
    if (RI)
    {
        RI = 0;                      //clear RI
        //get received byte from SBUF
        //serial data is shown in P0
        //RB8 contains the parity bit if any   
    }
    if (TI)
    {
        TI = 0;                      //clear TI
        busy = 0;                  //clear busy flag
    }
}

void uartSendByte(unsigned char dat)
{
    while (busy);                //wait to finish sending the previous data
    ACC = dat;                  //access to the parity bit ---- P (PSW.0)
    busy = 1;
    SBUF = ACC;  
}

void uartSendString(char *s)
{
    while (*s) 
    {
        uartSendByte(*s++);   
    }
}