#ifndef __VTABLE_H__
#define __VTABLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "consts.h"
#include "sqd3_types.h"

typedef enum {
  NEW_CONTEXT,
  SCOPE_LOCAL,
} scope_t;

typedef struct VTABLE_ENTRY {
  varname_t varname;
  scope_t scope;
  SQD3_OBJECT *ref;
  struct VTABLE_ENTRY *next;
  struct VTABLE_ENTRY *previous;
} VTABLE_ENTRY;

void init_vtable(void);
void init_context(varname_t context_name);
void finish_context(void);
VTABLE_ENTRY *declare_local_variable(varname_t varname, SQD3_OBJECT *value);
SQD3_OBJECT *recover_from_stack_args(int pos);
void dispose_local_variables();

SQD3_OBJECT *execute_operator_assign(SQD3_OBJECT *left, SQD3_OBJECT *right);

VTABLE_ENTRY *recover_variable(varname_t varname);
integer read_integer_from_ref(SQD3_OBJECT *object);

#endif
