#include "s21_matrix.h"

void s21_free_matrix(matrix_t *matrix, int i)
{
	if (matrix) {
		s21_free_matrix_array(matrix->matrix, i);
    	matrix->matrix = NULL;
		free(matrix);
	}
}

void s21_free_arr_array(float **arr, int i)
{
	if (arr) {
		if (arr[0]) {
			free(arr[0]);
		}
		while (--i > -1) {
			arr[i] = NULL;
		}
		free(arr);
	}
}