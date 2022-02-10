
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor_L = AFMS.getMotor(3);//key in the port the left motor is connected to here
Adafruit_DCMotor *motor_R = AFMS.getMotor(4);//key in the port the right motor is connected to here
int motor_L_speed;
int motor_R_speed;
const int linefollower_LR = 5;//key in the pin of left rear line follower here
const int linefollower_RR = 2;//key in the pin of right rear line follower here
const int linefollower_LF = 4; //key in the pin of left front line follower here
const int linefollower_RF = 3; //key in the pin of right front line follower here
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
  Serial.begin(9600);
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
  Serial.print("line_follower_constant");
  Serial.println(line_follower_constant);
  motor_L->setSpeed(motor_L_speed); 
  motor_L->run(FORWARD);
  motor_R->setSpeed(motor_R_speed);
  motor_R->run(FORWARD);
}

void loop() {
  refresh_displacement_value();
  int line_follower_constant;
    line_follower_constant=k_r*displacement_rear-k_f*displacement_front;
    if (line_follower_constant>0){motor_L_speed=255-line_follower_constant;};
    if (line_follower_constant<0){motor_R_speed=255+line_follower_constant;};
  Serial.print("line_follower_constant");
  Serial.println(line_follower_constant);

}
