#include "../src/vtable.h"
#include <check.h>

extern VTABLE_ENTRY *first_entry;

/**
 * fixture function
 */
SQD3_OBJECT *a_function() { return integer_from_long_long(1); }

START_TEST(test_init_vtable) {
  init_vtable();
  ck_assert_str_eq("\0", first_entry->varname);
  ck_assert_ptr_eq(NULL, first_entry->ref);
  ck_assert_ptr_eq(NULL, first_entry->next);
  ck_assert_int_eq(NEW_CONTEXT, first_entry->scope);
}
END_TEST

START_TEST(test_declare_local_variable) {
  init_vtable();

  SQD3_OBJECT *value = integer_from_long_long(100);
  declare_local_variable("x", value);

  VTABLE_ENTRY *next = first_entry->next;
  ck_assert_str_eq("x", next->varname);

  ck_assert_ptr_eq(NULL, next->next);

  ck_assert_int_eq(100, read_integer_from_object(next->ref));
  ck_assert_int_eq(SCOPE_LOCAL, next->scope);

  free_object(value);
}
END_TEST

START_TEST(test_declare_local_builtin_function) {
  init_vtable();

  SQD3_OBJECT *value = build_builtin_function_ref("a_function", &a_function);
  declare_local_variable("a_function", value);

  VTABLE_ENTRY *next = first_entry->next;
  ck_assert_str_eq("a_function", next->varname);

  ck_assert_ptr_eq(NULL, next->next);

  ck_assert_ptr_eq(a_function, read_function_from_object(next->ref));
  ck_assert_int_eq(SCOPE_LOCAL, next->scope);

  free_object(value);
}
END_TEST

START_TEST(test_dispose_local_variables) {
  init_vtable();

  SQD3_OBJECT *value = integer_from_long_long(100);
  declare_local_variable("x", value);

  dispose_local_variables();

  ck_assert_int_eq(NEW_CONTEXT, first_entry->scope);
  ck_assert_ptr_eq(NULL, first_entry->next);

  free_object(value);
}
END_TEST

Suite *vtable_suite(void) {
  Suite *suite;
  TCase *tc_vtable;

  tc_vtable = tcase_create("init vtable");
  tcase_add_test(tc_vtable, test_init_vtable);
  tcase_add_test(tc_vtable, test_declare_local_variable);
  tcase_add_test(tc_vtable, test_declare_local_builtin_function);
  tcase_add_test(tc_vtable, test_dispose_local_variables);

  suite = suite_create("V-Table");

  suite_add_tcase(suite, tc_vtable);

  return suite;
}

int main() {
  int number_failed;
  Suite *suite;
  SRunner *suite_runner;

  suite = vtable_suite();
  suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return number_failed;
}
