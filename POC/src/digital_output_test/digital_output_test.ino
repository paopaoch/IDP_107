// this test allows for the test the digital output. It will output in an alternate of high and low, in a digital pin.
const int input = 2;// initialize the digital pin. pleas key in the digital pin tested here in the plase of 2
void setup() {

  pinMode(input, OUTPUT);  // initialize the digital pin. pleas key in the digital pin tested in the number 2
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(input, HIGH);   // sets the pin high
  delay(1000);                       //leave the pin high for a second(if alternate times needed, please key in the time here)
  digitalWrite(input, LOW);    // sets the pin LOW
  delay(1000);                       //leave the pin low for a second(if alternate times needed, please key in the time here)
}
