#ifndef __SQD3_TYPES_H__
#define __SQD3_TYPES_H__

#include <stdlib.h>
#include <string.h>

#include "consts.h"

typedef enum {
  T_INTEGER,
  T_REF,
  T_STRING,
} object_t;

typedef struct SQD3_OBJECT {
  object_t object_type;
  void *value;
} SQD3_OBJECT;

typedef struct SQD3_OBJECT_REF_VALUE {
  varname_t varname;
} SQD3_OBJECT_REF_VALUE;

SQD3_OBJECT *integer_from_long_long(integer value);
SQD3_OBJECT *string_from_const_char(const char *value);
SQD3_OBJECT *build_ref(varname_t varname);

integer read_integer_from_object(SQD3_OBJECT *object);
const char *read_string_from_object(SQD3_OBJECT *object);

SQD3_OBJECT *execute_operator_plus(SQD3_OBJECT *left, SQD3_OBJECT *right);
SQD3_OBJECT *execute_operator_multi(SQD3_OBJECT *left, SQD3_OBJECT *right);
SQD3_OBJECT *execute_operator_division(SQD3_OBJECT *left, SQD3_OBJECT *right);
SQD3_OBJECT *execute_operator_minus(SQD3_OBJECT *left, SQD3_OBJECT *right);

void invert_number_value(SQD3_OBJECT *object);
void free_object(SQD3_OBJECT *object);

#endif
