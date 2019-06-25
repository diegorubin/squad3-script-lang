#ifndef __TOKENS_H__
#define __TOKENS_H__

typedef int token;

enum {
  START_PARENTHESES = 40,
  END_PARENTHESES,
  COMMA = 44,

  UINT = 255,
  FLOAT,
  ID
};

#endif /*__TOKENS_H__*/
