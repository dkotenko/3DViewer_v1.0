#include "tests.h"
#include <math.h>

double test_s21_determinant(matrix_t *A)
{
	if (A->rows != A->columns || A->rows < 1 || A->columns < 1) {
		return NAN;
	}
	return 0;
}


START_TEST(test_determ_invalid) {
	matrix_t m = s21_create_matrix(2,2);
	double determinant = 0;

	m.rows = 0;
	determinant = s21_determinant(&m);
	ck_assert_int_eq(isnan(determinant), SUCCESS);

	m.rows = 2;
	m.columns = 0;
	determinant = s21_determinant(&m);
	ck_assert_int_eq(isnan(determinant), SUCCESS);

	m.columns = 3;
	determinant = s21_determinant(&m);
	ck_assert_int_eq(isnan(determinant), SUCCESS);
	s21_free_matrix(&m, m.rows);
} END_TEST


START_TEST(test_determ_correct) {
	matrix_t m1;
	matrix_t m2;

	m1 = s21_create_matrix(3, 3);
	m2 = s21_create_matrix(3, 3);

	/*
	54 2 5
	56 4 7
	1 -4 -20
	*/
	m1.matrix[0][0] = 54;
	m1.matrix[0][1] = 2;
	m1.matrix[0][2] = 5;
	m1.matrix[1][0] = 56;
	m1.matrix[1][1] = 4;
	m1.matrix[1][2] = 7;
	m1.matrix[2][0] = 1;
	m1.matrix[2][1] = -4;
	m1.matrix[2][2] = -20;

	/*
	1 4 7
	2 5 8
	3 6 9 
	*/
	m2.matrix[0][0] = 1;
	m2.matrix[0][1] = 4;
	m2.matrix[0][2] = 7;
	m2.matrix[1][0] = 2;
	m2.matrix[1][1] = 5;
	m2.matrix[1][2] = 8;
	m2.matrix[2][0] = 3;
	m2.matrix[2][1] = 6;
	m2.matrix[2][2] = 9;

	ck_assert_int_eq(s21_determinant(&m1), -1694);
	ck_assert_int_eq(s21_determinant(&m2), 0);
	s21_free_matrix(&m1, m1.rows);
	s21_free_matrix(&m2, m2.rows);
	
} END_TEST


Suite *determ_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Determinant");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_determ_correct);
  tcase_add_test(tc_core, test_determ_invalid);
  suite_add_tcase(s, tc_core);

  return s;
}