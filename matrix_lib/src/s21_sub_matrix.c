#include "s21_matrix.h"
#include <check.h>

matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B)
{
	if (A->columns != B->columns || A->rows != B->rows || A->rows < 1 || A->columns < 1) {
		return s21_get_incorrect_matrix();
	}
	matrix_t matrix = s21_create_matrix(A->rows, A->columns);
	for (int i = 0; i < A->columns; i++) {
		for (int j = 0; j < A->rows; j++) {
			matrix.matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
		}
	}
	matrix.matrix_type = CORRECT_MATRIX;
	return matrix;
}