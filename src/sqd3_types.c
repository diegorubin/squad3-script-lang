#include "sqd3_types.h"

extern SQD3_OBJECT *read_value_from_ref(SQD3_OBJECT *object);

#define NORMALIZE(o) (o->object_type == T_REF) ? read_value_from_ref(o) : o

SQD3_OBJECT *integer_from_long_long(integer value) {
  SQD3_OBJECT *ref = malloc(sizeof(SQD3_OBJECT));

  ref->object_type = T_INTEGER;

  ref->value = malloc(sizeof(integer));
  memcpy(ref->value, &value, sizeof(integer));

  return ref;
}

SQD3_OBJECT *string_from_const_char(const char *value) {
  SQD3_OBJECT *ref = malloc(sizeof(SQD3_OBJECT));

  ref->object_type = T_STRING;

  ref->value = malloc(strlen(value));
  memcpy(ref->value, &value, strlen(value));

  return ref;
}

SQD3_OBJECT *build_ref(varname_t varname) {
  SQD3_OBJECT *ref = malloc(sizeof(SQD3_OBJECT));

  ref->object_type = T_REF;

  SQD3_OBJECT_REF_VALUE *ref_value = malloc(sizeof(SQD3_OBJECT_REF_VALUE));
  memcpy(ref_value->varname, varname, strlen(varname));
  ref_value->ref_type = T_VARIABLE;

  ref->value = (void *)ref_value;

  return ref;
}

SQD3_OBJECT *build_builtin_function_ref(varname_t varname, void *function_ptr) {
  SQD3_OBJECT *ref = malloc(sizeof(SQD3_OBJECT));

  ref->object_type = T_REF;

  SQD3_OBJECT_REF_VALUE *ref_value = malloc(sizeof(SQD3_OBJECT_REF_VALUE));
  memcpy(ref_value->varname, varname, strlen(varname));
  ref_value->ref_type = T_BUILTIN_FUNCTION;
  ref_value->ptr = function_ptr;

  ref->value = (void *)ref_value;

  return ref;
}

integer read_integer_from_object(SQD3_OBJECT *object) {
  return *((integer *)object->value);
}

const char *read_string_from_object(SQD3_OBJECT *object) {
  return *((const char **)object->value);
}

void *read_function_from_object(SQD3_OBJECT *object) {
  return ((SQD3_OBJECT_REF_VALUE *)object->value)->ptr;
}

SQD3_OBJECT *execute_operator_plus(SQD3_OBJECT *left, SQD3_OBJECT *right) {
  return integer_from_long_long(read_integer_from_object(NORMALIZE(left)) +
                                read_integer_from_object(NORMALIZE(right)));
}

SQD3_OBJECT *execute_operator_multi(SQD3_OBJECT *left, SQD3_OBJECT *right) {
  return integer_from_long_long(read_integer_from_object(NORMALIZE(left)) *
                                read_integer_from_object(NORMALIZE(right)));
}

SQD3_OBJECT *execute_operator_division(SQD3_OBJECT *left, SQD3_OBJECT *right) {
  return integer_from_long_long(read_integer_from_object(NORMALIZE(left)) /
                                read_integer_from_object(NORMALIZE(right)));
}

SQD3_OBJECT *execute_operator_minus(SQD3_OBJECT *left, SQD3_OBJECT *right) {
  return integer_from_long_long(read_integer_from_object(NORMALIZE(left)) -
                                read_integer_from_object(NORMALIZE(right)));
}

void invert_number_value(SQD3_OBJECT *object) {
  *((integer *)object->value) = *((integer *)object->value) * -1;
}

void free_object(SQD3_OBJECT *object) {
  free(object->value);
  free(object);
}
