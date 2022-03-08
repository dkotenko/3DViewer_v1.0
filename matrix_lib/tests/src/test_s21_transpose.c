#include "tests.h"

START_TEST(test_trans_invalid) {
	matrix_t m = s21_create_matrix(2,2);

	m.rows = 0;
	matrix_t trans = s21_transpose(&m);
	ck_assert_int_eq(trans.matrix_type, INCORRECT_MATRIX);

	m.rows = 2;
	m.columns = 0;
	trans = s21_transpose(&m);
	ck_assert_int_eq(trans.matrix_type, INCORRECT_MATRIX);

	s21_free_matrix(&m, m.rows);
} END_TEST

START_TEST(test_trans_correct) {
	matrix_t src;
	matrix_t dest;

	src = s21_create_matrix(3, 3);
	dest = s21_create_matrix(3, 3);

	/*
	1 2 3
	4 5 6
	7 8 9
	*/
	src.matrix[0][0] = 1;
	src.matrix[0][1] = 2;
	src.matrix[0][2] = 3;
	src.matrix[1][0] = 4;
	src.matrix[1][1] = 5;
	src.matrix[1][2] = 6;
	src.matrix[2][0] = 7;
	src.matrix[2][1] = 8;
	src.matrix[2][2] = 9;

	/*
	1 4 7
	2 5 8
	3 6 9 
	*/
	dest.matrix[0][0] = 1;
	dest.matrix[0][1] = 4;
	dest.matrix[0][2] = 7;
	dest.matrix[1][0] = 2;
	dest.matrix[1][1] = 5;
	dest.matrix[1][2] = 8;
	dest.matrix[2][0] = 3;
	dest.matrix[2][1] = 6;
	dest.matrix[2][2] = 9;

	matrix_t trans = s21_transpose(&src);
	ck_assert_int_eq(s21_eq_matrix(&dest, &trans), SUCCESS);
	s21_free_matrix(&src, src.rows);
	s21_free_matrix(&dest, dest.rows);
	s21_free_matrix(&trans, trans.rows);
} END_TEST


Suite *trans_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Transpose");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_trans_correct);
  tcase_add_test(tc_core, test_trans_invalid);
  suite_add_tcase(s, tc_core);

  return s;
}