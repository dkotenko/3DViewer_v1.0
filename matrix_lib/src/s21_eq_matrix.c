#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B)
{
	if (!A || !B || A->columns != B->columns || A->rows != B->rows) {
		return FAILURE;
	}
	for (int i = 0; i < A->rows; i++) {
		if (memcmp(A->matrix[i], B->matrix[i], A->columns * sizeof(double))) {
			return FAILURE;
		}
	}
	return SUCCESS;
}