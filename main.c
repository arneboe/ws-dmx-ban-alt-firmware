#include <mcs51/lint.h>
#include <mcs51/8051.h>
#include "stc15w.h"
#include "delay.h"
#include "uart.h"
#include "dip.h"
#include "config.h"
#include "leds.h"

extern volatile unsigned char dmxData[NUM_ADRESSES]; //is defined in uart.c
unsigned short dmxAddr = 0;
unsigned char functionBit = 0;

// #define NUMBER_OF_DIGITS 16   /* space for NUMBER_OF_DIGITS + '\0' */

// void uitoa(unsigned int value, char* string, int radix)
// {
// unsigned char index, i;

//   index = NUMBER_OF_DIGITS;
//   i = 0;

//   do {
//     string[--index] = '0' + (value % radix);
//     if ( string[index] > '9') string[index] += 'A' - ':';   /* continue with A, B,.. */
//     value /= radix;
//   } while (value != 0);

//   do {
//     string[i++] = string[index++];
//   } while ( index < NUMBER_OF_DIGITS );

//   string[i] = 0; /* string terminator */
// }

// void itoa(int value, char* string, int radix)
// {
//   if (value < 0 && radix == 10) {
//     *string++ = '-';
//     uitoa(-value, string, radix);
//   }
//   else {
//     uitoa(value, string, radix);
//   }
// }

unsigned char duty = 128;

// char c[20];
int main()
{
    // int i = 0;
   
    P0_3 = 0; //turn on power led

    P3_4 = 0;
    P3_5 = 0;
    P2_1 = 0;
    P2_2 = 0;
    P2_3 = 0;
    P2_4 = 0;
    P2_5 = 0;
    P2_6 = 0;

    P3M0 = 0x30; //set P3.4 and P3.5 to strong push pull output
    P2M0 = 0x7e; //set P2.1 - P2.6 to strong push pull output

    dipInit();
    dmxAddr = readDmxAddr();
    functionBit = readFunctionDip();
    //TODO read dips once before initializing uart to make sure that
    //we start with a valid dmx adress.
    uartInit(); //initially sets AUXR
    ledInit(); //mofies AUXR

    while(1)
    {
        dmxAddr = readDmxAddr();
        functionBit = readFunctionDip();
        delay(50); //TODO remove if finished testing
        //duty++;


    //   for(i = 0; i < NUM_ADRESSES; ++i)
    //   {
    //       uartSendByte(dmxData[i]);
    //   }

      //  uartSendByte('\n');

       // uartSendByte(dipValue);
       // uartSendByte(dipValue >> 8);

   }
}
