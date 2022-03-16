#include "s21_matrix.h"
#include <math.h>

static void s21_populate_minor(float **src, float **dest,  int row, int column, int a_size)
{
    int k = 0;
    int m;

    for (int i = 0; i < a_size; i++) {
        if (i == row) {
            continue;
        }
        m = 0;
        for (int j = 0; j < a_size; j++) {
            if (j == column) {
                continue;
            }
            dest[k][m] = src[i][j];
            m++;
        }
        k++;
    }
}

matrix_t s21_calc_complements(matrix_t *A)
{
    if (A->rows != A->columns || A->rows < 1 || A->columns < 1) {
		return s21_get_incorrect_matrix();
	}
    int n = A->rows;
    float **temp_minor = s21_create_matrix_array(n - 1, n - 1);
    matrix_t complements_matrix = s21_create_matrix(n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            s21_populate_minor(A->matrix, temp_minor, i, j, n);
            complements_matrix.matrix[i][j] = s21_determinant_array(temp_minor, n - 1, n - 1) * pow(-1, i + j);
        }
    }
    s21_free_matrix_array(temp_minor, n - 1);
    complements_matrix.matrix_type = CORRECT_MATRIX;
    return complements_matrix;
}