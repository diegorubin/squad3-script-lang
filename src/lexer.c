#include "lexer.h"

FILE *stream;
token lookeahead;
char lexeme[LEXEME_MAX_SIZE];
int position;


void read_digits() {

  char c = 0;

  while ((c = getc(stream)) && isdigit(c)) {
    lexeme[position++] = c;
  }
  ungetc(c, stream);
}

/**
 * Funcoes privadas.
 * Essas funcoes serao utilizadas para
 * reconhecer tokens.
 */
token read_number(void) {
  char c = getc(stream);
  position = 0;
  
  if (isdigit(c)) {
    lexeme[position++] = c;
    read_digits();

    c = getc(stream);
    if (c == '.') {
      lexeme[position++] = c;

      read_digits();

      lexeme[position] = '\0';
      ungetc(c, stream);
      
      return FLOAT;
    }



    lexeme[position] = '\0';
    ungetc(c, stream);
    return UINT;
  }
  ungetc(c, stream);
  return 0;
}

void ignore_spaces(void) {
  char c;
  while ((c = getc(stream)) && isspace(c)) {
  }
  ungetc(c, stream);
}

bool binary_op(void) {
  char c = getc(stream);
  if (c == '+' || c == '-' || c == '*' || c == '/') {
    lexeme[0] = c;
    lexeme[1] = '\0';
    return true;
  }
  ungetc(c, stream);
  return false;
}

token is_valid_char(void) {
  char c = getc(stream);
  if (c == '(' || c == ')') {
    lexeme[0] = '\0';
    return c;
  }
  ungetc(c, stream);
  return 0;
}

token get_next_token(void) {
  ignore_spaces();
  token kind;
  if (kind = read_number())
    return kind;
  if (binary_op())
    return BINARY_OP;
  return is_valid_char();
}

void read_lexeme(char *dest) { strcpy(dest, lexeme); }

/**
 * Essas funcoes sao publicas.
 * O parser utilizara essas funcoes.
 */
void match(token expected) {
  if (expected != lookeahead) {
    fprintf(stderr, "expected %d but found %d", expected, lookeahead);
    exit(-1);
  }
  lookeahead = get_next_token();
}

int get_lookahead(void) { return lookeahead; }

void init_lexer(FILE *input) {
  stream = input;
  strcpy(lexeme, "\0");
  lookeahead = get_next_token();
}
