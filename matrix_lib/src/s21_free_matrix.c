#include "s21_matrix.h"

void s21_free_matrix(matrix_t *matrix, int i)
{
	s21_free_matrix_array(matrix->matrix, i);
    matrix->matrix = NULL;
}

void s21_free_matrix_array(double **matrix, int i)
{
	while (--i > -1) {
		free(matrix[i]);
        matrix[i] = NULL;
	}
	free(matrix);
}