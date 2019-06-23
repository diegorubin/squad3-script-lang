#include "../src/parser.h"
#include "../src/sqd3_types.h"

#include <check.h>

/**
 * Fixture function
 */
SQD3_OBJECT *build1() { return integer_from_long_long(1); }

START_TEST(test_factor_integer) {
  char input[] = "1234";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  SQD3_OBJECT *result = factor();
  ck_assert_int_eq(1234, read_integer_from_object(result));
  fclose(buffer);
}
END_TEST

START_TEST(test_expr_only_factor) {
  char input[] = "1";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  SQD3_OBJECT *result = expr();
  ck_assert_int_eq(read_integer_from_object(result), 1);
  fclose(buffer);
}
END_TEST

START_TEST(test_expr_sum) {
  char input[] = "1 + 1";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  SQD3_OBJECT *result = expr();
  ck_assert_int_eq(read_integer_from_object(result), 2);
  fclose(buffer);
}
END_TEST

START_TEST(test_expr_minus) {
  char input[] = "1 - 1";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  SQD3_OBJECT *result = expr();
  ck_assert_int_eq(read_integer_from_object(result), 0);
  fclose(buffer);
}
END_TEST

START_TEST(test_expr_minus_negative) {
  char input[] = "1 - 2";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  SQD3_OBJECT *result = expr();
  ck_assert_int_eq(read_integer_from_object(result), -1);
  fclose(buffer);
}
END_TEST

START_TEST(test_expr_minus_more_digits) {
  char input[] = "25 - 15";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  SQD3_OBJECT *result = expr();
  ck_assert_int_eq(read_integer_from_object(result), 10);
  fclose(buffer);
}
END_TEST

START_TEST(test_expr_mult) {
  char input[] = "2 * 2";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  SQD3_OBJECT *result = expr();
  ck_assert_int_eq(read_integer_from_object(result), 4);
  fclose(buffer);
}
END_TEST

START_TEST(test_expr_div) {
  char input[] = "4 / 2";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  SQD3_OBJECT *result = expr();
  ck_assert_int_eq(read_integer_from_object(result), 2);
  fclose(buffer);
}
END_TEST

START_TEST(test_expr_mult_and_minus) {
  char input[] = "100*2 - 15";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  SQD3_OBJECT *result = expr();
  ck_assert_int_eq(read_integer_from_object(result), 185);
  fclose(buffer);
}
END_TEST

START_TEST(test_complex_with_parentheses) {
  char input[] = "100*(4 + 4)";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  SQD3_OBJECT *result = expr();
  ck_assert_int_eq(read_integer_from_object(result), 800);
  fclose(buffer);
}
END_TEST

START_TEST(test_complex_without_parentheses) {
  char input[] = "100*4 + 4";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  SQD3_OBJECT *result = expr();
  ck_assert_int_eq(read_integer_from_object(result), 404);
  fclose(buffer);
}
END_TEST

START_TEST(test_negative_expression) {
  char input[] = "- 10";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  ck_assert_int_eq(read_integer_from_object(expr()), -10);
  fclose(buffer);
}
END_TEST

START_TEST(test_negative_factor) {
  char input[] = "10 + - 9";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  ck_assert_int_eq(read_integer_from_object(expr()), 1);
  fclose(buffer);
}
END_TEST

START_TEST(test_negative_with_parentheses) {
  char input[] = "- (- 10 + (- 9))";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  ck_assert_int_eq(read_integer_from_object(expr()), 19);
  fclose(buffer);
}
END_TEST

START_TEST(test_factor_id) {
  char input[] = "10 + x";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_vtable();
  init_lexer(buffer);

  SQD3_OBJECT *x = integer_from_long_long(5);
  declare_local_variable("x", x);

  ck_assert_int_eq(read_integer_from_object(expr()), 15);
  fclose(buffer);
}
END_TEST

START_TEST(test_assign_variable) {
  char input[] = "x = 10";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);
  init_vtable();

  ck_assert_int_eq(read_integer_from_object(expr()), 10);
  fclose(buffer);
}
END_TEST

START_TEST(test_assign_expression_result) {
  char input[] = "x = (10 + 20 * 5)";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);
  init_vtable();

  ck_assert_int_eq(read_integer_from_object(expr()), 110);
  VTABLE_ENTRY *entry = recover_variable("x");
  ck_assert_int_eq(read_integer_from_object(entry->ref), 110);

  fclose(buffer);
}
END_TEST

START_TEST(test_builtin_function) {
  char input[] = "build1() + 1";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);
  init_vtable();

  SQD3_OBJECT *ref = build_builtin_function_ref("build1", &build1);
  declare_local_variable("build1", ref);

  ck_assert_int_eq(read_integer_from_object(expr()), 2);

  fclose(buffer);
}
END_TEST

Suite *parser_suite(void) {
  Suite *suite;
  TCase *tc_factor;
  TCase *tc_expr;
  TCase *tc_complex_expr;
  TCase *tc_assgn_expr;
  TCase *tc_function_call;

  suite = suite_create("Parser");
  tc_factor = tcase_create("factor");
  tc_expr = tcase_create("expr");
  tc_complex_expr = tcase_create("complex expr");
  tc_assgn_expr = tcase_create("assgn expr");
  tc_function_call = tcase_create("function call");

  tcase_add_test(tc_factor, test_factor_integer);
  tcase_add_test(tc_factor, test_factor_id);

  tcase_add_test(tc_expr, test_expr_only_factor);
  tcase_add_test(tc_expr, test_expr_sum);
  tcase_add_test(tc_expr, test_expr_minus);
  tcase_add_test(tc_expr, test_expr_minus_negative);
  tcase_add_test(tc_expr, test_expr_minus_more_digits);
  tcase_add_test(tc_expr, test_expr_mult);
  tcase_add_test(tc_expr, test_expr_div);
  tcase_add_test(tc_expr, test_expr_mult_and_minus);
  tcase_add_test(tc_expr, test_negative_expression);
  tcase_add_test(tc_expr, test_negative_factor);
  tcase_add_test(tc_expr, test_negative_with_parentheses);

  tcase_add_test(tc_complex_expr, test_complex_with_parentheses);
  tcase_add_test(tc_complex_expr, test_complex_without_parentheses);

  tcase_add_test(tc_assgn_expr, test_assign_variable);
  tcase_add_test(tc_assgn_expr, test_assign_expression_result);

  tcase_add_test(tc_function_call, test_builtin_function);

  suite_add_tcase(suite, tc_factor);
  suite_add_tcase(suite, tc_expr);
  suite_add_tcase(suite, tc_complex_expr);
  suite_add_tcase(suite, tc_assgn_expr);
  suite_add_tcase(suite, tc_function_call);

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
