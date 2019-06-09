#ifndef __SQD3_TYPES_H__
#define __SQD3_TYPES_H__

#include <stdlib.h>
#include <string.h>

typedef long long integer;

typedef enum {
  T_INTEGER,
} object_t;

typedef struct SQD3_OBJECT {
  object_t object_type;
  void *value;
} SQD3_OBJECT;

SQD3_OBJECT *integer_from_long_long(integer value);

SQD3_OBJECT *execute_operator_plus(SQD3_OBJECT *left, SQD3_OBJECT *right);
SQD3_OBJECT *execute_operator_multi(SQD3_OBJECT *left, SQD3_OBJECT *right);
SQD3_OBJECT *execute_operator_division(SQD3_OBJECT *left, SQD3_OBJECT *right);
SQD3_OBJECT *execute_operator_minus(SQD3_OBJECT *left, SQD3_OBJECT *right);

integer read_integer_from_object(SQD3_OBJECT *object);

void invert_number_value(SQD3_OBJECT *object);
void free_object(SQD3_OBJECT *object);

#endif
