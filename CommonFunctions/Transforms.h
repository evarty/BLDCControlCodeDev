#ifndef FOCTRANSFORMS
#define FOCTRANSFORMS

int ComputeVoltageStepSize(int MaxVoltage, int MaxADCValue);
int ConvertADCReadingToCurrent(int ADCReading, int VoltageStepSize, int ResistorValue);
void ClarkTransform(int ClarkCurrent[], int CurrentA, int CurrentB);
void ParkTransform(int ParkCurrent[], int ClarkCurrent[], int SinRotorAngle, int CosRotorAngle);

#endif
