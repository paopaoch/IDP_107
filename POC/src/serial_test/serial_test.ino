     // this is a test to key in in the serial portal, and returns the same thing you typed to make sure the serial connection working
     char k;
void setup() {

     Serial.begin(9600);//sets the baud rate to 115200. do change the baud rate to this value in the portal as well


}

void loop() {
  if (Serial.available()) {
 k=Serial.read();
 delay (1);
 Serial.write(k);}
}
