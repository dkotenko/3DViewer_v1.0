#include "tests.h"

START_TEST(test_mult_matrix_invalid) {
	matrix_t mult;
	matrix_t A;
	matrix_t B;
	init_matrixes_3x3(&A, &B);

	A.columns = 4;
	mult = s21_mult_matrix(&A, &B);
	ck_assert_int_eq(mult.matrix_type, INCORRECT_MATRIX);
	
    A.columns = 3;
	A.rows = 0;
	mult = s21_mult_matrix(&A, &B);
	ck_assert_int_eq(mult.matrix_type, INCORRECT_MATRIX);

	A.rows = 3;
	A.columns = 0;
	mult = s21_mult_matrix(&A, &B);
	ck_assert_int_eq(mult.matrix_type, INCORRECT_MATRIX);

    A.columns = 3;
    B.rows = 0;
	mult = s21_mult_matrix(&A, &B);
	ck_assert_int_eq(mult.matrix_type, INCORRECT_MATRIX);

	B.rows = 3;
	B.columns = 0;
	mult = s21_mult_matrix(&A, &B);
	ck_assert_int_eq(mult.matrix_type, INCORRECT_MATRIX);

	s21_free_matrix(&A, A.rows);
	s21_free_matrix(&B, B.rows);
} END_TEST

START_TEST(test_mult_matrix_correct) {
	matrix_t A;
	matrix_t B;
	init_matrixes_3x3(&A, &B);

	matrix_t mult = s21_mult_matrix(&A, &B);
	matrix_t m_result = s21_create_matrix(3,3);
	float result[3][3] = {{6,6,6}, {15,15,15}, {24,24,24}};
	
	for (int i = 0; i < m_result.rows; i++) {
        for (int j = 0; j < m_result.columns; j++) {
            m_result.matrix[i][j] = result[i][j];
        }
    }
	ck_assert_int_eq(s21_eq_matrix(&mult, &m_result), SUCCESS);
	
	s21_free_matrix(&m_result, m_result.rows);
	s21_free_matrix(&mult, mult.rows);
	s21_free_matrix(&A, A.rows);
	s21_free_matrix(&B, B.rows);
} END_TEST


Suite *mult_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Mult matrix");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_mult_matrix_correct);
  tcase_add_test(tc_core, test_mult_matrix_invalid);
  suite_add_tcase(s, tc_core);

  return s;
}