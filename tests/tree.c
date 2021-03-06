#include "../src/tree.h"
#include <check.h>

START_TEST(test_read_node) {
  NODE *father = NULL;
  NODE *left = NULL;
  NODE *right = NULL;

  father = tree_node_init(OPERATOR);
  left = tree_node_init(VALUE);
  right = tree_node_init(VALUE);

  tree_add(father, left, NODE_LEFT);
  tree_add(father, right, NODE_RIGHT);

  ck_assert_ptr_eq(father->left, left);
  ck_assert_ptr_eq(father->right, right);

  tree_node_free(father);
}
END_TEST

START_TEST(test_print_arithmetic_tree) {
  char result[1024];
  strcpy(result, "\0");

  NODE *plus = NULL;
  NODE *multi = NULL;
  NODE *n1 = NULL;
  NODE *n2 = NULL;
  NODE *n3 = NULL;

  plus = tree_node_init(OPERATOR);
  tree_node_set_op(plus, "+");

  multi = tree_node_init(OPERATOR);
  tree_node_set_op(multi, "*");

  n1 = tree_node_init(VALUE);
  tree_node_set_value(n1, integer_from_long_long(1));

  n2 = tree_node_init(VALUE);
  tree_node_set_value(n2, integer_from_long_long(2));

  n3 = tree_node_init(VALUE);
  tree_node_set_value(n3, integer_from_long_long(3));

  tree_add(plus, n1, NODE_LEFT);
  tree_add(plus, n2, NODE_RIGHT);

  tree_add(multi, plus, NODE_LEFT);
  tree_add(multi, n3, NODE_RIGHT);

  print_tree(multi, result);
  ck_assert_str_eq("1 + 2 * 3", result);

  tree_node_free(plus);
}
END_TEST

START_TEST(test_print_arithmetic_tree_adjusted) {
  char result[1024];
  strcpy(result, "\0");

  NODE *root = tree_node_init(VALUE);
  tree_node_set_value(root, integer_from_long_long(1));
  root = tree_put_operation(root, "+", integer_from_long_long(2));

  print_tree(root, result);
  ck_assert_str_eq("1 + 2", result);
  ck_assert_int_eq(3, read_integer_from_object(calculate_tree(root)));

  tree_node_free(root);
}
END_TEST

START_TEST(test_print_arithmetic_tree_adjusted_mult) {
  char result[1024];
  strcpy(result, "\0");

  NODE *root = tree_node_init(VALUE);
  tree_node_set_value(root, integer_from_long_long(1));
  root = tree_put_operation(root, "*", integer_from_long_long(2));

  print_tree(root, result);
  ck_assert_str_eq("1 * 2", result);
  ck_assert_int_eq(2, read_integer_from_object(calculate_tree(root)));

  tree_node_free(root);
}
END_TEST

START_TEST(test_print_arithmetic_tree_correct_order) {
  char result[1024];
  strcpy(result, "\0");

  NODE *root = tree_node_init(VALUE);
  tree_node_set_value(root, integer_from_long_long(1));
  root = tree_put_operation(root, "+", integer_from_long_long(1));
  root = tree_put_operation(root, "*", integer_from_long_long(2));

  print_tree(root, result);
  ck_assert_str_eq("1 + 1 * 2", result);
  ck_assert_int_eq(3, read_integer_from_object(calculate_tree(root)));

  tree_node_free(root);
}
END_TEST

START_TEST(test_print_arithmetic_tree_correct_order_with_sum) {
  char result[1024];
  strcpy(result, "\0");

  NODE *root = tree_node_init(VALUE);
  tree_node_set_value(root, integer_from_long_long(1));
  root = tree_put_operation(root, "*", integer_from_long_long(2));
  root = tree_put_operation(root, "+", integer_from_long_long(3));
  root = tree_put_operation(root, "*", integer_from_long_long(4));

  print_tree(root, result);
  ck_assert_str_eq("1 * 2 + 3 * 4", result);
  ck_assert_int_eq(14, read_integer_from_object(calculate_tree(root)));

  tree_node_free(root);
}
END_TEST

START_TEST(test_print_arithmetic_tree_correct_order_with_minus) {
  char result[1024];
  strcpy(result, "\0");

  NODE *root = tree_node_init(VALUE);
  tree_node_set_value(root, integer_from_long_long(4));
  root = tree_put_operation(root, "*", integer_from_long_long(3));
  root = tree_put_operation(root, "+", integer_from_long_long(10));
  root = tree_put_operation(root, "/", integer_from_long_long(2));
  root = tree_put_operation(root, "-", integer_from_long_long(7));

  print_tree(root, result);
  ck_assert_str_eq("4 * 3 + 10 / 2 - 7", result);
  ck_assert_int_eq(10, read_integer_from_object(calculate_tree(root)));

  tree_node_free(root);
}
END_TEST

START_TEST(test_print_arithmetic_tree_correct_order_with_plus_sequence) {
  char result[1024];
  strcpy(result, "\0");

  NODE *root = tree_node_init(VALUE);
  tree_node_set_value(root, integer_from_long_long(1));
  root = tree_put_operation(root, "+", integer_from_long_long(5));
  root = tree_put_operation(root, "*", integer_from_long_long(2));
  root = tree_put_operation(root, "*", integer_from_long_long(10));
  root = tree_put_operation(root, "/", integer_from_long_long(4));
  root = tree_put_operation(root, "-", integer_from_long_long(25));

  print_tree(root, result);
  ck_assert_str_eq("1 + 5 * 2 * 10 / 4 - 25", result);
  ck_assert_int_eq(-4, read_integer_from_object(calculate_tree(root)));

  tree_node_free(root);
}
END_TEST

Suite *tree_suite(void) {
  Suite *suite;
  TCase *tc_tree;

  tc_tree = tcase_create("init tree");
  tcase_add_test(tc_tree, test_read_node);
  tcase_add_test(tc_tree, test_print_arithmetic_tree);
  tcase_add_test(tc_tree, test_print_arithmetic_tree_adjusted);
  tcase_add_test(tc_tree, test_print_arithmetic_tree_adjusted_mult);
  tcase_add_test(tc_tree, test_print_arithmetic_tree_correct_order);
  tcase_add_test(tc_tree, test_print_arithmetic_tree_correct_order_with_sum);
  tcase_add_test(tc_tree, test_print_arithmetic_tree_correct_order_with_minus);
  tcase_add_test(tc_tree,
                 test_print_arithmetic_tree_correct_order_with_plus_sequence);

  suite = suite_create("Tree");

  suite_add_tcase(suite, tc_tree);

  return suite;
}

int main() {
  int number_failed;
  Suite *suite;
  SRunner *suite_runner;

  suite = tree_suite();
  suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return number_failed;
}
