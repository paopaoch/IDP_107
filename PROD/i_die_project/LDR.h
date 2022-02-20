#define FINE_BLOCK 0
#define COARSE_BLOCK 1
#define ERROR_BLOCK 2

const int LDRinput = A0; // sets up the analogue pin A0

//const int coarseAvg = 400; // set average reading of coarse block
//const int fineAvg = 650;   // set averagereading of fine block
const int threshold = 520; // set the threshold offset of each block
const int lowerBound = 100;
int block_type;

int block_detect()
{
    if (analogRead(LDRinput) >= threshold)
    {
        return FINE_BLOCK;
    }
    else if (analogRead(LDRinput) < threshold && analogRead(LDRinput) >= lowerBound)
    {
        return COARSE_BLOCK;
    }
    else
    {
        return ERROR_BLOCK;
    }
}
