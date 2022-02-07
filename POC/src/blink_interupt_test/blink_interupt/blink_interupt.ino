#include <MsTimer2.h>

const int led = LED_BUILTIN;  // the pin with a LED
int STATE = 1;
int ledState = LOW;

void setup(void)
{
//  pinMode(led, OUTPUT);
//  MsTimer2.initialize(500000); // set the interval 500000 is .5 secs
//  MsTimer2.attachInterrupt(blinkLED); // attach blinkLED to the Timer as an interrupt
    MsTimer2::set(250, blinkLED);
    MsTimer2::start(); // enable timer interrupt
}

void blinkLED(void) // function to blink LED
{
  if (ledState == LOW) {
    ledState = HIGH;
  } else {
    ledState = LOW;
  }
  digitalWrite(led, ledState);
}

void loop(void)
{
}
