#include <mcs51/lint.h>
#include <mcs51/8051.h>
#include "stc15w.h"
#include "delay.h"
#include "uart.h"
#include "config.h"

extern volatile unsigned char dmxData[NUM_ADRESSES]; //is defined in uart.c
int dmxStartAddr = 0;

int main()
{
    int i = 0;
    char numBuf[10];
    P0M1 = 0;
    P0M0 = 0;
    P0_3 = 0;

    uartInit();


   while(1)
   {
      // uartSendString("test \n");
      delay(1000);
      for(i = 0; i < NUM_ADRESSES; ++i)
      {
          uartSendByte(dmxData[i]);
      }
   }
}
