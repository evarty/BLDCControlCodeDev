#include <math.h>
#include <stdio.h>
#include <stdlib.h>


//These all take larger matrices than needed
//Because C needs to know array size at compile-time, they take 10x10 matrices
//The actual operations don't do that, they use defined matrix dimensions
//But the memory footprint is higher than it needs to be for smaller matrices
//Must define matrices as 10x10. Just fill the remaining with zeros.
void MatrixMultiply(float A[][10], float B[][10], int ADimRow, int ADimCol, int BDimRow, int BDimCol, float Result[][10]);
void MatrixAddition(float A[][10], float B[][10], int ADimRow, int ADimCol, float Result[][10]);
void MatrixSubtraction(float A[][10], float B[][10], int ADimRow, int ADimCol, float Result[][10]);
void MultiplyMatrixByConstant(float A[][10], float C, int ADimRow, int ADimCol, float Result[][10]);

int main(void){


    //FILE *Output;
    //Output = fopen("./Output.txt","w");
    //fprintf(Output, "Theta, USetpoint, VSetpoint, WSetpoint\n");

    int DimACol = 4;
    int DimARow = 4;
    float A[10][10] = {
        {1,8,3,0,0,0,0,0,0,0},
        {0,1,0,0,0,0,0,0,0,0},
        {0,2,1,0,0,0,0,0,0,0},
        {0,0,6,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},              
        {0,0,0,0,0,0,0,0,0,0},               
        {0,0,0,0,0,0,0,0,0,0},              
        {0,0,0,0,0,0,0,0,0,0},               
        {0,0,0,0,0,0,0,0,0,0}               
    };
    int DimBCol = 4;
    int DimBRow = 4;
    float B[10][10] = {
        {2,5,7,2,0,0,0,0,0,0},
        {7,9,3,4,0,0,0,0,0,0},
        {5,8,2,5,0,0,0,0,0,0},
        {8,4,9,3,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},              
        {0,0,0,0,0,0,0,0,0,0}
    };
    float C = 5;
    float Result[10][10] = {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
    };

    MatrixSubtraction(A, B, DimARow, DimACol, Result);
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            printf("%lf ", Result[i][j]);
        }
        printf("\n");
    }




}


//Multiplies matrices together
//This assumes that proper sized matrices are passed to it. Checks must be done outside the function.
void MatrixMultiply(float A[][10], float B[][10], int ADimRow, int ADimCol, int BDimRow, int BDimCol, float Result[][10]){

    for(int i = 0; i < ADimRow; i++){
        for(int j = 0; j < BDimCol; j++){
            Result[i][j] = 0;

            for(int k = 0; k < ADimCol; k++){
                Result[i][j] += A[i][k]*B[k][j];

            }
        }
    }
}

void MatrixAddition(float A[][10], float B[][10], int ADimRow, int ADimCol, float Result[][10]){

    for(int i = 0; i < ADimRow; i++){
        for(int j = 0; j < ADimCol; j++){
            Result[i][j] = A[i][j] + B[i][j];
        }
    }
}

void MatrixSubtraction(float A[][10], float B[][10], int ADimRow, int ADimCol, float Result[][10]){

    for(int i = 0; i < ADimRow; i++){
        for(int j = 0; j < ADimCol; j++){
            Result[i][j] = A[i][j] - B[i][j];
        }
    }
}

void MultiplyMatrixByConstant(float A[][10], float C, int ADimRow, int ADimCol, float Result[][10]){

    for(int i = 0; i < ADimRow; i++){
        for(int j = 0; j < ADimCol; j++){
            Result[i][j] = C*A[i][j];
        }
    }
}
