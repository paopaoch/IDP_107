//this program teste the analogue read of the analogue pins. It then outputs the reading via the serial communication in the port
const int input1 = A0;                  // sets up the analogue pin A0
const int input2 = A1;
const int input3 = A2;
const int input4 = A3;
void setup() {
  // initialize the serial communications:
  Serial.begin(9600);// set the baud rate(9600 in this case）


}

void loop() {
  Serial.print("reading from 1 is:");
  Serial.println(analogRead(input1));

  //get reading from the pin
  delay(1000);//delay 100 before the next reading
}
