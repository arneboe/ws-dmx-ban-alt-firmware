#include "dip.h"
#include <mcs51/lint.h>
#include <mcs51/8051.h>
#include "stc15w.h"

unsigned short dmxStartAddr = 1;

/* dip mapping:
   1  = P1.2
   2  = P1.3
   3  = P1.4
   4  = P1.5
   5  = P1.6
   6  = P1.7
   7  = P5.4
   8  = P5.5
   9  = P3.2
   10 = P3.3
*/


void dipInit()
{
    //we use the quasi-bi-directional mode.
    //This is the default thus we dont have to configure the mode.

    //turn on the pullups
    P1_2 = 1;
    P1_3 = 1;
    P1_4 = 1;
    P1_5 = 1;
    P1_6 = 1;
    P1_7 = 1;
    P5_4 = 1;
    P5_5 = 1;
    P3_2 = 1;
    P3_3 = 1;
}

unsigned short readDmxAddr()
{
    //initialize unused bits as 1 (will later be inverted to 0)
    unsigned short result = 0xfe00;

    result = result | P1_2;
    result = result | (P1_3 << 1);
    result = result | (P1_4 << 2);
    result = result | (P1_5 << 3);
    result = result | (P1_6 << 4);
    result = result | (P1_7 << 5);
    result = result | (P5_4 << 6);
    result = result | (P5_5 << 7);
    result = result | (P3_2 << 8);
    //result = result | (P3_3 << 9);

    //due to the pullups we read a 1 when the dip is in off-position.
    //thus invert every pin
    result = ~result;
    return result;
}

unsigned char readFunctionDip()
{
    return !P3_3;
}