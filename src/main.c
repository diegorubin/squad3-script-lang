#include <stdio.h>

#include "parser.h"

int main() {

  for (;;) {
    printf("> ");

    char input[120];
    fgets(input, 120, stdin);

    FILE *buffer = fmemopen(input, strlen(input), "r");
    init_lexer(buffer);
    printf("%lld \n", expr());
  }
  return 0;
}
