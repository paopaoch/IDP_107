/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards



void setup() {
  myservo.attach(9);  // this is to attach servo to object, pin 10 for servo1, pin 9 for servo 2
}

void loop() {
 
    // in steps of 1 degree
    myservo.write(135);              // tell servo to go to position in variable 'pos'
    delay(3000);                       // waits 15 ms for the servo to reach the position
  
 
    myservo.write(45);              // tell servo to go to position in variable 'pos'
    delay(3000);                       // waits 15 ms for the servo to reach the position
  
}
