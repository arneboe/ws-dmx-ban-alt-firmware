#include <mcs51/lint.h>
#include <mcs51/8051.h>
#include "stc15w.h"
#include "delay.h"
#include "uart.h"
#include "dip.h"
#include "config.h"
#include "leds.h"

//400 interrupts/s 
#define STROBE_TIMER_START (65536-FOSC/12/400)
// on time of a strobe flash in 2.5ms steps
#define STROBE_ON_TIME_MS 4


extern volatile unsigned char dmxData[NUM_ADRESSES]; //defined in uart.c
extern unsigned short dmxAddr; //defined in uart.c
extern unsigned char ledBrightness[NUM_LEDS]; //defined in leds.c

/** this value is increased by a timer every 2.5ms.
 *  It is used in the strobe logic.
 *  The strobe logic also resets this value */
volatile unsigned char timeMs = 0;

void initStrobeTimer()
{
    AUXR &= 0xBF;   // Set timer1 clock source to sysclk/12 (12T mode)
    TMOD &= 0x0F;    // Clear 4bit field for timer1

    //set reload counter
    TH1 = STROBE_TIMER_START >> 8;
    TL1 = (unsigned char)STROBE_TIMER_START;

    // set timer 1 interrupt priority to low
    PT1 = 0; 

    TR1 = 1; // Start Timer 1

    //enable interrupt
    ET1 = 1;
    EA  = 1;
}


/** Is invoked at 1000hz */
void systick()  __interrupt(TF1_VECTOR) __using(1)
{
    // the systick has the same priority as uart.
    // thus we can do nearly nothing in here. 
    ++timeMs;
}


unsigned char calcStrobeTimeMs(unsigned char strobeDmxVal)
{
    //TODO implement me
    return strobeDmxVal;
}


void main()
{
    unsigned char i = 0;
    unsigned short masterBrightness = 0;
    unsigned char strobeDmx = 0;
    unsigned char strobeOffTime = 0;
    unsigned char functionBit = 0;
    unsigned char oldStrobe = 0;
    unsigned char strobeOn = 0; //current state of strobe (led on or off)

    dipInit();

    // //read dips once before initializing uart to make sure that
    // //we start with a valid dmx adress.
    // //FIXME check for dmxAddr==0 because thats not allowed
    dmxAddr = readDmxAddr();
    functionBit = readFunctionDip();

    uartInit(); //initially sets AUXR
    ledInit(); //modifies AUXR
    initStrobeTimer(); //modifes AUXR

    P0_3 = 0; //turn on power

    while(1)
    {
      //  uartSendByte('\n');
        dmxAddr = readDmxAddr();
        functionBit = readFunctionDip();

        strobeDmx = dmxData[1];
        if(!oldStrobe)
        {
            //strobe has been turned on, reset strobe start time to now
            timeMs = 0;
            strobeOn = 1;
        }
        oldStrobe = strobeDmx;

        if(strobeDmx)
        {
            if(strobeOn)
            {
                //check if strobe flash needs to be turned off
                if(timeMs >  STROBE_ON_TIME_MS)
                {
                    //led was on long enough, turn off
                    masterBrightness = 0;
                    strobeOn = 0;
                    timeMs = 0;
                }
                else
                {
                    //led should stay on (or turn on)
                    masterBrightness = dmxData[0];
                }
            }
            else
            {
                strobeOffTime = calcStrobeTimeMs(strobeDmx);
                //check if it is time to turn on strobe
                if(timeMs > strobeOffTime)
                {
                    //time to turn the strobe back on
                    masterBrightness = dmxData[0];
                    strobeOn = 1;
                    timeMs = 0;
                }
                else
                {
                    //leave it off a little longer (or turn it off)
                    masterBrightness = 0;
                }
            }
        }
        else
        {
            masterBrightness = dmxData[0];
        }


        for(i = 2; i < NUM_LEDS + 2; ++i)
        {
            // The master scaling is done in fixed point math with scale 255
            // 255 was chosen because it allows to ommit scaling of masterBrightness
            // and is close to the theoretical maximum scale of 257 
            // (255*257=biggest possible unsigned short).
            ledBrightness[i-2] = (dmxData[i] * masterBrightness) / 255;
        }
    }
}
