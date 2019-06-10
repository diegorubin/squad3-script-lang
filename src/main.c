#include <stdio.h>

#include "parser.h"

int main() {

  for (;;) {
    printf("> ");

    char input[120];
    fgets(input, 120, stdin);

    FILE *buffer = fmemopen(input, strlen(input), "r");
    init_lexer(buffer);
    SQD3_OBJECT *result = expr();
    printf("%lld \n", read_integer_from_object(result));
    free_object(result);
  }
  return 0;
}
