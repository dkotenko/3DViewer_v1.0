#include "s21_matrix.h"
#include <stdio.h>

float **s21_create_matrix_array(int rows, int columns)
{
	float **matrix;
	float *values;
	
	matrix = malloc(sizeof(float *) * rows);
	if (!matrix) {
		return NULL;
	}
	values = calloc(columns * rows, sizeof(float));
	if (!values) {
		s21_free_matrix_array(matrix, 0);
		return NULL;
	}

	for (int i = 0; i < columns; i++) {
		matrix[i] = values + (i * columns);
	}
	return matrix;
}

matrix_t s21_create_matrix(int rows, int columns)
{
	matrix_t matrix;

	if (rows < 1 || columns < 1) {
		matrix.matrix_type = INCORRECT_MATRIX;
		return matrix;
	}
	matrix.matrix = s21_create_matrix_array(rows, columns);
	if (!matrix.matrix) {
		return s21_get_incorrect_matrix();
	}
	matrix.matrix_type = ZERO_MATRIX;
	matrix.rows = rows;
	matrix.columns = columns;
	return matrix;
}