int wheel_encoder_count;
void setup() {

Serial.begin(9600);
pinMode(2, INPUT);
attachInterrupt(digitalPinToInterrupt(2), wheel_encoder_increment, CHANGE) ;
}
void wheel_encoder_increment(){wheel_encoder_count=wheel_encoder_count+1;}
void loop() {
  Serial.println(wheel_encoder_count);
  delay(1000);
}