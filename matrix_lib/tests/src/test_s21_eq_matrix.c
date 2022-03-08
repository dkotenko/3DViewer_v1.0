#include "tests.h"

START_TEST(test_equal_matrix) {
	matrix_t A = s21_create_matrix(2,2);
	matrix_t B = s21_create_matrix(2,2);

	ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
	s21_free_matrix(&A, A.rows);
	s21_free_matrix(&B, B.rows);
} END_TEST

START_TEST(test_non_equal_matrix) {
	matrix_t A = s21_create_matrix(2,2);
	matrix_t B = s21_create_matrix(3,3);
	matrix_t C = s21_create_matrix(2,2);

	C.matrix[1][1] = 2;

	ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
	ck_assert_int_eq(s21_eq_matrix(&A, &C), FAILURE);

	s21_free_matrix(&A, A.rows);
	s21_free_matrix(&B, B.rows);
	s21_free_matrix(&C, C.rows);
} END_TEST


Suite *equal_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Eq matrix");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_equal_matrix);
  tcase_add_test(tc_core, test_non_equal_matrix);
  suite_add_tcase(s, tc_core);

  return s;
}