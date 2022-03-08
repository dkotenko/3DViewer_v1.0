#include "tests.h"

START_TEST(test_sum_invalid) {
	matrix_t sum;
	matrix_t A;
	matrix_t B;
	init_matrixes_3x3(&A, &B);

	A.columns = 4;
	sum = s21_sum_matrix(&A, &B);
	ck_assert_int_eq(sum.matrix_type, INCORRECT_MATRIX);
	
	A.rows = 4;
	A.columns = 3;
	sum = s21_sum_matrix(&A, &B);
	ck_assert_int_eq(sum.matrix_type, INCORRECT_MATRIX);

	A.rows = 0;
	B.rows = 0;
	sum = s21_sum_matrix(&A, &B);
	ck_assert_int_eq(sum.matrix_type, INCORRECT_MATRIX);

	A.rows = 1;
	B.rows = 1;
	A.columns = 0;
	B.columns = 0;
	sum = s21_sum_matrix(&A, &B);
	ck_assert_int_eq(sum.matrix_type, INCORRECT_MATRIX);
	
	A.rows = 3;
	B.rows = 3;
	s21_free_matrix(&A, A.rows);
	s21_free_matrix(&B, B.rows);
} END_TEST

START_TEST(test_sum_correct) {
	matrix_t A;
	matrix_t B;
	init_matrixes_3x3(&A, &B);

	matrix_t sum = s21_sum_matrix(&A, &B);
	matrix_t m_result = s21_create_matrix(3,3);
	double result[3][3] = {{2,3,4}, {5,6,7}, {8,9,10}};
	
	for (int i = 0; i < m_result.rows; i++) {
        for (int j = 0; j < m_result.columns; j++) {
            m_result.matrix[i][j] = result[i][j];
        }
    }
	ck_assert_int_eq(s21_eq_matrix(&sum, &m_result), SUCCESS);
	
	s21_free_matrix(&m_result, m_result.rows);
	s21_free_matrix(&sum, sum.rows);
	s21_free_matrix(&A, A.rows);
	s21_free_matrix(&B, B.rows);
} END_TEST


Suite *sum_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Sum matrix");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_sum_correct);
  tcase_add_test(tc_core, test_sum_invalid);
  suite_add_tcase(s, tc_core);

  return s;
}