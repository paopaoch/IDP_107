/*
    all led interupt functions should be included in here
*/

#define TIMER_INTERRUPT_DEBUG 2
#define _TIMERINTERRUPT_LOGLEVEL_ 4

#define USING_16MHZ true
#define USING_8MHZ false
#define USING_250KHZ false

#define USE_TIMER_0 false
#define USE_TIMER_1 true
#define USE_TIMER_2 false
#define USE_TIMER_3 false

#define TIMER1_INTERVAL_MS 1000
#define TIMER1_FREQUENCY (float)(1000.0f / TIMER1_INTERVAL_MS)
#define TIMER1_DURATION_MS 0 //(10 * TIMER1_INTERVAL_MS)
#define ADJUST_FACTOR ((float)0.99850)

#include "megaAVR_TimerInterrupt.h"

unsigned int outputPin = 6;
int STATE = 1;

void blinkLED(unsigned int outputPin = 6)
{
    static bool toggle1 = false;
    static bool started = false;

    if (!started)
    {
        started = true;
        pinMode(outputPin, OUTPUT);
    }

    // timer interrupt toggles pin LED_BUILTIN
    digitalWrite(outputPin, toggle1);
    toggle1 = !toggle1;
}