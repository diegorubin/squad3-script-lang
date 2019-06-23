#ifndef __PARSER_H__
#define __PARSER_H__

/** SQD3 EBNF
 * expr -> factor { binary_op factor }
 * binary_op -> '+' | '-' | '*' | '/' | '='
 * factor -> ['-'] ( 'UINT' | 'ID' ['(' ')'] | '(' expr ')' )
 */

#include <stdlib.h>

#include "lexer.h"
#include "sqd3_types.h"
#include "tree.h"

SQD3_OBJECT *expr(void);
SQD3_OBJECT *factor(void);

#endif
