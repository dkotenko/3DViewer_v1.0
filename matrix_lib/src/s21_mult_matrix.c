#include "s21_matrix.h"

matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B)
{
    int sum = 0;

    if (A->columns != B->rows || A->rows < 1 || A->columns < 1 || B->rows < 1 || B->columns < 1) {
		return s21_get_incorrect_matrix();
	}
    matrix_t matrix = s21_create_matrix(A->rows, B->columns);
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.columns; j++) {
            sum = 0;
            for (int k = 0; k < A->columns; k++) {
                sum += A->matrix[i][k] * B->matrix[k][j];
            }
            matrix.matrix[i][j] = sum;
        }
    }
    matrix.matrix_type = CORRECT_MATRIX;
    return matrix;
}