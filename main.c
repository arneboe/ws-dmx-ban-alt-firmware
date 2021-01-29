#include <mcs51/lint.h>
#include <mcs51/8051.h>
#include "stc15w.h"
#include "delay.h"

int main()
{

    P0M1 = 0;
    P0M0 = 0;
    P0_3 = 0;

   while(1)
   {
       delay(5);
       P0_3 = 1;
       delay(5);
       P0_3 = 0;
   }
}
