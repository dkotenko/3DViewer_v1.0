#include "tests.h"
#include <math.h>


START_TEST(test_calc_complements_invalid) {
	matrix_t m = s21_create_matrix(2,2);
	matrix_t result;

	m.rows = 0;
	result = s21_calc_complements(&m);
	ck_assert_int_eq(result.matrix_type, INCORRECT_MATRIX);

	m.rows = 2;
	m.columns = 0;
	result = s21_calc_complements(&m);
	ck_assert_int_eq(result.matrix_type, INCORRECT_MATRIX);

	m.columns = 3;
	result = s21_calc_complements(&m);
	ck_assert_int_eq(result.matrix_type, INCORRECT_MATRIX);

	s21_free_matrix(&m, m.rows);
} END_TEST

START_TEST(test_calc_complements_correct) {
	matrix_t ex1;
	matrix_t res1;

	ex1 = s21_create_matrix(3, 3);
	res1 = s21_create_matrix(3, 3);

	/*
	1 2 3
	0 4 2
	5 2 1
	*/
	ex1.matrix[0][0] = 1;
	ex1.matrix[0][1] = 2;
	ex1.matrix[0][2] = 3;
	ex1.matrix[1][0] = 0;
	ex1.matrix[1][1] = 4;
	ex1.matrix[1][2] = 2;
	ex1.matrix[2][0] = 5;
	ex1.matrix[2][1] = 2;
	ex1.matrix[2][2] = 1;

	/*
	0 10 -20
	4 -14 8
	-8 -2 4 
	*/
	res1.matrix[0][0] = 0;
	res1.matrix[0][1] = 10;
	res1.matrix[0][2] = -20;
	res1.matrix[1][0] = 4;
	res1.matrix[1][1] = -14;
	res1.matrix[1][2] = 8;
	res1.matrix[2][0] = -8;
	res1.matrix[2][1] = -2;
	res1.matrix[2][2] = 4;

	matrix_t calc_complements1 = s21_calc_complements(&ex1);
	ck_assert_int_eq((int)res1.matrix[0][0], (int)calc_complements1.matrix[0][0]);
	ck_assert_int_eq((int)res1.matrix[0][1], (int)calc_complements1.matrix[0][1]);
	ck_assert_int_eq((int)res1.matrix[0][2], (int)calc_complements1.matrix[0][2]);
	ck_assert_int_eq((int)res1.matrix[1][0], (int)calc_complements1.matrix[1][0]);
	ck_assert_int_eq((int)res1.matrix[1][1], (int)calc_complements1.matrix[1][1]);
	ck_assert_int_eq((int)res1.matrix[1][2], (int)calc_complements1.matrix[1][2]);
	ck_assert_int_eq((int)res1.matrix[2][0], (int)calc_complements1.matrix[2][0]);
	ck_assert_int_eq((int)res1.matrix[2][1], (int)calc_complements1.matrix[2][1]);
	ck_assert_int_eq((int)res1.matrix[2][2], (int)calc_complements1.matrix[2][2]);
	
	s21_free_matrix(&ex1, ex1.rows);
	s21_free_matrix(&res1, res1.rows);
	s21_free_matrix(&calc_complements1, calc_complements1.rows);
	
} END_TEST


Suite *calc_complements_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("calc_complements matrix");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_calc_complements_correct);
  tcase_add_test(tc_core, test_calc_complements_invalid);
  suite_add_tcase(s, tc_core);

  return s;
}