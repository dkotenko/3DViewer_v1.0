#include "s21_matrix.h"
#include <stdio.h>

void s21_print_matrix(matrix_t *m, char *name)
{
    printf("%s\n", name);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            printf("%f ", m->matrix[i][j]);
        }
        printf("\n");
    }
}