#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor_L = AFMS.getMotor(3);//key in the port the left motor is connected to here
Adafruit_DCMotor *motor_R = AFMS.getMotor(4);//key in the port the right motor is connected to here
int motor_L_speed;
int motor_R_speed;

const int encoder_L = 7;//key in the pin of left encoder here
const int encoder_R = 6;//key in the pin of right encoder here

int encoder_L_count=0;
int encoder_R_count=0;

int displacement_front;
int displacement_rear;
void setup() {
  AFMS.begin();

  pinMode(encoder_L,INPUT);
  pinMode(encoder_R,INPUT);
  attachInterrupt(digitalPinToInterrupt(encoder_L), wheel_encoder_L_increment, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder_R), wheel_encoder_R_increment, CHANGE);


}
void wheel_encoder_L_increment() 
{ 
  encoder_L_count += 1; 
}
void wheel_encoder_R_increment() 
{ 
  encoder_R_count += 1; 
}
void kill_it()
{
  motor_L->run(RELEASE);
  motor_R->run(RELEASE);
}
void clear_encoder()
{
 encoder_L_count=0;
 encoder_R_count=0;
}

void rotate(int k){
  motor_L_speed=255;
  motor_R_speed=255;
  motor_L->setSpeed(motor_L_speed); 
  motor_R->setSpeed(motor_R_speed);
  clear_encoder();
  switch (k){   //+:turn right, -:turn left  method 1:move forward while turing  method 2:move backward while turning default:turn left 90 deg, not moving
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
    };
  while (encoder_L_count+encoder_R_count<19){
    delay(1);}
  kill_it();
  clear_encoder();
  }

void loop() {

  while(true){
  delay(100);};
}
