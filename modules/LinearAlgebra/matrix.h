#ifndef MATRIX
#define MATRIX


typedef struct Matrix Matrix;

typedef struct Matrix{
	int columns;
	int rows;
	double** data;
	// functions
	void(*print)(char*, Matrix);
	Matrix(*multiply)(Matrix, Matrix);
	Matrix(*add)(Matrix, Matrix);
	Matrix(*subtract)(Matrix, Matrix);
	Matrix(*scale)(Matrix, const double);
	Matrix(*transpose)(Matrix);
} Matrix;


Matrix initMatrix(int rows, int columns, double defaultVal);
#endif // MATRIX
