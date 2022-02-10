/*
    All servo movements function should be included in this file
*/
#include <Servo.h>

//#ifndef MOVEMENT
//#define MOVEMENT
//#include "movement.h"
//#endif

// ---------INIT SERVO-------------
Servo servo_L;
Servo servo_R;
int servo_state = 0; // 0 is close left, 1 is close right, 2 is all close, 3 is all open
int CLOSE_R = 145;
int CLOSE_L = 45;
int OPEN_R = 55;
int OPEN_L = 145;
int pos_L;
int pos_R;
int grabber_speed = 20;

void close_R()
{
    for (pos_R = OPEN_R; pos_R <= CLOSE_R; pos_R += 1)
    {
        blinkLEDTemp();
        servo_R.write(pos_R);
        delay(grabber_speed);
    }
}

void open_R()
{
    for (pos_R = CLOSE_R; pos_R >= OPEN_R; pos_R -= 1)
    {
        blinkLEDTemp();
        servo_R.write(pos_R);
        delay(grabber_speed);
    }
}

void close_L()
{
    for (pos_L = OPEN_L; pos_L >= CLOSE_L; pos_L -= 1)
    {
        blinkLEDTemp();
        servo_L.write(pos_L);
        delay(grabber_speed);
    }
}

void open_L()
{
    for (pos_L = CLOSE_L; pos_L <= OPEN_L; pos_L += 1)
    {
        blinkLEDTemp();
        servo_L.write(pos_L);
        delay(grabber_speed);
    }
}

void open_both()
{
    pos_L = CLOSE_L;
    for (pos_R = CLOSE_R; pos_R >= OPEN_R; pos_R -= 1)
    {
        blinkLEDTemp();
        servo_R.write(pos_R);
        servo_L.write(pos_L);
        delay(grabber_speed);
        pos_L += 1;
    }
}

void close_both()
{
    pos_L = OPEN_L;
    for (pos_R = OPEN_R; pos_R <= CLOSE_R; pos_R += 1)
    {
        blinkLEDTemp();
        servo_R.write(pos_R);
        servo_L.write(pos_L);
        delay(grabber_speed);
        pos_L -= 1;
    }
}

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
   close_L();
   open_L();
   close_R();
   open_R();
   close_L();
   open_L();
   move_to_grab(MOVE_GRAB_LEFT); // turn left
   move_to_grab(MOVE_GRAB_RIGHT); // turn right
   move_to_grab(MOVE_GRAB_FORWARD); // move forward
   move_to_grab(MOVE_GRAB_RIGHT); // turn right *for correction
   move_to_grab(MOVE_GRAB_LEFT); // turn left *for correction
   move_to_grab(MOVE_GRAB_FORWARD); // move forward
   close_both();
}
