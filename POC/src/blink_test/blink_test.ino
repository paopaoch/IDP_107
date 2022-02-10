// this is the basic program to test whether the arduino is working. simply uploade, and it will turn the onboard LED on and off alternatly.
unsigned int outputPin = 8;
int ledState = 0;
unsigned long previousMillis = 0;
const long interval = 250;
// the setup function runs once when you press reset or power the board
void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(outputPin, OUTPUT);
}

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
    digitalWrite(outputPin, ledState);
  }
}

void loop()
{
  blinkLEDTemp();
}
