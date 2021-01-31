#ifndef LEDS_H
#include <mcs51/lint.h>
#include <mcs51/8051.h>
#include "stc15w.h"

//ATTETION there is an unrolled loop in leds.c depending on this number.
//         if you change this number, also fix the loop
#define NUM_LEDS 8

void ledInit();

void timer0Interrupt()  __interrupt(TF0_VECTOR) __using(1);

#define LEDS_H
#endif