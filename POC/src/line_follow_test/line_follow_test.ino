
#include <Adafruit_MotorShield.h>

#define TIMER_INTERRUPT_DEBUG 2
#define _TIMERINTERRUPT_LOGLEVEL_ 4

#define USING_16MHZ true
#define USING_8MHZ false
#define USING_250KHZ false

#define USE_TIMER_0 false
#define USE_TIMER_1 true
#define USE_TIMER_2 false
#define USE_TIMER_3 false 

#define TIMER1_INTERVAL_MS 250
#define TIMER1_FREQUENCY (float)(1000.0f / TIMER1_INTERVAL_MS)
#define TIMER1_DURATION_MS 0 //(10 * TIMER1_INTERVAL_MS)
#define ADJUST_FACTOR ((float)0.99850)
#include "megaAVR_TimerInterrupt.h"

unsigned int outputPin = 8;

void blinkLED(unsigned int outputPin = 8)
{
  static bool toggle1 = false;
  static bool started = false;

  if (!started)
  {
    started = true;
    pinMode(outputPin, OUTPUT);
  }

  // timer interrupt toggles pin LED_BUILTIN
  digitalWrite(outputPin, toggle1);
  toggle1 = !toggle1;
}

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor_L = AFMS.getMotor(3);//key in the port the left motor is connected to here
Adafruit_DCMotor *motor_R = AFMS.getMotor(4);//key in the port the right motor is connected to here
int motor_L_speed;
int motor_R_speed;
const int linefollower_LR = 5;//key in the pin of left rear line follower here
const int linefollower_RR = 2;//key in the pin of right rear line follower here
const int linefollower_LF = 3; //key in the pin of left front line follower here
const int linefollower_RF = 4; //key in the pin of right front line follower here
const int k_f = 100;
const int k_r = 40;

int displacement_front;
int displacement_rear;
void setup() {
  AFMS.begin();
  pinMode(linefollower_LR, INPUT);  
  pinMode(linefollower_RR, INPUT);  
  pinMode(linefollower_LF, INPUT);  
  pinMode(linefollower_RF, INPUT);
  ITimer1.init();
  ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS * ADJUST_FACTOR, blinkLED, outputPin, TIMER1_DURATION_MS);
}
void refresh_displacement_value(){      //this function reads the data from the sensors, and updates the state of which wheel encoder is touching the left/right
  if(digitalRead(linefollower_LR)==digitalRead(linefollower_RR))
  {displacement_rear=0;}
  else{  
    if(digitalRead(linefollower_LR)==HIGH){displacement_rear=1;}
    else{displacement_rear=-1;};};

  if(digitalRead(linefollower_LF)==digitalRead(linefollower_RF))
  {displacement_front=0;}
  else{
    if(digitalRead(linefollower_LF)==HIGH){displacement_front=1;}
     else{displacement_front=-1;};};
  }
void line_follow(){//this function reads displacement constants, and update the motor speed, and move the motor}
  motor_L_speed=255;
  motor_R_speed=255;
  int line_follower_constant;
    line_follower_constant=k_r*displacement_rear-k_f*displacement_front;
    if (line_follower_constant>0){motor_L_speed=255-line_follower_constant;};
    if (line_follower_constant<0){motor_R_speed=255+line_follower_constant;};

  motor_L->setSpeed(motor_L_speed); 
  motor_L->run(FORWARD);
  motor_R->setSpeed(motor_R_speed);
  motor_R->run(FORWARD);
}

void loop() {
  refresh_displacement_value();
  line_follow();
}
