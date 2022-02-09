#define TIMER_INTERRUPT_DEBUG 2
#define _TIMERINTERRUPT_LOGLEVEL_ 4

#define USING_16MHZ false
#define USING_8MHZ true
#define USING_250KHZ false

#define USE_TIMER_0 false
#define USE_TIMER_1 false
#define USE_TIMER_2 true
#define USE_TIMER_3 false

#define TIMER2_INTERVAL_MS 250
#define TIMER2_FREQUENCY (float)(1000.0f / TIMER1_INTERVAL_MS)
#define TIMER2_DURATION_MS 0 //(10 * TIMER1_INTERVAL_MS)
#define ADJUST_FACTOR ((float)0.99850)