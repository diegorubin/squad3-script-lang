#include "parser.h"

integer expr(void) {
  char number[1024];

  integer expr_result = factor();
  sprintf(number, "%lld", expr_result);

  NODE *expr_root = tree_node_init(INTEGER);
  tree_node_set_str(expr_root, number);

  while (get_lookahead() == BINARY_OP) {
    char lexeme[2];
    read_lexeme(lexeme);
    match(BINARY_OP);

    integer partial = factor();
    sprintf(number, "%lld", partial);

    expr_root = tree_put_operation(expr_root, lexeme, number);
  }

  integer tree_result = calculate_tree(expr_root);
  tree_node_free(expr_root);

  return tree_result;
}

integer factor(void) {
  integer result = 0;

  if (get_lookahead() == START_PARENTHESES) {
    match(START_PARENTHESES);
    result = expr();
    match(END_PARENTHESES);
    return result;
  }

  char lexeme[LEXEME_MAX_SIZE];
  read_lexeme(lexeme);
  match(UINT);
  return atoll(lexeme);
}
