// this is the basic program to test whether the arduino is working. simply uploade, and it will turn the onboard LED on and off alternatly.
unsigned int outputPinGreen = 12;
unsigned int outputPinRed = 8;

void shineGreen()
{
    digitalWrite(outputPinGreen, 1);
}

void dimGreen()
{
    digitalWrite(outputPinGreen, 0);
}

void shineRed()
{
    digitalWrite(outputPinRed, 1);
}

void dimRed()
{
    digitalWrite(outputPinRed, 0);
}
