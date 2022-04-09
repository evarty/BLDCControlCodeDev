#include <math.h>


//Multiplies matrices together
//This assumes that proper sized matrices are passed to it. Checks must be done outside the function.
void MatrixMultiply(int A[][10], int B[][10], int ADimRow, int ADimCol, int BDimRow, int BDimCol, int Result[][10]){

    for(int i = 0; i < ADimRow; i++){
        for(int j = 0; j < BDimCol; j++){
            Result[i][j] = 0;

            for(int k = 0; k < ADimCol; k++){
                Result[i][j] += A[i][k]*B[k][j];

            }
        }
    }
}

void MatrixAddition(int A[][10], int B[][10], int ADimRow, int ADimCol, int Result[][10]){

    for(int i = 0; i < ADimRow; i++){
        for(int j = 0; j < ADimCol; j++){
            Result[i][j] = A[i][j] + B[i][j];
        }
    }
}

void MatrixSubtraction(int A[][10], int B[][10], int ADimRow, int ADimCol, int Result[][10]){

    for(int i = 0; i < ADimRow; i++){
        for(int j = 0; j < ADimCol; j++){
            Result[i][j] = A[i][j] - B[i][j];
        }
    }
}

void MultiplyMatrixByConstant(int A[][10], int C, int ADimRow, int ADimCol, int Result[][10]){

    for(int i = 0; i < ADimRow; i++){
        for(int j = 0; j < ADimCol; j++){
            Result[i][j] = C*A[i][j];
        }
    }
}

void DivideMatrixByConstant(int A[][10], int C, int ADimRow, int ADimCol, int Result[][10]){

    for(int i = 0; i < ADimRow; i++){
        for(int j = 0; j < ADimCol; j++){
            Result[i][j] = A[i][j]/C;
        }
    }
}


