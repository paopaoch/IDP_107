#include <Adafruit_MotorShield.h>

// simply connect the motors in the motor shield, set the speed, upload the code, and off you go.
int k = 200;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *motor_L = AFMS.getMotor(3);
Adafruit_DCMotor *motor_R = AFMS.getMotor(4);

int encoder_L = 0;
int encoder_R = 0;
float encoder_calibrator = 1.0; // adjust according to how encoder count correlate with degrees
void move(int distance = 1, int direction = FOWARD)
{
    motor_L->setSpeed(k);
    motor_R->setSpeed(k);

    while (encoder_L != distance + 1 || encoder_R != distance + 1)
    {
        if (encoder_L != distance)
        {
            motor_L->run(direction);
        }
        else
        {
            motor_L->run(RELEASE);
        }

        if (encoder_R != distance)
        {
            motor_R->run(direction);
        }
        else
        {
            motor_R->run(RELEASE);
        }
    }

    encoder_L = 0;
    encoder_R = 0;
}

// 0 -> turn left with both wheels
// 1 -> turn right with both wheels
// 2 -> turn left with right wheel
// 3 -> turn right with left wheel
void turn(int degrees, int turn_mode)
{
    int encoder_max = static_cast<int>(degrees * encoder_calibrator);
    motor_L->setSpeed(k);
    motor_R->setSpeed(k);
    switch (turn_mode)
    {
    case 0:
    case 1:
        if (turn_mode == 0)
        {
            int direction_L = BACKWARD;
            int direction_R = FORWARD;
        }
        else
        {
            int direction_L = FORWARD;
            int direction_R = BACKWARD;
        }
        while (encoder_L != encoder_max + 1 || encoder_R != encoder_max + 1)
        {
            if (encoder_L != encoder_max)
            {
                motor_L->run(direction_L);
            }
            else
            {
                motor_L->run(RELEASE);
            }

            if (encoder_R != encoder_max)
            {
                motor_R->run(direction_R);
            }
            else
            {
                motor_R->run(RELEASE);
            }
        }
        break;
    case 2:
        while (encoder_R != encoder_max + 1)
        {
            if (encoder_R != encoder_max)
            {
                motor_R->run(FORWARD);
            }
            else
            {
                motor_R->run(RELEASE);
            }
        }
        break;
    default:
        while (encoder_L != encoder_max + 1)
        {
            if (encoder_L != encoder_max)
            {
                motor_L->run(FORWARD);
            }
            else
            {
                motor_L->run(RELEASE);
            }
        }
        break;
    }
    encoder_L = 0;
    encoder_R = 0;
}

void wheel_encoder_increment_L() 
{ 
  encoder_L += 1; 
}

void wheel_encoder_increment_R() 
{ 
  encoder_R += 1; 
}

void setup()
{
    Serial.begin(9600);
    pinMode(2, INPUT); // change pin to real pin
    pinMode(3, INPUT); // change pin to real pin
    attachInterrupt(digitalPinToInterrupt(2), wheel_encoder_increment_L, CHANGE);
    attachInterrupt(digitalPinToInterrupt(3), wheel_encoder_increment_R, CHANGE);

    AFMS.begin()
}

void loop()
{
}