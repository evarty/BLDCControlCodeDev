#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ONEOVERROOTTHREE 0.57735
#define TWOOVERROOTTHREE 1.15470
#define PI 3.14159

//Int based definitions. Just multiplying them by 10,000
#define ONEOVERROOTTHREEINT 5774
#define TWOOVERROOTTHREEINT 11457
#define PIINT 31416

void SpaceVector(float VAlpha, float VBeta, float DCLinkVoltage, float PulsePeriod, int PWMMaxValue, int PWMReturnValues[]);
//void SpaceVectorInt(float VAlpha, float VBeta, float DCLinkVoltage, float PulsePeriod, int PWMMaxValue, int PWMReturnValues[]);
void PhaseCorrectPWMSimulate(int MaxValue, int SetValue, char name[]);

int main(void){
 
    //float RotorPosition = 0;
    //float TorqueControlInput = 0;
    //float UOut = 0;
    //float VOut = 0;
    //float WOut = 0;
    int Setpoints[3] = {0,0,0};
    float MaxDC = 24;
    float VAlpha = 0;
    float VBeta = 0;
    float PulsePeriod = 1;
    int PWMMax = 4800;
    //float theta = 0;
    float length = 6;
    int SetValue = 600;//Out of 3600
    char name1[50] = "./OutputPWM1.txt";
    char name2[50] = "./OutputPWM2.txt";
    char name3[50] = "./OutputPWM3.txt";

    FILE *Output;
    Output = fopen("./Output.txt","w");
    //fprintf(Output, "Valpha, VBeta, USetpoint, VSetpoint, WSetpoint\n");
    fprintf(Output, "Theta, USetpoint, VSetpoint, WSetpoint\n");

    FILE *OutputImp;
    OutputImp = fopen("./OutputImp.txt","w");
    fprintf(OutputImp, "Theta, USetpoint, VSetpoint, WSetpoint\n");

    FILE *OutputPWM;
    OutputPWM = fopen("./OutputPWM.txt","w");
    fprintf(OutputPWM, "Setpoint, CounterValue, PWM Output\n");


    //for(float j = 0; j < 14; j++){
        for(int i = 0; i < 3600; i++){
            VAlpha = /*j*cos(i/1800.*PI);*/length*cos(i/1800.*PI);
            VBeta = /*j*sin(i/1800.*PI);*/length*sin(i/1800.*PI);
            //printf("VAlpha: %lf, VBeta: %lf\n", VAlpha, VBeta);
            //printf("Angle: %d ", i);
            SpaceVector(VAlpha, VBeta, MaxDC, PulsePeriod, PWMMax, Setpoints);
            //fprintf(Output, "%lf %lf %d %d %d\n", VAlpha, VBeta, Setpoints[0], Setpoints[1], Setpoints[2]);
            fprintf(Output, "%d %d %d %d\n", i, Setpoints[0], Setpoints[1], Setpoints[2]);
            //SpaceVectorIMP((int)(10000*VAlpha), (int)(10000*VBeta), (int)(10000*MaxDC), (int)(10000*PulsePeriod), PWMMax, Setpoints);
            //fprintf(OutputImp, "%d %d %d %d\n", i, Setpoints[0], Setpoints[1], Setpoints[2]);
            if(i == SetValue){
                PhaseCorrectPWMSimulate(PWMMax, Setpoints[0], name1);
                PhaseCorrectPWMSimulate(PWMMax, Setpoints[1], name2);
                PhaseCorrectPWMSimulate(PWMMax, Setpoints[2], name3);
            }
        }
    //}

    //PhaseCorrectPWMSimulate(PWMMax, SetValue);

    //fprintf(Output, "%lf %lf %lf %lf %lf\n", RotorPosition, TorqueControlInput, Output[0], Output[1], Output[2]);

}

void SpaceVector(float VAlpha, float VBeta, float DCLinkVoltage, float PulsePeriod, int PWMMaxValue, int PWMReturnValues[]){

    float a = 0;
    float b = 0;
    float c = 0;
    int Quadrant = 0;
    int Sector = 0;
    float ur = 0;
    float ul = 0;
    float umax = 0.6666666*DCLinkVoltage;
    float Tr = 0;
    float Tl = 0;
    float T0 = 0;
    //float T7 = 0;
    int uSetpoint = 0;
    int vSetpoint = 0;
    int wSetpoint = 0;


    //define terms needed for the computation and sector identification
    a = fabs(VAlpha) + ONEOVERROOTTHREE*fabs(VBeta);
    b = fabs(VAlpha) - ONEOVERROOTTHREE*fabs(VBeta);
    c = TWOOVERROOTTHREE*fabs(VBeta);


    //Identify sector and quadrant.
    if(VBeta < 0){
        if(VAlpha < 0){
            Quadrant = 3;
            if(b < 0){
                Sector = 5;
            }else{
                Sector = 4;
            }
        }else{
            Quadrant = 4;
            if(b < 0){
                Sector = 5;
            }else{
                Sector = 6;
            }
        }
    }else{
        if(VAlpha < 0){
            Quadrant = 2;
            if(b < 0){
                Sector = 2;
            }else{
                Sector = 3;
            }
        }else{
            Quadrant = 1;
            if(b < 0){
                Sector = 2;
            }else{
                Sector = 1;
            }
        }
    }

    //printf("Sector: %d, Quadrant: %d\n", Sector, Quadrant);
    //printf("a: %lf, b: %lf, c:%lf\n", a, b, c);
    //The Quadrant and Sector stuff works correctly. Which also implies that a, b, and c are calculated correctly.

    //Now, we have a, b, and c along with the sector and quadrant.
    //With this, we can simply look up the moduli of the vector to the left and the right of the given vector.
    if(Sector == 1 && Quadrant == 1){
        ur = b;
        ul = c;
    }else if(Sector == 2 && Quadrant == 1){
        ur = a;
        ul = -b;
    }else if(Sector == 2 && Quadrant == 2){
        ur = -b;
        ul = a;
    }else if(Sector == 3 && Quadrant == 2){
        ur = c;
        ul = b;
    }else if(Sector == 4 && Quadrant == 3){
        ur = b;
        ul = c;
    }else if(Sector == 5 && Quadrant == 3){
        ur = a;
        ul = -b;
    }else if(Sector == 5 && Quadrant == 4){
        ur = -b;
        ul = a;
    }else if(Sector == 6 && Quadrant == 4){
        ur = c;
        ul = b;
    }else{
        ur = 0;
        ul = 0;
    }

    
    //Now we have ur and ul and can easily get the switching times for r and l
    Tr = PulsePeriod*fabs(ur)/umax;
    Tl = PulsePeriod*fabs(ul)/umax;
    T0 = (PulsePeriod - Tr - Tl)/2.;//had been 2.

    //Now we have the switching times for all 4 states used in one cycle. We also have the Sector, so we know which vectors ur and ul are.
    //I am assuming phase correct PWM. When the PWM counter is less than the setpoint, the pair controlled by that PWM is connected to ground. When the counter is greater than the setpoint, the pair is connected to the DC Link Voltage.
    //So, say we are looking at u. if the counter is 100 and the setpoint is 200, u is connected to ground. if the counter is 300, u is connected to high DC voltage. 
    //Phase correct means the counter counts up from 0 to the max pwm value, then back down to zero.
    if(Sector == 1){
        uSetpoint = (PWMMaxValue)*T0/PulsePeriod;
        vSetpoint = (PWMMaxValue)*(T0 + Tr)/PulsePeriod;
        wSetpoint = (PWMMaxValue)*(T0 + Tr + Tl)/PulsePeriod;//1. - T7/PulsePeriod);
    }else if(Sector == 2){
        vSetpoint = (PWMMaxValue)*T0/PulsePeriod;
        uSetpoint = (PWMMaxValue)*(T0 + Tl)/PulsePeriod;
        wSetpoint = (PWMMaxValue)*(T0 + Tr + Tl)/PulsePeriod;//1. - T7/PulsePeriod);       wSetpoint = (PWMMaxValue)*(1. - T7/PulsePeriod);
    }else if(Sector == 3){
        vSetpoint = (PWMMaxValue)*T0/PulsePeriod;
        wSetpoint = (PWMMaxValue)*(T0 + Tr)/PulsePeriod;
        uSetpoint = (PWMMaxValue)*(T0 + Tr + Tl)/PulsePeriod;//1. - T7/PulsePeriod);       uSetpoint = (PWMMaxValue)*(1. - T7/PulsePeriod);
    }else if(Sector == 4){
        wSetpoint = (PWMMaxValue)*T0/PulsePeriod;
        vSetpoint = (PWMMaxValue)*(T0 + Tl)/PulsePeriod;
        uSetpoint = (PWMMaxValue)*(T0 + Tr + Tl)/PulsePeriod;//1. - T7/PulsePeriod);       uSetpoint = (PWMMaxValue)*(1. - T7/PulsePeriod);
    }else if(Sector == 5){
        wSetpoint = (PWMMaxValue)*T0/PulsePeriod;
        uSetpoint = (PWMMaxValue)*(T0 + Tr)/PulsePeriod;
        vSetpoint = (PWMMaxValue)*(T0 + Tr + Tl)/PulsePeriod;//1. - T7/PulsePeriod);       vSetpoint = (PWMMaxValue)*(1. - T7/PulsePeriod);
    }else if(Sector == 6){
        uSetpoint = (PWMMaxValue)*T0/PulsePeriod;
        wSetpoint = (PWMMaxValue)*(T0 + Tl)/PulsePeriod;
        vSetpoint = (PWMMaxValue)*(T0 + Tr + Tl)/PulsePeriod;//1. - T7/PulsePeriod);       vSetpoint = (PWMMaxValue)*(1. - T7/PulsePeriod);
    }else{
        uSetpoint = 0;
        vSetpoint = 0;
        wSetpoint = 0;
    }
    
    //So, we have the u, v, and w setpoints for phase correct PWM. Put them into the return array so they can be accessed once this function ends.
    PWMReturnValues[0] = uSetpoint;
    PWMReturnValues[1] = vSetpoint;
    PWMReturnValues[2] = wSetpoint;

}


void PhaseCorrectPWMSimulate(int MaxValue, int SetValue, char name[]){
    
    int PWMCounterValue = 0;
    int PWMOutput = 0;
    int Steps = 0;
    
    FILE *OutputPWM;
    OutputPWM = fopen(name,"w");
    fprintf(OutputPWM, "Setpoint, CounterValue, PWM Output\n");


    while(PWMCounterValue <=MaxValue){
        if(PWMCounterValue >= SetValue){
            PWMOutput = 1;
        }else{
            PWMOutput = 0;
        }
        fprintf(OutputPWM, "%d %d %d\n", SetValue, Steps, PWMOutput);
        PWMCounterValue++;
        Steps++;
    }
    while(PWMCounterValue >= 0){
        if(PWMCounterValue >= SetValue){
            PWMOutput = 1;
        }else{
            PWMOutput = 0;
        }
        fprintf(OutputPWM, "%d %d %d\n", SetValue, Steps, PWMOutput);
        PWMCounterValue--;
        Steps++;
    }
}



void SpaceVectorInt(float VAlpha, float VBeta, float DCLinkVoltage, float PulsePeriod, int PWMMaxValue, int PWMReturnValues[]){

    float a = 0;
    float b = 0;
    float c = 0;
    int Quadrant = 0;
    int Sector = 0;
    float ur = 0;
    float ul = 0;
    float umax = 0.6666666*DCLinkVoltage;
    float Tr = 0;
    float Tl = 0;
    float T0 = 0;
    //float T7 = 0;
    int uSetpoint = 0;
    int vSetpoint = 0;
    int wSetpoint = 0;


    //define terms needed for the computation and sector identification
    a = fabs(VAlpha) + ONEOVERROOTTHREE*fabs(VBeta);
    b = fabs(VAlpha) - ONEOVERROOTTHREE*fabs(VBeta);
    c = TWOOVERROOTTHREE*fabs(VBeta);


    //Identify sector and quadrant.
    if(VBeta < 0){
        if(VAlpha < 0){
            Quadrant = 3;
            if(b < 0){
                Sector = 5;
            }else{
                Sector = 4;
            }
        }else{
            Quadrant = 4;
            if(b < 0){
                Sector = 5;
            }else{
                Sector = 6;
            }
        }
    }else{
        if(VAlpha < 0){
            Quadrant = 2;
            if(b < 0){
                Sector = 2;
            }else{
                Sector = 3;
            }
        }else{
            Quadrant = 1;
            if(b < 0){
                Sector = 2;
            }else{
                Sector = 1;
            }
        }
    }

    //printf("Sector: %d, Quadrant: %d\n", Sector, Quadrant);
    //printf("a: %lf, b: %lf, c:%lf\n", a, b, c);
    //The Quadrant and Sector stuff works correctly. Which also implies that a, b, and c are calculated correctly.

    //Now, we have a, b, and c along with the sector and quadrant.
    //With this, we can simply look up the moduli of the vector to the left and the right of the given vector.
    if(Sector == 1 && Quadrant == 1){
        ur = b;
        ul = c;
    }else if(Sector == 2 && Quadrant == 1){
        ur = a;
        ul = -b;
    }else if(Sector == 2 && Quadrant == 2){
        ur = -b;
        ul = a;
    }else if(Sector == 3 && Quadrant == 2){
        ur = c;
        ul = b;
    }else if(Sector == 4 && Quadrant == 3){
        ur = b;
        ul = c;
    }else if(Sector == 5 && Quadrant == 3){
        ur = a;
        ul = -b;
    }else if(Sector == 5 && Quadrant == 4){
        ur = -b;
        ul = a;
    }else if(Sector == 6 && Quadrant == 4){
        ur = c;
        ul = b;
    }else{
        ur = 0;
        ul = 0;
    }

    
    //Now we have ur and ul and can easily get the switching times for r and l
    Tr = PulsePeriod*fabs(ur)/umax;
    Tl = PulsePeriod*fabs(ul)/umax;
    T0 = (PulsePeriod - Tr - Tl)/2.;//had been 2.

    //Now we have the switching times for all 4 states used in one cycle. We also have the Sector, so we know which vectors ur and ul are.
    //I am assuming phase correct PWM. When the PWM counter is less than the setpoint, the pair controlled by that PWM is connected to ground. When the counter is greater than the setpoint, the pair is connected to the DC Link Voltage.
    //So, say we are looking at u. if the counter is 100 and the setpoint is 200, u is connected to ground. if the counter is 300, u is connected to high DC voltage. 
    //Phase correct means the counter counts up from 0 to the max pwm value, then back down to zero.
    if(Sector == 1){
        uSetpoint = (PWMMaxValue)*T0/PulsePeriod;
        vSetpoint = (PWMMaxValue)*(T0 + Tr)/PulsePeriod;
        wSetpoint = (PWMMaxValue)*(T0 + Tr + Tl)/PulsePeriod;//1. - T7/PulsePeriod);
    }else if(Sector == 2){
        vSetpoint = (PWMMaxValue)*T0/PulsePeriod;
        uSetpoint = (PWMMaxValue)*(T0 + Tl)/PulsePeriod;
        wSetpoint = (PWMMaxValue)*(T0 + Tr + Tl)/PulsePeriod;//1. - T7/PulsePeriod);       wSetpoint = (PWMMaxValue)*(1. - T7/PulsePeriod);
    }else if(Sector == 3){
        vSetpoint = (PWMMaxValue)*T0/PulsePeriod;
        wSetpoint = (PWMMaxValue)*(T0 + Tr)/PulsePeriod;
        uSetpoint = (PWMMaxValue)*(T0 + Tr + Tl)/PulsePeriod;//1. - T7/PulsePeriod);       uSetpoint = (PWMMaxValue)*(1. - T7/PulsePeriod);
    }else if(Sector == 4){
        wSetpoint = (PWMMaxValue)*T0/PulsePeriod;
        vSetpoint = (PWMMaxValue)*(T0 + Tl)/PulsePeriod;
        uSetpoint = (PWMMaxValue)*(T0 + Tr + Tl)/PulsePeriod;//1. - T7/PulsePeriod);       uSetpoint = (PWMMaxValue)*(1. - T7/PulsePeriod);
    }else if(Sector == 5){
        wSetpoint = (PWMMaxValue)*T0/PulsePeriod;
        uSetpoint = (PWMMaxValue)*(T0 + Tr)/PulsePeriod;
        vSetpoint = (PWMMaxValue)*(T0 + Tr + Tl)/PulsePeriod;//1. - T7/PulsePeriod);       vSetpoint = (PWMMaxValue)*(1. - T7/PulsePeriod);
    }else if(Sector == 6){
        uSetpoint = (PWMMaxValue)*T0/PulsePeriod;
        wSetpoint = (PWMMaxValue)*(T0 + Tl)/PulsePeriod;
        vSetpoint = (PWMMaxValue)*(T0 + Tr + Tl)/PulsePeriod;//1. - T7/PulsePeriod);       vSetpoint = (PWMMaxValue)*(1. - T7/PulsePeriod);
    }else{
        uSetpoint = 0;
        vSetpoint = 0;
        wSetpoint = 0;
    }
    
    //So, we have the u, v, and w setpoints for phase correct PWM. Put them into the return array so they can be accessed once this function ends.
    PWMReturnValues[0] = uSetpoint;
    PWMReturnValues[1] = vSetpoint;
    PWMReturnValues[2] = wSetpoint;

}


