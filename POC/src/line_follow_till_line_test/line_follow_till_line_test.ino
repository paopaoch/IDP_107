#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor_L = AFMS.getMotor(3);//key in the port the left motor is connected to here
Adafruit_DCMotor *motor_R = AFMS.getMotor(4);//key in the port the right motor is connected to here
int motor_L_speed;
int motor_R_speed;
const int linefollower_LR = 5;//key in the pin of left rear line follower here
const int linefollower_RR = 2;//key in the pin of right rear line follower here
const int linefollower_LF = 4; //key in the pin of left front line follower here
const int linefollower_RF = 3; //key in the pin of right front line follower here
const int encoder_L = 3;//key in the pin of left encoder here
const int encoder_R = 3;//key in the pin of right encoder here
const int k_f = 100;
const int k_r = 40;
bool not_at_the_line=true;
int encoder_L_count=0;
int encoder_R_count=0;

int displacement_front;
int displacement_rear;
void setup() {
  AFMS.begin();
  pinMode(linefollower_LR, INPUT);  
  pinMode(linefollower_RR, INPUT);  
  pinMode(linefollower_LF, INPUT);  
  pinMode(linefollower_RF, INPUT);
  pinMode(encoder_L,INPUT);
  pinMode(encoder_R,INPUT);
  attachInterrupt(digitalPinToInterrupt(encoder_L), wheel_encoder_L_increment, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder_R), wheel_encoder_R_increment, CHANGE);

//  ITimer2.init();
//  ITimer2.attachInterruptInterval(TIMER2_INTERVAL_MS * ADJUST_FACTOR, blinkLED, outputPin, TIMER2_DURATION_MS);
}
void wheel_encoder_L_increment() 
{ 
  encoder_L_count += 1; 
}
void wheel_encoder_R_increment() 
{ 
  encoder_R_count += 1; 
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
  
  if(digitalRead(linefollower_LF)==HIGH && digitalRead(linefollower_RF)==HIGH){not_at_the_line=false;}{not_at_the_line=true;};
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
void line_follow_main_rev(float rev_needed)//this function follow the line, untile the front sensors reach the line we need
{ 
    while(not_at_the_line||float(encoder_L_count)<12*rev_needed){
    refresh_displacement_value();
    line_follow();};
 encoder_L_count=0;
 encoder_R_count=0;
}
void loop() {
  line_follow_main_rev(1);
  while(true){
  delay(100);};
}
