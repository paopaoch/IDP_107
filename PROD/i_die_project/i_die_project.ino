#include "movement.h"
#include "graber.h"
#include "LDR.h"
#include "shine_LED.h"
// pao just some info, the robot should go 187 cm forward, 110 cm back, and another 177 cm forward, another 155 cm back, another 205 cm forward, 185cm backward, and after the last block, and 74 cm back to starting position
// convert to revolution, that is (8.52 rev, 5.019rev, 8.06 rev, 7.24 rev, 9.34 rev,8.61 rev and 3.37 rev), as the wheel perimeter is 21.94 cm.
// for the rotation, it takes 1.654 rev on a single wheel to turn 90 deg(or in other words, 0.827 on both wheels to have 90 deg turn. double for 180 deg turn. )

int STATE = 1;
void setup(void)
{
    //    Serial.begin(9600);
    // *********SET UP LED*************
    pinMode(outputPinGreen, OUTPUT);
    pinMode(outputPinRed, OUTPUT);

    // *********SET UP MOTOR***********
    pinMode(linefollower_LR, INPUT);
    pinMode(linefollower_RR, INPUT);
    pinMode(linefollower_LF, INPUT);
    pinMode(linefollower_RF, INPUT);
    pinMode(encoder_L, INPUT);
    pinMode(encoder_R, INPUT);
    attachInterrupt(digitalPinToInterrupt(encoder_L), wheel_encoder_L_increment, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoder_R), wheel_encoder_R_increment, CHANGE);
    AFMS.begin();

    // *********SET UP SERVO***********
    servo_L.attach(10); // this is to attach servo to object, pin 10 for servo1, pin 9 for servo 2
    servo_R.attach(9);  // this is to attach servo to object, pin 10 for servo1, pin 9 for servo 2
    servo_R.write(OPEN_R);
    servo_L.write(OPEN_L);
    delay(3000);
}

void loop()
{
    switch (STATE)
    {
    case 1: // move robot to block
        if (BLOCK_NUMBER == 1)
        {
            line_follow_main_rev(90, 100);
        }
        else if (BLOCK_NUMBER == 2)
        {
            line_follow_main_rev(40, 60);
            delay(500);
            line_follow_main_rev(10, 25);
        }
        else if (BLOCK_NUMBER == 3)
        {
            line_follow_main_rev(40, 60);
            delay(500);
            line_follow_main_rev(10, 25);
            delay(500);
            forward(20);
        }
        
        else if (BLOCK_NUMBER == 4)
        {
            STATE = 7;
            break;
        }
        STATE = 2;
        break;
    case 2:
        if (BLOCK_NUMBER == 1 || BLOCK_NUMBER == 2)
        {
            grabber_main(); // grab the block
        }
        else if (BLOCK_NUMBER == 3)
        {
            grabbing_third_block(); // grab the 3rd block
        }
        STATE = 3;
        delay(1000);
        break;
    case 3: // detect block type
//        block_type = block_detect();
//        if (block_type == ERROR_BLOCK)
//        {
//            for (size_t i = 0; i < 3; i++)
//            {
//                move_to_grab(MOVE_GRAB_BACKWARD);
//            }
//            open_both();
//        }
//        else
//        {
//            STATE = 4;
//            switch (block_type)
//            {
//            case FINE_BLOCK:
//                shineGreen();
//                break;
//            case COARSE_BLOCK:
//                shineRed();
//                break;
//            default:
//                delay(1000);
//                break;
//            }
//        }
          STATE = 4;
          block_type = FINE_BLOCK;
        break;
    case 4: // turn around
        rotate(TURN_AROUND);
        STATE = 5;
        break;
    case 5: // bring robot back
        if (BLOCK_NUMBER == 2 || BLOCK_NUMBER == 3)
        {
            line_follow_main_rev(5, 10); // line follow till back to line
        }
        line_follow_main_rev(30, 45);
        STATE = 6;
        break;
    case 6:                             // logic for putting block in the right box
        if (block_type == COARSE_BLOCK) // logic for coarse block
        {
            dimRed();
            coarse_block_put_back(700);
        }
        else if (block_type == FINE_BLOCK) // logic for fine block
        {
            dimGreen();
            fine_block_put_back(700);
        }
        else // error handling if fail to read block (this code should not run in theory as case 3 should remain in loop if block reads error)
        {
            error_block_put_back(500);
            break;
        }
        STATE = 1;
        BLOCK_NUMBER += 1;
        break;
    case 7:
        rotate(TURN_AROUND); // turn around
        line_follow_main_rev(10, 15);
        move_to_grab(MOVE_GRAB_FORWARD, 1000);
        forward(20);
        servo_R.write(CLOSE_R);
        servo_L.write(CLOSE_L);
        while (true)
        {
            delay(100);
        }

    default:
        break;
    }
}
