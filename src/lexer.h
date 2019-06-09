#ifndef __LEXER_H__
#define __LEXER_H__

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "consts.h"
#include "tokens.h"

// Essa funcao inicializa o lexer
void init_lexer(FILE *input);

// Essas funcoes serao utilizadas no parser
token get_lookahead(void);
void match(int expected);
void read_lexeme(char *dest);

#endif
