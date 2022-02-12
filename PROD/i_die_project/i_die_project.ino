#include "blink_temp.h"
#include "movement.h"
#include "graber.h"
// pao just some info, the robot should go 187 cm forward, 110 cm back, and another 177 cm forward, another 155 cm back, another 205 cm forward, 185cm backward, and after the last block, and 74 cm back to starting position
// convert to revolution, that is (8.52 rev, 5.019rev, 8.06 rev, 7.24 rev, 9.34 rev,8.61 rev and 3.37 rev), as the wheel perimeter is 21.94 cm. 
// for the rotation, it takes 1.654 rev on a single wheel to turn 90 deg(or in other words, 0.827 on both wheels to have 90 deg turn. double for 180 deg turn. )

int STATE = 1;

void setup(void)
{
//    Serial.begin(9600);
    //**********SET UP BLINK***********
    pinMode(amberPin, OUTPUT);

    // *********SET UP MOTOR***********
    pinMode(linefollower_LR, INPUT);  
    pinMode(linefollower_RR, INPUT);  
    pinMode(linefollower_LF, INPUT);  
    pinMode(linefollower_RF, INPUT);
    pinMode(encoder_L,INPUT);
    pinMode(encoder_R,INPUT);
    attachInterrupt(digitalPinToInterrupt(encoder_L), wheel_encoder_L_increment, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoder_R), wheel_encoder_R_increment, CHANGE);
    AFMS.begin();

    // *********SET UP SERVO***********
    servo_L.attach(10);  // this is to attach servo to object, pin 10 for servo1, pin 9 for servo 2
    servo_R.attach(9); // this is to attach servo to object, pin 10 for servo1, pin 9 for servo 2
    servo_R.write(OPEN_R);
    servo_L.write(OPEN_L);
    delay(3000);
}

void loop()
{
//      servo_R.write(CLOSE_R);
//      servo_L.write(CLOSE_L);
//      line_follow_main_rev(100); // line follow till block
//      while(true) {
//        delay(100);
//        }
    blinkLEDTemp();
    switch (STATE)
    {
    case 1:
        // line_follow_main();
        line_follow_main_rev(100); // line follow till block
        STATE = 2;
        break;
    case 2:
        grabber_main(); // grab the block
        STATE = 3;
        break;
    case 3:
        rotate(3); // turn around
        STATE = 4;
        break;
    case 4:
        // line_follow_main();
        line_follow_main_rev(65); // line follow till back to line * have to calibrate
        STATE = 5;
        break;
    case 5:
        rotate(TURN_RIGHT_FORWARD); // turn right while move forwards
        open_both(); //open
        rotate(TURN_LEFT_BACKWARD); // turn right while move backwards
        STATE = 1;
        rotate(3);
        break;
    default:
        break;
    }
}
