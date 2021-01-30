#include <mcs51/lint.h>
#include <mcs51/8051.h>
#include "stc15w.h"
#include "delay.h"
#include "uart.h"
#include "dip.h"
#include "config.h"

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

// char c[20];
int main()
{
    // int i = 0;
   
    P0_3 = 0; //turn on power led

    dipInit();
    dmxAddr = readDmxAddr();
    functionBit = readFunctionDip();
    //TODO read dips once before initializing uart to make sure that
    //we start with a valid dmx adress.
    uartInit();

    while(1)
    {
        dmxAddr = readDmxAddr();
        functionBit = readFunctionDip();
        delay(1000); //TODO remove if finished testing


        
    //   for(i = 0; i < NUM_ADRESSES; ++i)
    //   {
    //       uartSendByte(dmxData[i]);
    //   }

      //  uartSendByte('\n');

       // uartSendByte(dipValue);
       // uartSendByte(dipValue >> 8);

   }
}
