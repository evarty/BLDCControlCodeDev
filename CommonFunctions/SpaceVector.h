#ifndef SPACEVECTOR
#define SPACEVECTOR

void SpaceVector(int VAlpha, int VBeta, int DCLinkVoltage, float PulsePeriod, int PWMMaxValue, int PWMReturnValues[]);
void PhaseCorrectPWMSimulate(int MaxValue, int SetValue, char name[]);

#endif
