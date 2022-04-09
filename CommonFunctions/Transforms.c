#include <math.h>

int ComputeVoltageStepSize(int MaxVoltage, int MaxADCValue){

    return MaxVoltage / (MaxADCValue - 1);

}

int ConvertADCReadingToCurrent(int ADCReading, int VoltageStepSize, int ResistorValue){

    return ResistorValue*(ADCReading * VoltageStepSize); 

}

void ClarkTransform(int ClarkCurrent[], int CurrentA, int CurrentB){

    ClarkCurrent[0] = CurrentA;
    ClarkCurrent[1] = CurrentA*57735 + CurrentB*115470;

}

void ParkTransform(int ParkCurrent[], int ClarkCurrent[], int SinRotorAngle, int CosRotorAngle){

    ParkCurrent[0] = ClarkCurrent[0]*CosRotorAngle + ClarkCurrent[1]*SinRotorAngle;
    ParkCurrent[1] = -ClarkCurrent[0]*SinRotorAngle + ClarkCurrent[1]*CosRotorAngle;

}

void InverseParkTransform(int InputVoltage[], int OutputVoltage[], int SinRotorAngle, int CosRotorAngle){

    OutputVoltage[0] = InputVoltage[0]*CosRotorAngle - InputVoltage[1]*SinRotorAngle;
    OutputVoltage[1] = InputVoltage[0]*SinRotorAngle + InputVoltage[1]*CosRotorAngle;

}
