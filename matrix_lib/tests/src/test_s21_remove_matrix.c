#include "s21_matrix.h"

START_TEST(test_remove) {
	matrix_t m = s21_create_matrix(3, 3);
	s21_remove_matrix(&m);
  ck_assert_int_eq(m.matrix_type, INCORRECT_MATRIX);
} END_TEST


Suite *remove_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Remove matrix");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_remove);
  suite_add_tcase(s, tc_core);

  return s;
}