/*
    THIS FILE SHOULD INCLUDE ALL FUNCTIONS WITH MOTOR ie. line follow
*/
#ifndef ADAFRUIT_MOTOR
#define ADAFRUIT_MOTOR
#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor_L = AFMS.getMotor(3); // key in the port the left motor is connected to here
Adafruit_DCMotor *motor_R = AFMS.getMotor(4); // key in the port the right motor is connected to here
// ---------INIT MOTOR-------------
// INIT MOTOR
// Create the motor shield object with the default I2C address
int motor_L_speed;
int motor_R_speed;
const int linefollower_LR = 5; // key in the pin of left rear line follower here
const int linefollower_RR = 2; // key in the pin of right rear line follower here
const int linefollower_LF = 4; // key in the pin of left front line follower here
const int linefollower_RF = 3; // key in the pin of right front line follower here
const int k_f = 100;
const int k_r = 40;
int k = 150;
int displacement_front;
int displacement_rear;

void move_to_grab(int direction) // temporary function will have to change to wheel encoder later
{
    switch (direction)
    {
    case 0: // move right wheel
        motor_R->setSpeed(k);  // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_R->run(FORWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        delay(1000);
        motor_R->run(RELEASE);
        break;

    case 1: // move left wheel
        motor_L->setSpeed(k);  // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_L->run(FORWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        delay(1000);
        motor_L->run(RELEASE);
        break;
    default: // move forwards
        motor_L->setSpeed(k);  // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_L->run(FORWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        motor_R->setSpeed(k);  // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_R->run(FORWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        delay(1000);
        motor_L->run(RELEASE);
        motor_R->run(RELEASE);
        break;
    }
    delay(500);
}

// ---------------------LINE FOLLOWER------------------------------------------
void refresh_displacement_value()
{ // this function reads the data from the sensors, and updates the state of which wheel encoder is touching the left/right
    if (digitalRead(linefollower_LR) == digitalRead(linefollower_RR))
    {
        displacement_rear = 0;
    }
    else
    {
        if (digitalRead(linefollower_LR) == HIGH)
        {
            displacement_rear = 1;
        }
        else
        {
            displacement_rear = -1;
        };
    };

    if (digitalRead(linefollower_LF) == digitalRead(linefollower_RF))
    {
        displacement_front = 0;
    }
    else
    {
        if (digitalRead(linefollower_LF) == HIGH)
        {
            displacement_front = 1;
        }
        else
        {
            displacement_front = -1;
        };
    };
}
void line_follow()
{ // this function reads displacement constants, and update the motor speed, and move the motor}
    motor_L_speed = 255;
    motor_R_speed = 255;
    int line_follower_constant;
    line_follower_constant = k_r * displacement_rear + k_f * displacement_front;
    if (line_follower_constant > 0)
    {
        motor_L_speed = 255 - line_follower_constant;
    };
    if (line_follower_constant < 0)
    {
        motor_R_speed = 255 + line_follower_constant;
    };
    motor_L->setSpeed(motor_L_speed);
    motor_L->run(FORWARD);
    motor_R->setSpeed(motor_R_speed);
    motor_R->run(FORWARD);
}

void line_follow_main()
{
    refresh_displacement_value();
    line_follow();
}
#endif
