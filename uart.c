#include "uart.h"
#include <mcs51/lint.h>
#include <mcs51/8051.h>
#include "stc11l04.h"
#include "config.h"

volatile unsigned char busy;//true if we are currently sending a byte 
volatile unsigned char dmxData[NUM_ADRESSES];
unsigned short dmxAddr = 0; //is written to from outside

void uartInit()
{
    int i = 0;
    for(i = 0; i < NUM_ADRESSES; ++i)
        dmxData[i] = 0;

    //DMX uses one start bit, 2 stopbits and no parity. That is mode 3 on the pcs15w404s

    busy = 0;
    /**
    set uart1 into 8-bit variable baud rate mode
   
    SM0=1 and SM1=1 => Mode 3 8 bitvariable baudrate async, one start bit, one stop bit, one programmable stop bit (TB8)
    SM2=0 => Disable automatic address recognition 
    REN=1 => enable serial reception
    TB8=1 => set to 1 because dmx uses two stop bits
    RB8 is set by the hardware and contains the value of the first stop bit (always one for DMX)
    TI/RI are interrupt flags that will be set by hardware*/
    SCON = 0xD8;

    //calculate timer overlow values based to achieve BAUD rate based on cpu frequency 
    //copied from the example code in offcial documentation
    
    TL1  =  (65536 - (FOSC/4/BAUD));    //Set the preload value
    TH1  =  (65536 - (FOSC/4/BAUD))>>8;
    AUXR = 0x40; //T1 in 1T mode and use T1 as uart1 baud-rate generator

    TR1 = 1; //start timer 1

    PS = 0; //set uart interrupt to low priority

    ES  =  1; //enable UART1 interrupt
    EA  =  1; //enable all interrupts

}

void uartInterrupt()  __interrupt(SI0_VECTOR) __using(1)
{
    /** NOTE 
     *  we could enable frame error detection and check for frame error instead of RB8.
     *  But if we do that we keep missing the start code.
     *  I have no idea why that happens :-( 
     *  But ignoring frame errors and just checking for RB8 works fine*/

    static unsigned short bytesReceived = 0;
    static unsigned char startCodeValid = 0; 

    if(RI) //if we received a byte
    {
        unsigned char dat = SBUF;
        RI = 0;

        //check 9th bit (first stop bit)
        if(RB8 == 1) //valid frame
        {
            //check if start code is correct (i.e. is zero for normal dmx signal)
            if(bytesReceived == 0 && dat == 0)
            {
                startCodeValid = 1;
            }
            //if start was valid and the current byte is in our adress range
            else if(startCodeValid && bytesReceived >= dmxAddr && bytesReceived < dmxAddr + NUM_ADRESSES)
            {
                dmxData[bytesReceived - dmxAddr] = dat;
            }
            bytesReceived++;
        }
        else //invalid frame. 
        {
            //check if frame is complete.
            //we dont check for (bytesReceived == 513) because dmx controllers are allowed 
            //to end a frame early when there are no lights configured in that range. 
            if(bytesReceived >= dmxAddr + NUM_ADRESSES)
            {
                //turn off power led.
                //the main loop will turn it back on resulting in a flickering led
                //if dmx is present
                P0_3 = 1;
            }

            bytesReceived = 0;
            startCodeValid = 0;
        }
    }

    if (TI) //if we have sent a byte
    {
        TI = 0; //clear transmit interrupt
        busy = 0; //clear busy flag to signal that the next byte may be sent
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