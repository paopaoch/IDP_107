/*
    THIS FILE SHOULD INCLUDE ALL FUNCTIONS WITH MOTOR eg. line follow
*/

#ifndef ADAFRUIT_MOTOR
#define ADAFRUIT_MOTOR

#define TURN_RIGHT_FORWARD 1
#define TURN_RIGHT_BACKWARD 2
#define TURN_LEFT_FORWARD -1
#define TURN_LEFT_BACKWARD -2
#define TURN_RIGHT_BOTH 3
#define TURN_LEFT_BOTH -3
#define TURN_AROUND 0

#define MOVE_GRAB_LEFT 0
#define MOVE_GRAB_RIGHT 1
#define MOVE_GRAB_FORWARD 2
#define MOVE_GRAB_BACKWARD 3

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
const int encoder_L = 6;       // key in the pin of left encoder here
const int encoder_R = 7;       // key in the pin of right encoder here
const int k_f = 95;
const int k_r = 38;
int not_at_the_line = 0;
bool res;
int encoder_L_count = 0;
int encoder_R_count = 0;
int k = 150;
int displacement_front;
int displacement_rear;

void move_to_grab(int direction, int GRAB_MOVE_SPEED = 200)
{
    switch (direction)
    {
    case MOVE_GRAB_LEFT:
        motor_L->setSpeed(k / 2); // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_L->run(FORWARD);    // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        motor_R->setSpeed(k);     // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_R->run(FORWARD);    // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        delay(GRAB_MOVE_SPEED);
        motor_L->run(RELEASE);
        motor_R->run(RELEASE);
        break;

    case MOVE_GRAB_RIGHT:
        motor_L->setSpeed(k);     // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_L->run(FORWARD);    // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        motor_R->setSpeed(k / 2); // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_R->run(FORWARD);    // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        delay(GRAB_MOVE_SPEED);
        motor_L->run(RELEASE);
        motor_R->run(RELEASE);
        break;
    case MOVE_GRAB_FORWARD:
        motor_L->setSpeed(k);  // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_L->run(FORWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        motor_R->setSpeed(k);  // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_R->run(FORWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        delay(GRAB_MOVE_SPEED);
        motor_L->run(RELEASE);
        motor_R->run(RELEASE);
        break;
    default:
        motor_L->setSpeed(k);   // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_L->run(BACKWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        motor_R->setSpeed(k);   // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_R->run(BACKWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        delay(GRAB_MOVE_SPEED);
        motor_L->run(RELEASE);
        motor_R->run(RELEASE);
        break;
    }
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

void wheel_encoder_L_increment()
{
    encoder_L_count += 1;
}
void wheel_encoder_R_increment()
{
    encoder_R_count += 1;
}
bool refresh_displacement_value()
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

    if (digitalRead(linefollower_LF) == LOW && digitalRead(linefollower_RF) == LOW)
    {
        //    not_at_the_line=1;
        return true;
    }
    else
    {
        //    not_at_the_line=0;
        return false;
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
void line_follow_main_rev(int rev_needed, int limit = 100) // this function follow the line, untile the front sensors reach the line we need
{
    clear_encoder();
    while (!res || encoder_L_count < rev_needed)
    {
        res = refresh_displacement_value();
        line_follow();
        if (encoder_L_count == limit)
        {
            break;
        }
    };
    motor_L->run(RELEASE);
    motor_R->run(RELEASE);
    clear_encoder();
}

void forward(int value)
{
    motor_L_speed = 255;
    motor_R_speed = 255;
    motor_L->setSpeed(motor_L_speed);
    motor_R->setSpeed(motor_R_speed);
    clear_encoder();
    motor_R->run(FORWARD);
    motor_L->run(FORWARD);
    while (encoder_L_count + encoder_R_count < value)
    {
        delay(1);
    }
    kill_it();
    clear_encoder();
}

void backward(int value)
{
    motor_L_speed = 255;
    motor_R_speed = 255;
    motor_L->setSpeed(motor_L_speed);
    motor_R->setSpeed(motor_R_speed);
    clear_encoder();
    motor_R->run(BACKWARD);
    motor_L->run(BACKWARD);
    while (encoder_L_count + encoder_R_count < value)
    {
        delay(1);
    }
    kill_it();
    clear_encoder();
}

void rotate(int k) // return value does not matter but if true then it should turn around
{
    bool move_through_line = false;
    motor_L_speed = 255;
    motor_R_speed = 255;
    motor_L->setSpeed(motor_L_speed);
    motor_R->setSpeed(motor_R_speed);
    clear_encoder();
    switch (k)
    { //+:turn right, -:turn left  method 1:move forward while turing  method 2:move backward while turning default:turn left 90 deg, not moving
    case TURN_RIGHT_FORWARD:
        motor_L->run(FORWARD);
        break;
    case TURN_LEFT_FORWARD:
        motor_R->run(FORWARD);
        break;
    case TURN_LEFT_BACKWARD:
        motor_L->run(BACKWARD);
        break;
    case TURN_RIGHT_BACKWARD:
        motor_R->run(BACKWARD);
        break;
    case TURN_RIGHT_BOTH:
        motor_R->run(BACKWARD);
        motor_L->run(FORWARD);
        break;
    case TURN_LEFT_BOTH:
        motor_R->run(FORWARD);
        motor_L->run(BACKWARD);
        break;
    default:
        motor_R->run(FORWARD);
        motor_L->run(BACKWARD);
        break;
    };
    int encoder_max = 20;
    if (k == TURN_AROUND)
    {
        encoder_max = 40;
    }
    while (encoder_L_count + encoder_R_count < encoder_max)
    {
        delay(1);
    }
    kill_it();
    clear_encoder();
    if (move_through_line)
    {
        move_to_grab(MOVE_GRAB_RIGHT, 250);
    }
    else
    {
        move_to_grab(MOVE_GRAB_LEFT, 250);
    }
}

#endif
