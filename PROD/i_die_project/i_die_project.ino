#include <TimerOne.h>
#include <Adafruit_MotorShield.h>

int STATE = 1;

// INIT MOTOR
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor_L = AFMS.getMotor(3); // key in the port the left motor is connected to here
Adafruit_DCMotor *motor_R = AFMS.getMotor(4); // key in the port the right motor is connected to here
int motor_L_speed;
int motor_R_speed;
const int linefollower_LR = 5; // key in the pin of left rear line follower here
const int linefollower_RR = 2; // key in the pin of right rear line follower here
const int linefollower_LF = 4; // key in the pin of left front line follower here
const int linefollower_RF = 3; // key in the pin of right front line follower here
const int k_f = 100;
const int k_r = 40;
int displacement_front;
int displacement_rear;

// INIT LED
const int led = 6; // the pin with a LED
int ledState = LOW;

void setup(void)
{
    Serial.begin(9600);
    
    // *********SET UP BLINK***********
    pinMode(led, OUTPUT);
    Timer1.initialize(500000);        // set the interval 500000 is .5 secs
    Timer1.attachInterrupt(blinkLED); // attach blinkLED to the Timer as an interrupt

    // *********SET UP MOTOR***********
    pinMode(linefollower_LR, INPUT);
    pinMode(linefollower_RR, INPUT);
    pinMode(linefollower_LF, INPUT);
    pinMode(linefollower_RF, INPUT);
    AFMS.begin();
}

// ---------------------BLINK INTERUPT----------------------------------------
void blinkLED(void) // function to blink LED
{
    if (ledState == LOW)
    {
        ledState = HIGH;
    }
    else
    {
        ledState = LOW;
    }
    digitalWrite(led, ledState);
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

void loop()
{
    switch (STATE)
    {
    case 1:
        line_follow_main();
        break;
    default:
        line_follow_main();
        break;
    }
}
