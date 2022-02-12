// this program teste the analogue read of the analogue pins. It then outputs the reading via the serial communication in the port
const int LDRinput = A0; // sets up the analogue pin A0
// const int porousHigh = 900;
// const int porousLow = 700;

const int coarseAvg = 700;
const int fineAvg = 900;
const int threshold = 100;
void setup()
{
    // initialize the serial communications:
    Serial.begin(9600); // set the baud rate(9600 in this case）
}

void loop()
{
//    // Serial.println(analogRead(input1));
//    if (analogRead(LDRinput) < fineAvg + threshold && analogRead(LDRinput) >= fineAvg - threshold)
//    {
//        Serial.println("fine block");
//    }
//    else if (analogRead(LDRinput) < coarseAvg + threshold && analogRead(LDRinput) >= coarseAvg - threshold)
//    {
//        Serial.println("coarse block");
//    }
//    else
//    {
        Serial.println(analogRead(LDRinput));
//    }
    
}
