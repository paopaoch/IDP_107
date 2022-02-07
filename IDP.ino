<<<<<<< HEAD
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
=======
#include <Serial.h>

     // this is a test to key in in the serial portal, and returns the same thing you typed to make sure the serial connection working
     char k;
void setup() {

     Serial.begin(9600);//sets the baud rate to 115200. do change the baud rate to this value in the portal as well


}

void loop() {
  if (Serial.available()) {
 k=Serial.read();
 delay (1);
 Serial.write(k);}
>>>>>>> c02400ecf5cc5d21610df4201584dc918465e311
}

