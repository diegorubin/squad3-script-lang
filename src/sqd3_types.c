#include "sqd3_types.h"

SQD3_OBJECT *integer_from_long_long(integer value) {
  SQD3_OBJECT *ref = malloc(sizeof(SQD3_OBJECT));

  ref->object_type = T_INTEGER;

  ref->value = malloc(sizeof(integer));
  memcpy(ref->value, &value, sizeof(integer));

  return ref;
}

integer read_integer_from_object(SQD3_OBJECT *object) {
  return *((integer *)object->value);
}

SQD3_OBJECT *execute_operator_plus(SQD3_OBJECT *left, SQD3_OBJECT *right) {
  return integer_from_long_long(read_integer_from_object(left) +
                                read_integer_from_object(right));
}

SQD3_OBJECT *execute_operator_multi(SQD3_OBJECT *left, SQD3_OBJECT *right) {
  return integer_from_long_long(read_integer_from_object(left) *
                                read_integer_from_object(right));
}

SQD3_OBJECT *execute_operator_division(SQD3_OBJECT *left, SQD3_OBJECT *right) {
  return integer_from_long_long(read_integer_from_object(left) /
                                read_integer_from_object(right));
}

SQD3_OBJECT *execute_operator_minus(SQD3_OBJECT *left, SQD3_OBJECT *right) {
  return integer_from_long_long(read_integer_from_object(left) -
                                read_integer_from_object(right));
}

void invert_number_value(SQD3_OBJECT *object) {
  *((integer *)object->value) = *((integer *)object->value) * -1;
}

void free_object(SQD3_OBJECT *object) {
  free(object->value);
  free(object);
}
