#include <mcs51/lint.h>
#include <mcs51/8051.h>
#include "stc15w.h"
#include "delay.h"
#include "uart.h"


int main()
{
    P0M1 = 0;
    P0M0 = 0;
    P0_3 = 0;

    uartInit();

   while(1)
   {
       uartSendString("test\n");
       delay(200);
       P0_3 = 1;
       delay(200);
       P0_3 = 0;
   }
}
