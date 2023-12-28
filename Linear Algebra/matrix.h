#ifndef MATRIX
#define MATRIX

typedef struct Matrix{
	int columns;
	int rows;
	double** data;
} Matrix;


Matrix initMatrix(int rows, int columns, double** data);
double** initMatrixData(int rows, int columns);
void printMatrix(char* name, Matrix m);
Matrix MatrixMultiply(Matrix a, Matrix b);
Matrix MatrixAdd(Matrix a, Matrix b);
Matrix MatrixSubtract(Matrix a, Matrix b);
Matrix MatrixScale(double n, Matrix a);
Matrix MatrixTranspose(Matrix a);
#endif // MATRIX
