#include "leds.h"
#include "config.h"

//software pwm for leds

//brightness array for leds, this is written to from somewhere else
volatile unsigned char ledBrightness[NUM_LEDS];

//27136 interrupts/s @ 2007916.66 increments/s
//#define TIMER_START 65462

//37888 interrupts/s = ~148hz led update rate
//#define TIMER_START (65536-53) 

//54272 interrupts/s = ~212hz led update rate
#define TIMER_START (65536-37) 

//80384 interrupts/s = ~314hz led update rate
//#define TIMER_START (65536-25) 

//105728 interrupts/s ( every 9,45823us) = ~413hz led update rate 
//#define TIMER_START (65536-19) 

void ledInit()
{
    P3_4 = 0;
    P3_5 = 0;
    P2_1 = 0;
    P2_2 = 0;
    P2_3 = 0;
    P2_4 = 0;
    P2_5 = 0;
    P2_6 = 0;

    P3M0 = 0x30; //set P3.4 and P3.5 to strong push pull output
    P2M0 = 0x7e; //set P2.1 - P2.6 to strong push pull output

    AUXR &= ~0x80;   // Set timer clock source to sysclk/12 (12T mode)
    TMOD &= 0xF0;    // Clear 4bit field for timer0

    //set reload counter
    TH0 = TIMER_START >> 8;
    TL0 = (unsigned char)TIMER_START;

    // set timer 0 interrupt priority to high
    // this is done to ensure stable pwm.
    // if we set this to low the uart will interrupt
    // the pwm and cause visible jitter when lamps 
    // are at low values
    PT0 = 1; 

    ET0 = 1; // Enable Timer0 interrupts
    EA  = 1; // Global interrupt enable

    TR0 = 1; // Start Timer 0
}


volatile unsigned char timer0Cnt = 0;
void timer0Interrupt()  __interrupt(TF0_VECTOR) __using(1)
{
    P0_3 = 1;
    //this timer does the software pwm

    //The interrupt is called approximately every 18us
    //make sure to spend way less time than that in here
    //because uart and main need time as well

    //right now this method takes up ~7us.


    //FIXME this code is not generic at all because there seems to be no way
    //      to put __sbit into an array? wtf?

    //NOTE when the loop is too slow, we can remove the ledBrightness[0] != 0 check without much problems
    //     This would result in the led turning on for one step when cnt==0
    if(timer0Cnt <= ledBrightness[0] && ledBrightness[0] != 0)
    {
        P3_4 = 1;
    }
    else
    {
        P3_4 = 0;
    }

    if(timer0Cnt <= ledBrightness[1] && ledBrightness[1] != 0)
    {
        P3_5 = 1;
    }
    else
    {
        P3_5 = 0;
    }

    if(timer0Cnt <= ledBrightness[2] && ledBrightness[2] != 0)
    {
        P2_1 = 1;
    }
    else
    {
        P2_1 = 0;
    }

    if(timer0Cnt <= ledBrightness[3] && ledBrightness[3] != 0)
    {
        P2_2 = 1;
    }
    else
    {
        P2_2 = 0;
    }

    if(timer0Cnt <= ledBrightness[4] && ledBrightness[4] != 0)
    {
        P2_3 = 1;
    }
    else
    {
        P2_3 = 0;
    }

    if(timer0Cnt <= ledBrightness[5] && ledBrightness[5] != 0)
    {
        P2_4 = 1;
    }
    else
    {
        P2_4 = 0;
    }

    if(timer0Cnt <= ledBrightness[6] && ledBrightness[6] != 0)
    {
        P2_5 = 1;
    }
    else
    {
        P2_5 = 0;
    }

    if(timer0Cnt <= ledBrightness[7] && ledBrightness[7] != 0)
    {
        P2_6 = 1;
    }
    else
    {
        P2_6 = 0;
    }

    timer0Cnt++;

    P0_3 = 0;

    //P0_3 = 0;


}