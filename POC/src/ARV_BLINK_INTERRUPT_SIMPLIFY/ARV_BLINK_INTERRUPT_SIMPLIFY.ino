#include "arv_blink_wifi_rev_config.h"
#include "megaAVR_TimerInterrupt.h"

unsigned int outputPin = 6;

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

void setup()
{
  ITimer1.init();
  ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS * ADJUST_FACTOR, blinkLED, outputPin, TIMER1_DURATION_MS);
}

void loop()
{
}
