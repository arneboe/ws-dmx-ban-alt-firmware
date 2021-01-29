#include "delay.h"

void delay(uint16_t ms)
{	
    //the constants have been hand tuned using a scope.
    //they are not very exact. 
    unsigned char i, j;
    do {
    	i = 12;
    	j = 200;
    	do
    	{
    		while (--j);
    	} while (--i);
    } while (--ms);
}