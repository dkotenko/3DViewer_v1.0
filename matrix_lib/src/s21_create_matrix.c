#include "s21_matrix.h"

double **s21_create_matrix_array(int rows, int columns)
{
	double **matrix;
	
	matrix = malloc(sizeof(double *) * rows);
	if (!matrix) {
		return NULL;
	}
	for (int i = 0; i < columns; i++) {
		matrix[i] = calloc(columns, sizeof(double));
		if (!matrix[i]) {
			s21_free_matrix_array(matrix, i);
			return NULL;
		}
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