#include <Servo.h>
#include <Adafruit_MotorShield.h>

// ---------INIT MOTOR-------------
// INIT MOTOR
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor_L = AFMS.getMotor(3); // key in the port the left motor is connected to here
Adafruit_DCMotor *motor_R = AFMS.getMotor(4); // key in the port the right motor is connected to here
int motor_L_speed;
int motor_R_speed;
int k = 200;
int CLOSE_R = 145;
int CLOSE_L = 45;
int OPEN_R = 55;
int OPEN_L = 145;
int pos_L;
int pos_R;

// ---------INIT SERVO-------------
Servo servo_L;
Servo servo_R;
int servo_state = 0; // 0 is close left, 1 is close right, 2 is all close, 3 is all open

void setup()
{
    AFMS.begin();
    servo_L.attach(10);  // this is to attach servo to object, pin 10 for servo1, pin 9 for servo 2
    servo_R.attach(9); // this is to attach servo to object, pin 10 for servo1, pin 9 for servo 2
    servo_R.write(OPEN_R);
    servo_L.write(OPEN_L);
}

void move_to_grab(int direction) // temporary function will have to change to wheel encoder later
{
    switch (direction)
    {
    case 0:
        motor_L->setSpeed(k/2);  // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_L->run(FORWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        motor_R->setSpeed(k);  // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_R->run(FORWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        delay(300);
        motor_L->run(RELEASE);
        motor_R->run(RELEASE);
        break;

    case 1:
        motor_L->setSpeed(k);  // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_L->run(FORWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        motor_R->setSpeed(k/2);  // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_R->run(FORWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        delay(300);
        motor_L->run(RELEASE);
        motor_R->run(RELEASE);
        break;
    default:
        motor_L->setSpeed(k);  // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_L->run(FORWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        motor_R->setSpeed(k);  // Set the speed of motor, from 0 (off) to 255 (max speed)
        motor_R->run(FORWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
        delay(300);
        motor_L->run(RELEASE);
        motor_R->run(RELEASE);
        break;
    }
    delay(300);
}

void close_R()
{
    for (pos_R = OPEN_R; pos_R <= CLOSE_R; pos_R += 1)
    {
        servo_R.write(pos_R);
        delay(17);
    }
}

void open_R()
{
    for (pos_R = CLOSE_R; pos_R >= OPEN_R; pos_R -= 1)
    {
        servo_R.write(pos_R);
        delay(17);
    }
}

void close_L()
{
    for (pos_L = OPEN_L; pos_L >= CLOSE_L; pos_L -= 1)
    {
        servo_L.write(pos_L);
        delay(17);
    }
}

void open_L()
{
    for (pos_L = CLOSE_L; pos_L <= OPEN_L; pos_L += 1)
    {
        servo_L.write(pos_L);
        delay(17);
    }
}

void open_both()
{
    pos_L = CLOSE_L;
    for (pos_R = CLOSE_R; pos_R >= OPEN_R; pos_R -= 1)
    {
        servo_R.write(pos_R);
        servo_L.write(pos_L);
        delay(17);
        pos_L += 1;
    }
}

void close_both()
{
    pos_L = OPEN_L;
    for (pos_R = OPEN_R; pos_R <= CLOSE_R; pos_R += 1)
    {
        servo_R.write(pos_R);
        servo_L.write(pos_L);
        delay(17);
        pos_L -= 1;
    }
}

void toggle_servo(int orientation)
{
    switch (orientation)
    {
    case 0: // close right open left
        servo_R.write(CLOSE_R);
        servo_L.write(OPEN_L);
        break;
    case 1: // open right close left
        servo_R.write(OPEN_R);
        servo_L.write(CLOSE_L);
        break;
    case 2: // close right close left
        servo_R.write(CLOSE_R);
        servo_L.write(CLOSE_L);
        break;
    default: // open right open left
        servo_R.write(OPEN_R);
        servo_L.write(OPEN_L);
        break;
    }
    delay(3000);
}

void loop()
{
    // // close right
    // toggle_servo(0);
    // // close left
    // toggle_servo(1);
    // // open both
    // toggle_servo(3);
    // // turn
    // move_to_grab(0); // turn left
    // move_to_grab(1); // turn right
    // move_to_grab(2); // move forward
    // move_to_grab(1); // turn right *for correction
    // move_to_grab(0); // turn left *for correction
    // // close both
    // toggle_servo(2);
    // delay(5000);

    //    toggle_servo(2);
    //    delay(3000);
    //    toggle_servo(3);
    //    close_R();
    //
    //    delay(2000);
    //    close_L();
    //    delay(5000);
    //    open_R();
    //
    //    delay(2000);
    //    open_L();
//    close_L();
//    open_L();
//    close_R();
//    open_R();
//    close_L();
//    open_L();
//    move_to_grab(0); // turn left
//    move_to_grab(1); // turn right
//    move_to_grab(1); // turn right *for correction
//    move_to_grab(0); // turn left *for correction
//    move_to_grab(2); // move forward
//    close_both();
//    delay(4000);
//    open_both();
//    delay(2000);
}
