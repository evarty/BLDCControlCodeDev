#ifndef PIController
#define PIController

void PIControllerComputeIrregularSampleInterval(int Error, int Kp, int Ki, int PIArray[], int TimeStep, int OutputMax);

void PIControllerComputeRegularSampleInterval(int Error, int Kp, int Ki, int PIArray[], int OutputMax);

int ComputeError(int Setpoint, int Realpoint);

#endif
