// This tests the Digital input. simply connest the digital port to a digital source. The onboard LED lights up when the digital input is high, and turns off when the input is low. do not forget to set the number of digital pin tested in the code as well
const int buttonPin = 5;     // the number of the digital port tested
int buttonState = 0; 
// variables will change:
const int linefollower_LR = 5;//key in the pin of left rear line follower here
const int linefollower_RR = 2;//key in the pin of right rear line follower here
const int linefollower_LF = 4; //key in the pin of left front line follower here
const int linefollower_RF = 3; //key in the pin of right front line follower here

int displacement_front;
int displacement_rear;
void setup() {
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
void loop() {
  // read the state of the digital pin:
 

  // check if the pin State is HIGH:
  refresh_displacement_value();
    // turn LED on:
    Serial.print("front");
    Serial.print(displacement_front);
    Serial.print("rear");
    Serial.println(displacement_rear);
  }
      
