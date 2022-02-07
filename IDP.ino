#include <TimerOne.h>

const int led = LED_BUILTIN; // the pin with a LED
int STATE = 1;
int ledState = LOW;

void setup(void)
{
     pinMode(led, OUTPUT);
     Timer1.initialize(500000);        // set the interval 500000 is .5 secs
     Timer1.attachInterrupt(blinkLED); // attach blinkLED to the Timer as an interrupt
}

void blinkLED(void) // function to blink LED
{
     if (ledState == LOW)
     {
          ledState = HIGH;
     }
     else
     {
          ledState = LOW;
     }
     digitalWrite(led, ledState);
}

void loop(void)
{
     delay(10000);

     if (STATE == 1)
     {
          Timer1.setPeriod(2000000);
          STATE = 0;
     }
     else
     {
          Timer1.setPeriod(500000);
          STATE = 1;
     }
}
