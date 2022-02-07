#include <Servo.h>
#include <Adafruit_MotorShield.h>

// ---------INIT MOTOR-------------
// INIT MOTOR
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor_L = AFMS.getMotor(1); // key in the port the left motor is connected to here
Adafruit_DCMotor *motor_R = AFMS.getMotor(2); // key in the port the right motor is connected to here
int motor_L_speed;
int motor_R_speed;
int k = 200;

// ---------INIT SERVO-------------
Servo servo_L;
Servo servo_R;
int servo_state = 0; // 0 is close left, 1 is close right, 2 is all close, 3 is all open

void setup()
{
    AFMS.begin();
    servo_L.attach(9);  // this is to attach servo to object, pin 10 for servo1, pin 9 for servo 2
    servo_R.attach(10); // this is to attach servo to object, pin 10 for servo1, pin 9 for servo 2
}

void move_to_grab(int direction) // temporary function will have to change to wheel encoder later
{
    switch (direction)
    {
    case 0:
        motor_R->setSpeed(k);  // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_R->run(FORWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        delay(1000);
        motor_R->run(RELEASE);
        break;

    case 1:
        motor_L->setSpeed(k);  // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_L->run(FORWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        delay(1000);
        motor_L->run(RELEASE);
        break;
    default:
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

void loop()
{
    // close right
    toggle_servo(0);
    // close left
    toggle_servo(1);
    // open both
    toggle_servo(3);
    // turn
    move_to_grab(0);
    move_to_grab(1);
    move_to_grab(2);
    // close both
    toggle_servo(2);
    delay(5000);
}
