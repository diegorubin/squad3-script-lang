#include "parser.h"

/**
 * private functions
 */
bool is_binary_op(token value) {
  return (value == '+' || value == '-' || value == '*' || value == '/');
}

/**
 * public functions
 */
SQD3_OBJECT *expr(void) {
  char number[1024];

  SQD3_OBJECT *expr_result = factor();
  sprintf(number, "%lld", read_integer_from_object(expr_result));

  NODE *expr_root = tree_node_init(INTEGER);
  tree_node_set_str(expr_root, number);

  while (is_binary_op(get_lookahead())) {
    char lexeme[2];
    read_lexeme(lexeme);
    match(get_lookahead());

    SQD3_OBJECT *partial = factor();
    sprintf(number, "%lld", read_integer_from_object(partial));

    expr_root = tree_put_operation(expr_root, lexeme, number);
  }

  SQD3_OBJECT *tree_result = calculate_tree(expr_root);
  tree_node_free(expr_root);

  return tree_result;
}

SQD3_OBJECT *factor(void) {
  SQD3_OBJECT *result;
  bool invert_factor = false;

  if (get_lookahead() == '-') {
    match('-');
    invert_factor = true;
  }

  if (get_lookahead() == START_PARENTHESES) {
    match(START_PARENTHESES);
    result = expr();

    match(END_PARENTHESES);
    if (invert_factor) {
      invert_number_value(result);
    }

    return result;
  }

  char lexeme[LEXEME_MAX_SIZE];
  read_lexeme(lexeme);
  match(UINT);

  if (invert_factor) {
    return integer_from_long_long(atoll(lexeme) * -1);
  }
  return integer_from_long_long(atoll(lexeme));
}
