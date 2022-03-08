#include "s21_matrix.h"

matrix_t	test_s21_get_incorrect_matrix(void)
{
	matrix_t matrix;
	matrix.matrix_type = INCORRECT_MATRIX;
	return matrix;
}