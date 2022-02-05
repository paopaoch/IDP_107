unsigned long time_cache;
int amber_led_state;
void setup() {

 pinMode(LED_BUILTIN, OUTPUT);
 time_cache = millis();
 amber_led_state=0;}
void loop() {
  delay (50);
  if ((millis()-time_cache)>250){
    if(amber_led_state==0){digitalWrite(LED_BUILTIN, HIGH);amber_led_state=1;time_cache = millis();}
    else{digitalWrite(LED_BUILTIN, LOW) ;amber_led_state=0;time_cache = millis();};};

 
}
