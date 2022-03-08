#ifndef TESTS_H
#define TESTS_H

#include "s21_matrix.h"
#include <stdio.h>
#include <check.h>

void init_matrixes_3x3(matrix_t *A, matrix_t *B);
int print_result(char *test_name, int result);
void print_matrix(matrix_t m);
Suite *free_suite(void);
Suite *create_suite(void);
Suite *equal_suite(void);
Suite *sum_suite(void);
Suite *sub_suite(void);
Suite *trans_suite(void);
Suite *mult_suite(void);
Suite *mult_number_suite(void);
Suite *determ_suite(void);
Suite *remove_suite(void);
Suite *inverse_suite(void);
Suite *calc_complements_suite(void);

#endif
