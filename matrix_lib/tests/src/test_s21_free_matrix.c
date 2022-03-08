#include "s21_matrix.h"
#include "tests.h"

START_TEST(test_free_matrix) {
	matrix_t m = s21_create_matrix(2,2);
		
	s21_free_matrix(&m, m.rows);
	ck_assert_ptr_eq(m.matrix, NULL);
} END_TEST


Suite *free_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Free matrix");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_free_matrix);
  suite_add_tcase(s, tc_core);

  return s;
}