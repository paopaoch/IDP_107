#include "arv_blink_wifi_rev_config.h"
#include "megaAVR_TimerInterrupt.h"

unsigned int outputPin = 8;

void blinkLED(unsigned int outputPin = 8)
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
  ITimer2.init();
  ITimer2.attachInterruptInterval(TIMER2_INTERVAL_MS * ADJUST_FACTOR, blinkLED, outputPin, TIMER2_DURATION_MS);
}

void loop()
{
  delay(10000);
}
