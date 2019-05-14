#include "parser.h"

integer expr() {
  integer expr_result = factor();
  while (get_lookahead() == BINARY_OP) {
    char lexeme[2];
    read_lexeme(lexeme);
    match(BINARY_OP);

    integer partial = factor();
    switch (lexeme[0]) {
    case '+':
      expr_result += partial;
      break;
    case '-':
      expr_result -= partial;
      break;
    case '*':
      expr_result *= partial;
      break;
    case '/':
      expr_result /= partial;
    }
  }

  return expr_result;
}

integer factor() {
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
