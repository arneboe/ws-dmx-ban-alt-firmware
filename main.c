#include <mcs51/lint.h>
#include <mcs51/8051.h>
#include "stc15w.h"
#include "delay.h"
#include "uart.h"
#include "dip.h"
#include "config.h"
#include "leds.h"



extern volatile unsigned char dmxData[NUM_ADRESSES]; //defined in uart.c
extern unsigned short dmxAddr; //defined in uart.c
extern unsigned char ledBrightness[NUM_LEDS]; //defined in leds.c
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
    unsigned char i = 0;
    unsigned short masterBrightness = 0;
   
    P0_3 = 0; //turn on power led

    dipInit();

    //read dips once before initializing uart to make sure that
    //we start with a valid dmx adress.
    //FIXME check for dmxAddr==0 because thats not allowed
    dmxAddr = readDmxAddr();
    functionBit = readFunctionDip();

    uartInit(); //initially sets AUXR
    ledInit(); //modifies AUXR

    while(1)
    {
        dmxAddr = readDmxAddr();
        functionBit = readFunctionDip();

        //FIXME this is bad, we get interrupted a lot. need
        //      move this to a 1ms timer or something.
        //TODO  check if we really get interrupted a lot

        // The master scaling is done in fixed point math with scale 255
        // 255 was chosen because it allows to ommit scaling of masterBrightness
        // and is close to the theoretical maximum scale of 257 
        // (255*257=biggest possible unsigned short).
        masterBrightness = dmxData[0];

        for(i = 1; i < NUM_LEDS + 1; ++i)
        {
            ledBrightness[i-1] = (dmxData[i] * masterBrightness) / 255;
            //ledBrightness[i]++;
            //ledBrightness[i]= 250;
        }
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
