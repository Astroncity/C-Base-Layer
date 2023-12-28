#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include <math.h>


Matrix MatrixMultiply(Matrix a, Matrix b){
	if(a.columns != b.rows){
		printf("Error: cannot multiply matricies, incompatible sizes");
		exit(1);
	}

	double** data = initMatrixData(a.rows, b.columns);

	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < b.columns; j++){
			for(int k = 0; k < a.columns; k++){
				data[i][j] += a.data[i][k] * b.data[k][j];
			}
		}
	}

	Matrix m;
	m.rows = a.rows;
	m.columns = b.columns;
	m.data = data;
	return m;
}


Matrix MatrixAdd(Matrix a, Matrix b){
	if(a.rows != b.rows || a.columns != b.columns){
		printf("Error: cannot add matricies, incompatible sizes");
		exit(1);
	}

	double** data = initMatrixData(a.rows, a.columns);

	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < a.columns; j++){
			data[i][j] = a.data[i][j] + b.data[i][j];
		}
	}

	Matrix m;
	m.rows = a.rows;
	m.columns = a.columns;
	m.data = data;
	return m;
}


Matrix MatrixSubstract(Matrix a, Matrix b){
	if(a.rows != b.rows || a.columns != b.columns){
		printf("Error: cannot substract matricies, incompatible sizes");
		exit(1);
	}

	double** data = initMatrixData(a.rows, a.columns);

	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < a.columns; j++){
			data[i][j] = a.data[i][j] - b.data[i][j];
		}
	}

	Matrix m;
	m.rows = a.rows;
	m.columns = a.columns;
	m.data = data;
	return m;
}


Matrix MatrixScale(double n, Matrix a){
	double** data = initMatrixData(a.rows, a.columns);

	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < a.columns; j++){
			data[i][j] = a.data[i][j] * n;
		}
	}

	Matrix m;
	m.rows = a.rows;
	m.columns = a.columns;
	m.data = data;
	return m;
}


Matrix MatrixTranspose(Matrix a){
	double** data = initMatrixData(a.columns, a.rows);

	for(int i = 0; i < a.rows; i++){
		for(int j = 0; j < a.columns; j++){
			data[j][i] = a.data[i][j];
		}
	}

	Matrix m;
	m.rows = a.columns;
	m.columns = a.rows;
	m.data = data;
	return m;
}

double** initMatrixData(int rows, int columns){
	double** data = malloc(rows * sizeof(double*));
	for(int i = 0; i < rows; i++){
		data[i] = malloc(columns * sizeof(double));
	}
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			data[i][j] = 0;
		}
	}
	return data;
}


Matrix initMatrix(int rows, int columns, double** data){
	Matrix M;
	M.columns = columns;
	M.rows = rows;
	M.data = data;
	return M;
}


void printMatrix(char* name, Matrix m){
	printf("Matrix: %s:\n", name);
	for(int i = 0; i < m.rows; i++){
		for(int j = 0; j < m.columns; j++){
			printf("%f ", round(m.data[i][j]));
		}
		printf("\n");
	}
	printf("\n");
}
