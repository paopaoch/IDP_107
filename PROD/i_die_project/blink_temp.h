unsigned int amberPin = 8;
int ledState = 0;
unsigned long previousMillis = 0;
const long interval = 250;
// the setup function runs once when you press reset or power the board

void blinkLEDTemp()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == 0)
    {
      ledState = 1;
    }
    else
    {
      ledState = 0;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(amberPin, ledState);
  }
}
