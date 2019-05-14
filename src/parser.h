/** SQD3 EBNF
 *
 * expr -> ['-'] factor { binary_op factor }
 * binary_op -> '+' | '-' | '*' | '/'
 * factor -> 'UINT' | '(' expr ')'
 *
 */

#include <stdlib.h>

#include "lexer.h"

typedef long long integer;

integer expr();
integer factor();
