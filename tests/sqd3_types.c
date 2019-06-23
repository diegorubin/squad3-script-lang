#include "../src/sqd3_types.h"
#include <check.h>
#include <stdio.h>

/**
 * Fixture function
 */
SQD3_OBJECT *simple_function() { return integer_from_long_long(0); }

START_TEST(test_init_integer) {
  integer *value = malloc(sizeof(integer));
  *value = 1000;

  SQD3_OBJECT *object = integer_from_long_long(*value);

  free(value);

  ck_assert_int_eq(read_integer_from_object(object), 1000);
  ck_assert_int_eq(object->object_type, T_INTEGER);

  free_object(object);
}
END_TEST

START_TEST(test_init_function_ref) {
  integer *value = malloc(sizeof(integer));
  *value = 1000;

  SQD3_OBJECT *object =
      build_builtin_function_ref("simple_function", &simple_function);

  free(value);

  ck_assert_ptr_eq(read_function_from_object(object), &simple_function);
  ck_assert_int_eq(object->object_type, T_REF);

  free_object(object);
}
END_TEST

START_TEST(test_plus_integers) {
  SQD3_OBJECT *a = integer_from_long_long(1);
  SQD3_OBJECT *b = integer_from_long_long(1);

  ck_assert_int_eq(read_integer_from_object(execute_operator_plus(a, b)), 2);

  free_object(a);
  free_object(b);
}
END_TEST

START_TEST(test_minus_integers) {
  SQD3_OBJECT *a = integer_from_long_long(5);
  SQD3_OBJECT *b = integer_from_long_long(3);

  ck_assert_int_eq(read_integer_from_object(execute_operator_minus(a, b)), 2);

  free_object(a);
  free_object(b);
}
END_TEST

START_TEST(test_division_integers) {
  SQD3_OBJECT *a = integer_from_long_long(10);
  SQD3_OBJECT *b = integer_from_long_long(2);

  ck_assert_int_eq(read_integer_from_object(execute_operator_division(a, b)),
                   5);

  free_object(a);
  free_object(b);
}
END_TEST

START_TEST(test_multi_integers) {
  SQD3_OBJECT *a = integer_from_long_long(10);
  SQD3_OBJECT *b = integer_from_long_long(2);

  ck_assert_int_eq(read_integer_from_object(execute_operator_multi(a, b)), 20);

  free_object(a);
  free_object(b);
}
END_TEST

START_TEST(test_invert_number_value) {
  SQD3_OBJECT *a = integer_from_long_long(10);
  invert_number_value(a);

  ck_assert_int_eq(read_integer_from_object(a), -10);

  free_object(a);
}
END_TEST

Suite *parser_suite(void) {
  Suite *suite;
  TCase *tc_integer;

  tc_integer = tcase_create("integers");

  suite = suite_create("SQD3 Types");

  tcase_add_test(tc_integer, test_init_integer);
  tcase_add_test(tc_integer, test_init_function_ref);
  tcase_add_test(tc_integer, test_plus_integers);
  tcase_add_test(tc_integer, test_minus_integers);
  tcase_add_test(tc_integer, test_multi_integers);
  tcase_add_test(tc_integer, test_division_integers);
  tcase_add_test(tc_integer, test_invert_number_value);

  suite_add_tcase(suite, tc_integer);

  return suite;
}

int main() {
  int number_failed;
  Suite *suite;
  SRunner *suite_runner;

  suite = parser_suite();
  suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return number_failed;
}
