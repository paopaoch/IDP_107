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
const int linefollower_LF = 3; // key in the pin of left front line follower here
const int linefollower_RF = 4; // key in the pin of right front line follower here
const int encoder_L = 7;       // key in the pin of left encoder here
const int encoder_R = 6;       // key in the pin of right encoder here
const int k_f = 100;
const int k_r = 40;
bool not_at_the_line = true;
int encoder_L_count = 0;
int encoder_R_count = 0;
int k = 150;
int displacement_front;
int displacement_rear;

void move_to_grab(int direction) // temporary function will have to change to wheel encoder later
{
    switch (direction)
    {
        case 0:
        motor_L->setSpeed(k/2);  // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_L->run(FORWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        motor_R->setSpeed(k);  // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_R->run(FORWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        delay(150);
        motor_L->run(RELEASE);
        motor_R->run(RELEASE);
        break;

    case 1:
        motor_L->setSpeed(k);  // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_L->run(FORWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        motor_R->setSpeed(k/2);  // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_R->run(FORWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        delay(150);
        motor_L->run(RELEASE);
        motor_R->run(RELEASE);
        break;
    default:
        motor_L->setSpeed(k);  // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_L->run(FORWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        motor_R->setSpeed(k);  // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_R->run(FORWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        delay(150);
        motor_L->run(RELEASE);
        motor_R->run(RELEASE);
        break;
    }
    delay(500);
}

// ---------------------LINE FOLLOWER------------------------------------------
// void refresh_displacement_value()
// { // this function reads the data from the sensors, and updates the state of which wheel encoder is touching the left/right
//     if (digitalRead(linefollower_LR) == digitalRead(linefollower_RR))
//     {
//         displacement_rear = 0;
//     }
//     else
//     {
//         if (digitalRead(linefollower_LR) == HIGH)
//         {
//             displacement_rear = 1;
//         }
//         else
//         {
//             displacement_rear = -1;
//         };
//     };

//     if (digitalRead(linefollower_LF) == digitalRead(linefollower_RF))
//     {
//         displacement_front = 0;
//     }
//     else
//     {
//         if (digitalRead(linefollower_LF) == HIGH)
//         {
//             displacement_front = 1;
//         }
//         else
//         {
//             displacement_front = -1;
//         };
//     };
// }
// void line_follow()
// { // this function reads displacement constants, and update the motor speed, and move the motor}
//     motor_L_speed = 255;
//     motor_R_speed = 255;
//     int line_follower_constant;
//     line_follower_constant = k_r * displacement_rear - k_f * displacement_front;
//     if (line_follower_constant > 0)
//     {
//         motor_L_speed = 255 - line_follower_constant;
//     };
//     if (line_follower_constant < 0)
//     {
//         motor_R_speed = 255 + line_follower_constant;
//     };
//     motor_L->setSpeed(motor_L_speed);
//     motor_L->run(FORWARD);
//     motor_R->setSpeed(motor_R_speed);
//     motor_R->run(FORWARD);
// }

// void line_follow_main()
// {
//     refresh_displacement_value();
//     line_follow();
// }

void wheel_encoder_L_increment()
{
    encoder_L_count += 1;
}
void wheel_encoder_R_increment()
{
    encoder_R_count += 1;
}
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

    if (digitalRead(linefollower_LF) == HIGH && digitalRead(linefollower_RF) == HIGH)
    {
        not_at_the_line = false;
    }
    {
        not_at_the_line = true;
    };
}
void line_follow()
{ // this function reads displacement constants, and update the motor speed, and move the motor}
    motor_L_speed = 255;
    motor_R_speed = 255;
    int line_follower_constant;
    line_follower_constant = k_r * displacement_rear - k_f * displacement_front;
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
void line_follow_main_rev(int rev_needed) // this function follow the line, untile the front sensors reach the line we need
{
    while (not_at_the_line || float(encoder_L_count) < 12 * rev_needed)
    {
        // while(true){
        refresh_displacement_value();
        line_follow();
    };
    motor_L->run(RELEASE);
    motor_R->run(RELEASE);
    encoder_L_count = 0;
    encoder_R_count = 0;
}

void kill_it()
{
    motor_L->run(RELEASE);
    motor_R->run(RELEASE);
}
void clear_encoder()
{
    encoder_L_count = 0;
    encoder_R_count = 0;
}

void rotate(int turn_k)
{
    motor_L_speed = 255;
    motor_R_speed = 255;
    motor_L->setSpeed(motor_L_speed);
    motor_R->setSpeed(motor_R_speed);
    clear_encoder();
    switch (turn_k)
    { //+:turn right, -:turn left  method 1:move forward while turing  method 2:move backward while turning default:turn left 90 deg, not moving
    case +1:
        motor_L->run(FORWARD);
        break;
    case -1:
        motor_R->run(FORWARD);
        break;
    case -2:
        motor_L->run(BACKWARD);
        break;
    case +2:
        motor_R->run(BACKWARD);
        break;
    default:
        motor_R->run(FORWARD);
        motor_L->run(BACKWARD);
        break;
    };
    while (encoder_L_count + encoder_R_count < 19)
    {
        delay(1);
    }
    kill_it();
    clear_encoder();
}

#endif
