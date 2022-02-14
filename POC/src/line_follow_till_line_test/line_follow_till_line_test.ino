#include <Adafruit_MotorShield.h>
// just some info, the robot should go 187 cm forward, 110 cm back, and another 177 cm forward, another 155 cm back, another 205 cm forward, 185cm backward, and after the last block, and 74 cm back to starting position
//  convert to revolution, that is (8.52 rev, 5.019rev, 8.06 rev, 7.24 rev, 9.34 rev,8.61 rev and 3.37 rev), as the wheel perimeter is 21.94 cm.
//  for the rotation, it takes 1.654 rev on a single wheel to turn 90 deg(or in other words, 0.827 on both wheels to have 90 deg turn. double for 180 deg turn. )
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor_L = AFMS.getMotor(3); // key in the port the left motor is connected to here
Adafruit_DCMotor *motor_R = AFMS.getMotor(4); // key in the port the right motor is connected to here
int motor_L_speed;
int motor_R_speed;
const int linefollower_LR = 5; // key in the pin of left rear line follower here
const int linefollower_RR = 2; // key in the pin of right rear line follower here
const int linefollower_LF = 3; // key in the pin of left front line follower here
const int linefollower_RF = 4; // key in the pin of right front line follower here
const int encoder_L = 7;       // key in the pin of left encoder here
const int encoder_R = 6;       // key in the pin of right encoder here
const int k_f = 100;
const int k_r = -40;
int not_at_the_line = 0;
bool res;
int encoder_L_count = 0;
int encoder_R_count = 0;
int previous_reading_LF = 0;
int previous_reading_RF = 0;
int displacement_front;
int displacement_rear;
void setup()
{
  AFMS.begin();
  pinMode(linefollower_LR, INPUT);
  pinMode(linefollower_RR, INPUT);
  pinMode(linefollower_LF, INPUT);
  pinMode(linefollower_RF, INPUT);
  pinMode(encoder_L, INPUT);
  pinMode(encoder_R, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoder_L), wheel_encoder_L_increment, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder_R), wheel_encoder_R_increment, CHANGE);
  Serial.begin(9600);

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
    return true;
  }
  else
  {
    // ------This block will compare current reading with the most previous reading for robustness (need testing)-----
    if (digitalRead(linefollower_LF) == LOW && previous_reading_RF == LOW)
    {
      return true;
    }
    else if (previous_reading_LF == LOW && digitalRead(linefollower_RF) == LOW)
    {
      return true;
    }
    else
    {
      // set previous reading
      int previous_reading_LF = digitalRead(linefollower_LF);
      int previous_reading_RF = digitalRead(linefollower_RF);
      // ----------------------------------------------------------------------------------------------------------------

      return false;
    }
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
  while (!res ||
         encoder_L_count < rev_needed)
  {
    // while(true){
    res = refresh_displacement_value();
    line_follow();
    // if (res) {
    //   break;
    // }
  };
  motor_L->run(RELEASE);
  motor_R->run(RELEASE);
  encoder_L_count = 0;
  encoder_R_count = 0;
}
void loop()
{
  refresh_displacement_value();
  line_follow_main_rev(10);
  ;
  while (true)
  {
    delay(100);
  }
}
