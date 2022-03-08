#include "tests.h"

void print_matrix(matrix_t m)
{
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.columns; j++)
        {
            printf("%f ", m.matrix[i][j]);
        }
        printf("\n");
    }
}

void populate_matrix(double **arr, matrix_t *m)
{
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            m->matrix[i][j] = arr[i][j];
        }
    }
}

void init_matrixes_3x3(matrix_t *A, matrix_t *B)
{   
	double m1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7,8,9}};
	double m2[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
    
	*A = s21_create_matrix(3, 3);
	*B = s21_create_matrix(3, 3);
    
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			A->matrix[i][j] = m1[i][j];
			B->matrix[i][j] = m2[i][j];
		}
	}
}

int main(void) {
    int no_failed = 0;                   
    SRunner *runner;
    
    runner = srunner_create(free_suite());          
    srunner_add_suite(runner, create_suite());
    srunner_add_suite(runner, equal_suite());
    srunner_add_suite(runner, sum_suite());
    srunner_add_suite(runner, sub_suite());
    srunner_add_suite(runner, trans_suite());
    srunner_add_suite(runner, mult_suite());
    srunner_add_suite(runner, mult_number_suite());
    srunner_add_suite(runner, determ_suite());
    srunner_add_suite(runner, remove_suite());
    srunner_add_suite(runner, inverse_suite());
    srunner_add_suite(runner, calc_complements_suite());
    

    srunner_run_all(runner, CK_NORMAL);  
    no_failed = srunner_ntests_failed(runner); 
    srunner_free(runner);                      
    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;  
}