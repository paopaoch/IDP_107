/*
    All servo movements function should be included in this file. test push
*/
#include <Servo.h>

// ---------INIT SERVO-------------
Servo servo_L;
Servo servo_R;
int servo_state = 0; // 0 is close left, 1 is close right, 2 is all close, 3 is all open
int CLOSE_R = 135;
int CLOSE_L = 65;
int OPEN_R = 30;
int OPEN_L = 160;
int pos_L;
int pos_R;
int grabber_speed = 20;

int BLOCK_NUMBER = 1; // current working block

void close_R()
{
    for (pos_R = OPEN_R; pos_R <= CLOSE_R; pos_R += 1)
    {

        servo_R.write(pos_R);
        delay(grabber_speed);
    }
}

void open_R()
{
    for (pos_R = CLOSE_R; pos_R >= OPEN_R; pos_R -= 1)
    {
        servo_R.write(pos_R);
        delay(grabber_speed);
    }
}

void close_L()
{
    for (pos_L = OPEN_L; pos_L >= CLOSE_L; pos_L -= 1)
    {
        servo_L.write(pos_L);
        delay(grabber_speed);
    }
}

void open_L()
{
    for (pos_L = CLOSE_L; pos_L <= OPEN_L; pos_L += 1)
    {
        servo_L.write(pos_L);
        delay(grabber_speed);
    }
}

void open_both()
{
    pos_L = CLOSE_L;
    for (pos_R = CLOSE_R; pos_R >= OPEN_R; pos_R -= 1)
    {
        servo_R.write(pos_R);
        servo_L.write(pos_L);
        delay(grabber_speed);
        pos_L += 1;
    }
}

void close_both()
{
    pos_L = OPEN_L;
    for (pos_R = OPEN_R; pos_R <= CLOSE_R; pos_R += 1)
    {
        servo_R.write(pos_R);
        servo_L.write(pos_L);
        delay(grabber_speed);

        pos_L -= 1;
    }
}

void toggle_servo(int orientation)
{
    switch (orientation)
    {
    case 0: // close right open left
        servo_R.write(135);
        servo_L.write(45);
        break;
    case 1: // open right close left
        servo_R.write(45);
        servo_L.write(135);
        break;
    case 2: // close right close left
        servo_R.write(135);
        servo_L.write(135);
        break;
    default: // open right open left
        servo_R.write(45);
        servo_L.write(45);
        break;
    }
}

void grabber_main()
{
    close_L();
    open_L();
    close_R();
    open_R();
    close_L();
    open_L();
    move_to_grab(MOVE_GRAB_LEFT);    // turn left
    move_to_grab(MOVE_GRAB_RIGHT);   // turn right
    move_to_grab(MOVE_GRAB_FORWARD); // move forward
    move_to_grab(MOVE_GRAB_RIGHT);   // turn right *for correction
    move_to_grab(MOVE_GRAB_LEFT);    // turn left *for correction
    move_to_grab(MOVE_GRAB_FORWARD); // move forward
    close_both();
}

void coarse_block_put_back(int distance = 500)
{
    if (BLOCK_NUMBER == 2 || BLOCK_NUMBER == 3)
    {
      rotate(TURN_RIGHT_BOTH);
      move_to_grab(MOVE_GRAB_FORWARD, distance + 800);
      open_both(); // open
      move_to_grab(MOVE_GRAB_BACKWARD, distance + 800);
      rotate(TURN_RIGHT_BOTH);
      open_both(); // open
    }
    else
    {
      rotate(TURN_RIGHT_FORWARD); // turn right while move forwards
      move_to_grab(MOVE_GRAB_FORWARD, distance);
      open_both(); // open
      move_to_grab(MOVE_GRAB_BACKWARD, distance);
      rotate(TURN_RIGHT_BACKWARD); // turn right while move backwards
    }
  
}

void fine_block_put_back(int distance = 500)
{
    if (BLOCK_NUMBER == 2 || BLOCK_NUMBER == 3)
    {
      rotate(TURN_LEFT_BOTH);
      move_to_grab(MOVE_GRAB_FORWARD, distance + 800);
      open_both(); // open
      move_to_grab(MOVE_GRAB_BACKWARD, distance + 800);
      close_both();
      rotate(TURN_LEFT_BOTH);
      open_both(); // open
    }
    else
    {
      rotate(TURN_LEFT_FORWARD); // turn right while move forwards
      move_to_grab(MOVE_GRAB_FORWARD, distance);
      open_both(); // open
      move_to_grab(MOVE_GRAB_BACKWARD, distance);
      rotate(TURN_LEFT_BACKWARD); // turn right while move backwards 
    }
}

void error_block_put_back(int distance = 500)
{
    rotate(TURN_AROUND); // turn around
    if (BLOCK_NUMBER == 1)
    {
        line_follow_main_rev(50); // line follow till back to line
        move_to_grab(MOVE_GRAB_FORWARD, distance);
    }
    else if (BLOCK_NUMBER == 2)
    {
        line_follow_main_rev(90); // line follow till back to line
        move_to_grab(MOVE_GRAB_FORWARD);
    }
    else if (BLOCK_NUMBER == 3)
    {
        line_follow_main_rev(90); // line follow till back to line
        move_to_grab(MOVE_GRAB_FORWARD, distance);
    }
}

void grabbing_third_block()
{
    close_both();
    backward(20);
    open_both();
    grabber_main();
}
