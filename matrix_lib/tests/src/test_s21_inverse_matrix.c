#include "tests.h"
#include <math.h>

START_TEST(test_inverse_invalid) {
	matrix_t m = s21_create_matrix(2,2);
	matrix_t result;

	m.rows = 0;
	result = s21_inverse_matrix(&m);
	ck_assert_int_eq(result.matrix_type, INCORRECT_MATRIX);

	m.rows = 2;
	m.columns = 0;
	result = s21_inverse_matrix(&m);
	ck_assert_int_eq(result.matrix_type, INCORRECT_MATRIX);

	m.columns = 3;
	result = s21_inverse_matrix(&m);
	ck_assert_int_eq(result.matrix_type, INCORRECT_MATRIX);

	s21_free_matrix(&m, m.rows);
} END_TEST


START_TEST(test_inverse_correct) {
	matrix_t ex1;
	matrix_t res1;

	ex1 = s21_create_matrix(3, 3);
	res1 = s21_create_matrix(3, 3);

	/*
	1 1 3
	1 3 -3
	-2 -4 -4
	*/
	ex1.matrix[0][0] = 1;
	ex1.matrix[0][1] = 1;
	ex1.matrix[0][2] = 3;
	ex1.matrix[1][0] = 1;
	ex1.matrix[1][1] = 3;
	ex1.matrix[1][2] = -3;
	ex1.matrix[2][0] = -2;
	ex1.matrix[2][1] = -4;
	ex1.matrix[2][2] = -4;

	/*
	1 4 7
	2 5 8
	3 6 9 
	*/
	res1.matrix[0][0] = 3;
	res1.matrix[0][1] = 1;
	res1.matrix[0][2] = 1.5;
	res1.matrix[1][0] = -1.25;
	res1.matrix[1][1] = -0.25;
	res1.matrix[1][2] = -0.75;
	res1.matrix[2][0] = -0.25;
	res1.matrix[2][1] = -0.25;
	res1.matrix[2][2] = -0.25;

	matrix_t inverse1 = s21_inverse_matrix(&ex1);
	ck_assert_int_eq((int)res1.matrix[0][0] * 100, (int)inverse1.matrix[0][0] * 100);
	ck_assert_int_eq((int)res1.matrix[0][1] * 100, (int)inverse1.matrix[0][1] * 100);
	ck_assert_int_eq((int)res1.matrix[0][2] * 100, (int)inverse1.matrix[0][2] * 100);
	ck_assert_int_eq((int)res1.matrix[1][0] * 100, (int)inverse1.matrix[1][0] * 100);
	ck_assert_int_eq((int)res1.matrix[1][1] * 100, (int)inverse1.matrix[1][1] * 100);
	ck_assert_int_eq((int)res1.matrix[1][2] * 100, (int)inverse1.matrix[1][2] * 100);
	ck_assert_int_eq((int)res1.matrix[2][0] * 100, (int)inverse1.matrix[2][0] * 100);
	ck_assert_int_eq((int)res1.matrix[2][1] * 100, (int)inverse1.matrix[2][1] * 100);
	ck_assert_int_eq((int)res1.matrix[2][2] * 100, (int)inverse1.matrix[2][2] * 100);
	
	s21_free_matrix(&ex1, ex1.rows);
	s21_free_matrix(&res1, res1.rows);
	s21_free_matrix(&inverse1, inverse1.rows);
	
} END_TEST


Suite *inverse_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Inverse matrix");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_inverse_correct);
  tcase_add_test(tc_core, test_inverse_invalid);
  suite_add_tcase(s, tc_core);

  return s;
}