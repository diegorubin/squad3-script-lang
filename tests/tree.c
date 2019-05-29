#include "../src/tree.h"
#include <check.h>

START_TEST(test_init_node) {
  NODE node;
  ck_assert_int_eq(1024, sizeof(node.value));
}
END_TEST

START_TEST(test_read_node) {
  NODE *father = NULL;
  NODE *left = NULL;
  NODE *right = NULL;

  father = tree_node_init(OPERATOR);
  left = tree_node_init(INTEGER);
  right = tree_node_init(INTEGER);

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
  tree_node_set_str(plus, "+");

  multi = tree_node_init(OPERATOR);
  tree_node_set_str(multi, "*");

  n1 = tree_node_init(INTEGER);
  tree_node_set_str(n1, "1");

  n2 = tree_node_init(INTEGER);
  tree_node_set_str(n2, "2");

  n3 = tree_node_init(INTEGER);
  tree_node_set_str(n3, "3");

  tree_add(plus, n1, NODE_LEFT);
  tree_add(plus, n2, NODE_RIGHT);

  tree_add(multi, plus, NODE_LEFT);
  tree_add(multi, n3, NODE_RIGHT);

  print_tree(multi, result);
  ck_assert_str_eq("1 + 2 * 3", result);

  tree_node_free(plus);
}
END_TEST

Suite *tree_suite(void) {
  Suite *suite;
  TCase *tc_tree;

  tc_tree = tcase_create("init tree");
  tcase_add_test(tc_tree, test_init_node);
  tcase_add_test(tc_tree, test_read_node);
  tcase_add_test(tc_tree, test_print_arithmetic_tree);

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
