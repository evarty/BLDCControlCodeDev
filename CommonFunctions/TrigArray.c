#include <math.h>

void ConstructSineArrayFullCircle(int SineArray[], int ArraySize){

    for(int i = 0; i < ArraySize; i++){
        SineArray[i] = sin((float)i*628318/ArraySize);

    }
}


void ConstructCosineArrayFullCircle(int CosineArray[], int ArraySize){

    for(int i = 0; i < ArraySize; i++){
        CosineArray[i] = cos((float)i*6.28318/ArraySize);

    }
}
