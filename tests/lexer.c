#include "../src/lexer.h"
#include <check.h>
#include <stdio.h>

START_TEST(test_uint_consumer) {
  char lexeme[LEXEME_MAX_SIZE];

  char input[] = "1234";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  ck_assert_int_eq(get_lookahead(), UINT);
  read_lexeme(lexeme);
  ck_assert_str_eq("1234", lexeme);

  fclose(buffer);
}
END_TEST

START_TEST(test_not_recognized) {
  char input[] = "test";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  ck_assert_int_eq(get_lookahead(), 0);
  fclose(buffer);
}
END_TEST

START_TEST(test_space_beginning) {
  char lexeme[LEXEME_MAX_SIZE];

  char input[] = "   1";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  ck_assert_int_eq(get_lookahead(), UINT);
  read_lexeme(lexeme);
  ck_assert_str_eq("1", lexeme);

  fclose(buffer);
}
END_TEST

START_TEST(test_space_between) {
  char input[] = "   1   1";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  ck_assert_int_eq(get_lookahead(), UINT);
  match(UINT);
  ck_assert_int_eq(get_lookahead(), UINT);
  fclose(buffer);
}
END_TEST

START_TEST(test_space_end) {
  char input[] = "1    ";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  ck_assert_int_eq(get_lookahead(), UINT);
  match(UINT);
  ck_assert_int_eq(get_lookahead(), 0);
  fclose(buffer);
}
END_TEST

START_TEST(test_if_is_plus) {
  char input[] = "+";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  ck_assert_int_eq(get_lookahead(), BINARY_OP);
  fclose(buffer);
}
END_TEST

START_TEST(test_if_is_minus) {
  char input[] = "-";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  ck_assert_int_eq(get_lookahead(), BINARY_OP);
  fclose(buffer);
}
END_TEST

START_TEST(test_if_is_multiplication) {
  char input[] = "*";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  ck_assert_int_eq(get_lookahead(), BINARY_OP);
  fclose(buffer);
}
END_TEST

START_TEST(test_if_is_division) {
  char input[] = "/";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  ck_assert_int_eq(get_lookahead(), BINARY_OP);
  fclose(buffer);
}
END_TEST

START_TEST(test_uint_with_operator) {
  char lexeme[LEXEME_MAX_SIZE];

  char input[] = "1*1";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  ck_assert_int_eq(get_lookahead(), UINT);
  read_lexeme(lexeme);
  ck_assert_str_eq("1", lexeme);
  match(UINT);

  ck_assert_int_eq(get_lookahead(), BINARY_OP);
  read_lexeme(lexeme);
  ck_assert_str_eq("*", lexeme);
  match(BINARY_OP);

  ck_assert_int_eq(get_lookahead(), UINT);
  read_lexeme(lexeme);
  ck_assert_str_eq("1", lexeme);
  match(UINT);

  fclose(buffer);
}
END_TEST

START_TEST(test_uint_with_parentheses) {
  char lexeme[LEXEME_MAX_SIZE];

  char input[] = "(1)";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  ck_assert_int_eq(get_lookahead(), START_PARENTHESES);
  read_lexeme(lexeme);
  ck_assert_str_eq("", lexeme);
  match(START_PARENTHESES);

  ck_assert_int_eq(get_lookahead(), UINT);
  read_lexeme(lexeme);
  ck_assert_str_eq("1", lexeme);
  match(UINT);

  ck_assert_int_eq(get_lookahead(), END_PARENTHESES);
  read_lexeme(lexeme);
  ck_assert_str_eq("", lexeme);
  match(END_PARENTHESES);

  fclose(buffer);
}
END_TEST

START_TEST(test_float_consumer) {
  char lexeme[LEXEME_MAX_SIZE];

  char input[] = "1.0";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  ck_assert_int_eq(get_lookahead(), FLOAT);
  read_lexeme(lexeme);
  ck_assert_str_eq("1.0", lexeme);

  fclose(buffer);
}
END_TEST

START_TEST(test_float_consumer_number_dot_number_dot_number) {
  char lexeme[LEXEME_MAX_SIZE];

  char input[] = "2.0.0";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  ck_assert_int_eq(get_lookahead(), FLOAT);
  read_lexeme(lexeme);
  ck_assert_str_eq("2.0", lexeme);

  fclose(buffer);
}
END_TEST

START_TEST(test_uint_with_dot) {
  char lexeme[LEXEME_MAX_SIZE];

  char input[] = "1.a";
  FILE *buffer = fmemopen(input, strlen(input), "r");
  init_lexer(buffer);

  ck_assert_int_eq(get_lookahead(), UINT);
  read_lexeme(lexeme);
  ck_assert_str_eq("1", lexeme);

  fclose(buffer);
}
END_TEST

Suite *lexer_suite(void) {
  Suite *suite;
  TCase *tc_integers;
  TCase *tc_spaces;
  TCase *tc_binary;
  TCase *tc_floats;

  suite = suite_create("Lexer");
  tc_integers = tcase_create("Integer");
  tc_spaces = tcase_create("Spaces");
  tc_binary = tcase_create("Binary");
  tc_floats = tcase_create("Floats");

  tcase_add_test(tc_integers, test_uint_consumer);
  tcase_add_test(tc_integers, test_not_recognized);
  tcase_add_test(tc_integers, test_uint_with_parentheses);
  tcase_add_test(tc_integers, test_uint_with_dot);

  tcase_add_test(tc_spaces, test_space_beginning);
  tcase_add_test(tc_spaces, test_space_between);
  tcase_add_test(tc_spaces, test_space_end);

  tcase_add_test(tc_binary, test_if_is_plus);
  tcase_add_test(tc_binary, test_if_is_minus);
  tcase_add_test(tc_binary, test_if_is_multiplication);
  tcase_add_test(tc_binary, test_if_is_division);
  tcase_add_test(tc_binary, test_uint_with_operator);

  tcase_add_test(tc_floats, test_float_consumer);
  tcase_add_test(tc_floats, test_float_consumer_number_dot_number_dot_number);

  suite_add_tcase(suite, tc_integers);
  suite_add_tcase(suite, tc_spaces);
  suite_add_tcase(suite, tc_binary);
  suite_add_tcase(suite, tc_floats);

  return suite;
}

int main() {
  int number_failed;
  Suite *suite;
  SRunner *suite_runner;

  suite = lexer_suite();
  suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return number_failed;
}
