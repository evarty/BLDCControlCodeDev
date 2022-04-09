#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float ComputeVoltageStepSize(float MaxVoltage, int MaxADCValue);
float ConvertADCReadingToCurrent(int ADCReading, float VoltageStepSize, float ResistorValue);
void ClarkTransform(float ClarkCurrent[], float CurrentA, float CurrentB);
void ParkTransform(float ParkCurrent[], float ClarkCurrent[], float SinRotorAngle, float CosRotorAngle);

int main(void){


    //FILE *Output;
    //Output = fopen("./Output.txt","w");
    //fprintf(Output, "i, Sin(2(PI)i/ArraySize)\n");

    float MaxVoltage = 24;
    int MaxADCValue = 4095;
    float VoltageStep = 0;
    VoltageStep = ComputeVoltageStepSize(MaxVoltage, MaxADCValue);

    float Resistance = 0.01;
    int ADCReadingA = 2467;
    int ADCReadingB = 3296;

    float ACurrent = 0;
    float BCurrent = 0;

    ACurrent = ConvertADCReadingToCurrent(ADCReadingA, VoltageStep, Resistance);
    BCurrent = ConvertADCReadingToCurrent(ADCReadingB, VoltageStep, Resistance);

    float ClarkCurrent[] = {0,0};
    float ParkCurrent[] = {0,0};
    int RotorPosition = 2345;
    int MagneticSteps = 2000;
    float RotorAngleRad = 0;
    RotorAngleRad = RotorPosition % MagneticSteps;
    RotorAngleRad /= MagneticSteps;
    RotorAngleRad *= 6.28319;

    float SinRotorAngle = sin(RotorAngleRad);
    float CosRotorAngle = cos(RotorAngleRad);

    ClarkTransform(ClarkCurrent, ACurrent, BCurrent);
    ParkTransform(ParkCurrent, ClarkCurrent, SinRotorAngle, CosRotorAngle);

    printf("Rotor Position: %d, Magsteps: %d\n", RotorPosition, MagneticSteps);
    printf("Rotor Angle Radians: %lf\n", RotorAngleRad);
    printf("sin rotorangle: %lf, cos rotorangle: %lf\n", SinRotorAngle, CosRotorAngle);
    printf("Clark Alpha: %lf, Clark Beta: %lf\n", ClarkCurrent[0], ClarkCurrent[1]);
    printf("Park d: %lf, Park q: %lf\n", ParkCurrent[0], ParkCurrent[1]);



}

float ComputeVoltageStepSize(float MaxVoltage, int MaxADCValue){

    return MaxVoltage / ((float)MaxADCValue - 1.);

}

float ConvertADCReadingToCurrent(int ADCReading, float VoltageStepSize, float ResistorValue){

    return ResistorValue*((float)ADCReading * VoltageStepSize); 

}

void ClarkTransform(float ClarkCurrent[], float CurrentA, float CurrentB){

    ClarkCurrent[0] = CurrentA;
    ClarkCurrent[1] = CurrentA*0.57735 + CurrentB*1.15470;

}

void ParkTransform(float ParkCurrent[], float ClarkCurrent[], float SinRotorAngle, float CosRotorAngle){

    ParkCurrent[0] = ClarkCurrent[0]*CosRotorAngle + ClarkCurrent[1]*SinRotorAngle;
    ParkCurrent[1] = -ClarkCurrent[0]*SinRotorAngle + ClarkCurrent[1]*CosRotorAngle;

}

void InverseParkTransform(float InputVoltage[], float OutputVoltage[], float SinRotorAngle, float CosRotorAngle){

    OutputVoltage[0] = InputVoltage[0]*CosRotorAngle - InputVoltage[1]*SinRotorAngle;
    OutputVoltage[1] = InputVoltage[0]*SinRotorAngle + InputVoltage[1]*CosRotorAngle;

}
