/*
    All servo movements function should be included in this file
*/
#include <Servo.h>

#ifndef MOVEMENT
#define MOVEMENT
#include "movement.h"
#endif

// ---------INIT SERVO-------------
Servo servo_L;
Servo servo_R;
int servo_state = 0; // 0 is close left, 1 is close right, 2 is all close, 3 is all open

void toggle_servo(int orientation)
{
    switch (orientation)
    {
    case 0: // close right open left
        servo_R.write(135);
        servo_L.write(45);
        break;
    case 1: // open right close left
        servo_R.write(45);
        servo_L.write(135);
        break;
    case 2: // close right close left
        servo_R.write(135);
        servo_L.write(135);
        break;
    default: // open right open left
        servo_R.write(45);
        servo_L.write(45);
        break;
    }
    delay(3000);
}

void grabber_main()
{
    // close right
    toggle_servo(0);
    // close left
    toggle_servo(1);
    // open both
    toggle_servo(3);
    // turn
    move_to_grab(0); // turn left
    move_to_grab(1); // turn right
    move_to_grab(2); // move forward
    move_to_grab(1); // turn right *for correction
    move_to_grab(0); // turn left *for correction
    // close both
    toggle_servo(2);
}
