#include "s21_matrix.h"

matrix_t s21_transpose(matrix_t *A)
{
	if (A->rows < 1 || A->columns < 1) {
		return s21_get_incorrect_matrix();
	}
	matrix_t matrix = s21_create_matrix(A->columns, A->rows);
	for (int i = 0; i < A->rows; i++) {
		for (int j = 0; j < A->columns; j++) {
			matrix.matrix[j][i] = A->matrix[i][j];
		}
	}
	matrix.matrix_type = CORRECT_MATRIX;
	return matrix;
}