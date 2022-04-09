#ifndef MATRIXFUNCTIONS
#define MATRIXFUNCTIONS

//These all take larger matrices than needed
//Because C needs to know array size at compile-time, they take 10x10 matrices
//The actual operations don't do that, they use defined matrix dimensions
//But the memory footprint is higher than it needs to be for smaller matrices
//Must define matrices as 10x10. Just fill the remaining with zeros.
void MatrixMultiply(float A[][10], float B[][10], int ADimRow, int ADimCol, int BDimRow, int BDimCol, float Result[][10]);
void MatrixAddition(float A[][10], float B[][10], int ADimRow, int ADimCol, float Result[][10]);
void MatrixSubtraction(float A[][10], float B[][10], int ADimRow, int ADimCol, float Result[][10]);
void MultiplyMatrixByConstant(float A[][10], float C, int ADimRow, int ADimCol, float Result[][10]);
void DivideMatrixByConstant(float A[][10], float C, int ADimRow, int ADimCol, float Result[][10]);

#endif
