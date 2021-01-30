#include "leds.h"
#include "config.h"

//software pwm for leds

//27136 interrupts/s @ 2007916.66 increments/s
//#define T1MS 65462

//37888 interrupts/s = ~148hz led update rate
#define T1MS (65536-53) 

void ledInit()
{
    //see https://www.theengineeringprojects.com/2016/02/generate-pwm-8051-microcontroller.html

    AUXR &= ~0x80;   // Set timer clock source to sysclk/12 (12T mode)
    TMOD &= 0xF0;    // Clear 4bit field for timer0

    //set reload counter
    TH0 = T1MS >> 8;
    TL0 = (unsigned char)T1MS;

    ET0 = 1;         // Enable Timer0 interrupts
    EA  = 1;         // Global interrupt enable

    TR0 = 1;         // Start Timer 0

}


extern unsigned char duty;

volatile unsigned char cnt = 0;

void timer0Interrupt()  __interrupt(TF0_VECTOR) __using(1)
{
    if(cnt < 128)
    {
        P3_4 = 0;
    }
    else
    {
        P3_4 = 1;
    }
    cnt++;

    // static unsigned char cnt = 0;
    // //set reload counter
    // //NOTE we need to be waaay faster than the timer in here :D
    // TH0 = T1MS >> 8;
    // TL0 = (unsigned char)T1MS;

    // if(cnt > duty)
    // {
    //     P3_4 = 1;
    //     P0_3 = 1;
    // }
    // else
    // {
    //     P3_4 = 0;
    //     P0_3 = 0;
    // }

}