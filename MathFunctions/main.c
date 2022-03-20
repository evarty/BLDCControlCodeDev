#include <math.h>
#include <stdio.h>
#include <stdlib.h>


void MatrixMultiply(float A[][4], float B[][4], int ADimRow, int ADimCol, int BDimRow, int BDimCol, float Result[][4]);
void MatrixAddition(float A[][4], float B[][4], int ADimRow, int ADimCol, float Result[][4]);
void MatrixSubtraction(float A[][4], float B[][4], int ADimRow, int ADimCol, float Result[][4]);
void MultiplyMatrixByConstant(float A[][4], float C, int ADimRow, int ADimCol, float Result[][4]);

int main(void){


    FILE *Output;
    Output = fopen("./Output.txt","w");
    //fprintf(Output, "Valpha, VBeta, USetpoint, VSetpoint, WSetpoint\n");
    fprintf(Output, "Theta, USetpoint, VSetpoint, WSetpoint\n");

    float A[4][4] = {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    };
    float B[4][4] = {
        {2,5,7,2},
        {7,9,3,4},
        {5,8,2,5},
        {8,4,9,3}
    };
    float C = 5;
    float Result[4][4] = {
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    };

    MultiplyMatrixByConstant(A, C, 4, 4, Result);
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            printf("%lf ", Result[i][j]);
        }
        printf("\n");
    }




}


//Multiplies matrices together
//This assumes that proper sized matrices are passed to it. Checks must be done outside the function.
void MatrixMultiply(float A[][4], float B[][4], int ADimRow, int ADimCol, int BDimRow, int BDimCol, float Result[][4]){

    for(int i = 0; i < ADimRow; i++){
        for(int j = 0; j < BDimCol; j++){
            Result[i][j] = 0;

            for(int k = 0; k < ADimCol; k++){
                Result[i][j] += A[i][k]*B[k][j];

            }
        }
    }
}

void MatrixAddition(float A[][4], float B[][4], int ADimRow, int ADimCol, float Result[][4]){

    for(int i = 0; i < ADimRow; i++){
        for(int j = 0; j < ADimCol; j++){
            Result[i][j] = A[i][j] + B[i][j];
        }
    }
}

void MatrixSubtraction(float A[][4], float B[][4], int ADimRow, int ADimCol, float Result[][4]){

    for(int i = 0; i < ADimRow; i++){
        for(int j = 0; j < ADimCol; j++){
            Result[i][j] = A[i][j] - B[i][j];
        }
    }
}

void MultiplyMatrixByConstant(float A[][4], float C, int ADimRow, int ADimCol, float Result[][4]){

    for(int i = 0; i < ADimRow; i++){
        for(int j = 0; j < ADimCol; j++){
            Result[i][j] = C*A[i][j];
        }
    }
}
