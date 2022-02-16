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
  myservo.attach(10);  // this is to attach servo to object, pin 10 for servo1, pin 9 for servo 
  myservo.write(160);
}

void loop() {
 
    // in steps of 1 degree
              // tell servo to go to position in variable 'pos'
                      // waits 15 ms for the servo to reach the position
                      //servi 10 left c:25 o 115
  
}
