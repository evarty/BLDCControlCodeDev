#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void ConstructSineArrayFullCircle(float SineArray[], int ArraySize);
void ConstructCosineArrayFullCircle(float CosineArray[], int ArraySize);

int main(void){


    FILE *Output;
    Output = fopen("./Output.txt","w");
    fprintf(Output, "i, Sin(2(PI)i/ArraySize)\n");

    int SineArraySize = 3600;
    float SineArray[3600];

    ConstructSineArrayFullCircle(SineArray, SineArraySize);
    for(int i = 0; i < SineArraySize; i++){

        fprintf(Output, "%d, %lf\n", i, SineArray[i]);
    }


}


void ConstructSineArrayFullCircle(float SineArray[], int ArraySize){

    for(int i = 0; i < ArraySize; i++){
        SineArray[i] = sin((float)i*6.283185307/ArraySize);

    }
}


void ConstructCosineArrayFullCircle(float CosineArray[], int ArraySize){

    for(int i = 0; i < ArraySize; i++){
        CosineArray[i] = cos((float)i*6.283185307/ArraySize);

    }
}
