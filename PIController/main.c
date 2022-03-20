#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void PIControllerComputeIrregularSampleInterval(int Error, float Kp, float Ki, int PIArray[], int TimeStep, int OutputMax);
void PIControllerComputeRegularSampleInterval(int Error, float Kp, float Ki, int PIArray[], int OutputMax);

int main(void){
 
    
    FILE *Output;
    Output = fopen("./Output.txt","w");
    //fprintf(Output, "Valpha, VBeta, USetpoint, VSetpoint, WSetpoint\n");
    fprintf(Output, "Theta, USetpoint, VSetpoint, WSetpoint\n");

    //PI controller constants
    float Kp = 1;
    float Ki = 1;
    
    //Error variable
    int Error = 0;

    //Setpoint and Realpoint variables
    int Setpoint = 0;
    int Realpoint = 0;

    //Controller required variables
    int LastIntegralValue = 0;
    int TimeStep = 1;
    int OutputMax = 4800;

    //Array to be passed to and from the PI controller
    //[0] is the output. [1] is the integral term, with constant already in it
    int PIControllerArray[2] = {0,0};
    
    




}

int ComputErrorInt(int Setpoint, int Realpoint){

    return Setpoint - Realpoint;
}

//This takes the error, P and I constants
//current value of output and the integral term, and the time step.
//it returns the updated value of the output and the integral term
//the prior output doesn't actually do anything.
//also clamps to output to be in [-OuputMax, OutputMAx]
void PIControllerComputeIrregularSampleInterval(int Error, float Kp, float Ki, int PIArray[], int TimeStep, int OutputMax){

    int hold = 0;

    PIArray[1] += Error*TimeStep;
    hold = Kp*Error + Ki*PIArray[1];
    if(hold > OutputMax)
        PIArray[0] = OutputMax;
    else if(hold < -OutputMax)
        PIArray[0] = -OutputMax;
    else
        PIArray[0] = hold;

}



//This takes the error, P and I constants
//current value of output and the integral term, and the time step.
//it returns the updated value of the output and the integral term
//the prior output doesn't actually do anything.
//also clamps to output to be in [-OuputMax, OutputMAx]
//Assumes that it will be called at a regular interval, such as by timer interrupt
//PIArray[0] is the output.
//PIArray [1] is the running Integral output term
void PIControllerComputeRegularSampleInterval(int Error, float Kp, float Ki, int PIArray[], int OutputMax){

    //Compute the Integral Term.
    //First add in the new integral term contirubtion from current error
    //and current Ki value
    PIArray[1] += Ki*Error;

    //Prevent windup
    //This bit keeps the I term from growing without bound
    //int IntegralOutputTerm = Ki*PIArray[1];
    if(PIArray[1]/*IntegralOutputTerm*/ > OutputMax)
        PIArray[1]/*IntegralOutputTerm*/ = OutputMax;
    else if(PIArray[1]/*IntegralOutputTerm*/ < -OutputMax)
        PIArray[1]/*IntegralOutputTerm*/ = -Outputmax;

    PIArray[0] = Kp*Error + PIArray[1]/*IntegralOutputTerm*/;
    
    //Prevents the output from going outside the given range. 
    if(PIArray[0] > OutputMax)
        PIArray[0] = OutputMax;
    else if(PIArray[0] < -OutputMax)
        PIArray[0] = -OutputMax;
    else
        PIArray[0] = PIArray[0];

}
