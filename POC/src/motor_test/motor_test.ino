//simply connect the motors in the motor shield, set the speed, upload the code, and off you go.
int k;

#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *motor_L = AFMS.getMotor(3);
Adafruit_DCMotor *motor_R = AFMS.getMotor(4);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  // Set the speed to start, from 0 (off) to 255 (max speed)


}
void move1(){ 
  k=200;
  motor_L->setSpeed(k);// Set the speed of motor 3, from 0 (off) to 255 (max speed)
  motor_L->run(FORWARD); // Set the direction of motor 3, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
  motor_R->setSpeed(k);// Set the speed of motor 4, from 0 (off) to 255 (max speed)
  motor_R->run(FORWARD); // Set the direction of motor 4, Use FORWARD to go forward and BACKWARD to go reverse, and RELEASE to not move it)
}
void loop() {
  
  move1();
  Serial.println(k);
 
  
}
