#pragma once
#include <stdint.h>

/** Delays by approx @p ms milliseconds.
 *  This method is not very exact! 
 *  Do not use for time critical things.
 *  */
void delay(uint16_t ms);
