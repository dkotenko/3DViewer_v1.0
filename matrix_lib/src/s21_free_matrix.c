#include "s21_matrix.h"

void s21_free_matrix(matrix_t *matrix, int i)
{
	s21_free_matrix_array(matrix->matrix, i);
    matrix->matrix = NULL;
}

void s21_free_matrix_array(float **matrix, int i)
{
	free(matrix[0]);
	while (--i > -1) {
        matrix[i] = NULL;
	}
	free(matrix);
}