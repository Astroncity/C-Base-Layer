#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "headers/colors.h"


static void print(char* name, Matrix m);
static double** initMatrixData(int rows, int columns, double defaultVal);
static Matrix multiply(Matrix a, Matrix b);
static Matrix add(Matrix a, Matrix b);
static Matrix subtract(Matrix a, Matrix b);
static Matrix scale(Matrix a, const double constant);
static Matrix transpose(Matrix a);

static double** initMatrixData(int rows, int columns, double defaultVal){
	double** data = malloc(rows * sizeof(double*));
	for(int i = 0; i < rows; i++){
		data[i] = malloc(columns * sizeof(double));
	}
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			data[i][j] = defaultVal;
		}
	}
	return data;
}


Matrix initMatrix(int rows, int columns, double defaultVal){
	if(rows == 0 || columns == 0){
		printf("%s\n", "[ERROR] Cannot matrix of size 0");
		exit(1);
	}

	Matrix M;
	M.columns = columns;
	M.rows = rows;
	M.data = initMatrixData(rows, columns, defaultVal);
	// functions
	M.print = print;
	M.multiply = multiply;
	M.add = add;
	M.subtract = subtract;
	M.scale = scale;
	M.transpose = transpose;
	return M;
}


static Matrix multiply(Matrix a, Matrix b){
	if(a.rows != b.columns){
		printf("%s\n", "[ERROR] Invalid Matrices for multiplicaion.");
		exit(1);
	}

	Matrix resultMatrix = initMatrix(a.rows, b.columns, 0);

	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < b.columns; j++){
			double sum = 0;
			for(int k = 0; k < a.columns; k++){
				sum += a.data[i][k] * b.data[k][j];
			}
			resultMatrix.data[i][j] = sum;
		}
	}

	return resultMatrix;
}


static Matrix add(Matrix a, Matrix b){
	if(a.rows != b.rows || a.columns != b.columns){
		printf("%s\n", "[ERROR] Invalid Matrices for addition.");
		exit(1);
	}

	Matrix c = initMatrix(a.rows, a.columns, 0);

	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < a.columns; j++){
			c.data[i][j] = a.data[i][j] + b.data[i][j];
		}
	}
	return c;
}


static Matrix subtract(Matrix a, Matrix b){
	if(a.rows != b.rows || a.columns != b.columns){
		printf("%s\n", "[ERROR] Invalid Matrices for subtraction.");
		exit(1);
	}

	Matrix c = initMatrix(a.rows, a.columns, 0);

	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < a.columns; j++){
			c.data[i][j] = a.data[i][j] - b.data[i][j];
		}
	}
	return c;
}


static Matrix scale(Matrix a, const double constant){
	Matrix c = initMatrix(a.rows, a.columns, 0);

	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < a.columns; j++){
			c.data[i][j] = a.data[i][j] * constant;
		}
	}
	return c;
}


static Matrix transpose(Matrix a){
	Matrix c = initMatrix(a.columns, a.rows, 0);

	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < a.columns; j++){
			c.data[j][i] = a.data[i][j];
		}
	}
	return c;
}


static void print(char* name, Matrix m){
	printf("%s", FAINTRED);
	printf("Matrix %s:\n", name);
	printf("%s", RESET);
	printf("%s", FAINTBLUE);
	for(int i = 0; i < m.rows; i++){
		printf("%s", "|");
		for(int j = 0; j < m.columns; j++){
			printf("%f", m.data[i][j]);
			//print space if not last column
			if(j != m.columns - 1){
				printf("%s", " ");
			}
		}
		printf("%s", "|");
		printf("\n");
	}
	printf("\n");
	printf("%s", RESET);
}