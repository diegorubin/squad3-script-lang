#include "parser.h"

/**
 * private functions
 */
bool is_binary_op(token value) {
  return (value == '+' || value == '-' || value == '*' || value == '/' ||
          value == '=');
}

SQD3_OBJECT *execute_function(varname_t function_name) {
  SQD3_OBJECT *(*function)();
  VTABLE_ENTRY *entry = recover_variable(function_name);

  if (entry == NULL) {
    fprintf(stderr, "error: function %s not declared\n", function_name);
    exit(-2);
  }

  void *function_ref = read_function_from_object(entry->ref);
  function = function_ref;

  return function();
}

/**
 * public functions
 */
SQD3_OBJECT *expr(void) {
  SQD3_OBJECT *expr_result = factor();

  NODE *expr_root = tree_node_init(VALUE);
  tree_node_set_value(expr_root, expr_result);

  while (is_binary_op(get_lookahead())) {
    operator_t op;
    read_lexeme(op);

    match(get_lookahead());

    SQD3_OBJECT *partial = factor();
    expr_root = tree_put_operation(expr_root, op, partial);
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

  if (get_lookahead() == UINT) {
    match(UINT);

    if (invert_factor) {
      return integer_from_long_long(atoll(lexeme) * -1);
    }
    return integer_from_long_long(atoll(lexeme));
  }

  match(ID);
  if (get_lookahead() == START_PARENTHESES) {
    SQD3_OBJECT *function_result = execute_function(lexeme);
    match(START_PARENTHESES);
    match(END_PARENTHESES);
    return function_result;
  }
  return build_ref(lexeme);
}
