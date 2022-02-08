#include "arv_blink_wifi_rev_config.h"
#include "graber.h"
#include "movement.h"

void setup(void)
{
    Serial.begin(9600);

    // *********SET UP BLINK***********
    ITimer1.init();
    ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS * ADJUST_FACTOR, blinkLED, outputPin, TIMER1_DURATION_MS);

    // *********SET UP MOTOR***********
    pinMode(linefollower_LR, INPUT);
    pinMode(linefollower_RR, INPUT);
    pinMode(linefollower_LF, INPUT);
    pinMode(linefollower_RF, INPUT);
    AFMS.begin();

    // *********SET UP SERVO***********
    servo_L.attach(9);  // this is to attach servo to object, pin 10 for servo1, pin 9 for servo 2
    servo_R.attach(10); // this is to attach servo to object, pin 10 for servo1, pin 9 for servo 2
}

void loop()
{
    switch (STATE)
    {
    case 1:
        line_follow_main();
        break;
    case 2:
        grabber_main();
        STATE = 1;
        break;
    default:
        break;
    }
}
