#ifndef LEDS_H
#include <mcs51/lint.h>
#include <mcs51/8051.h>


void ledInit();

void timer0Interrupt()  __interrupt(TF0_VECTOR) __using(1);

#define LEDS_H
#endif