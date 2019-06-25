#include "vtable.h"

VTABLE_ENTRY *first_entry;
VTABLE_ENTRY *last_entry;

void init_vtable(void) {
  first_entry = malloc(sizeof(VTABLE_ENTRY));
  first_entry->varname[0] = '\0';
  first_entry->ref = NULL;
  first_entry->next = NULL;
  first_entry->previous = NULL;
  first_entry->scope = NEW_CONTEXT;

  last_entry = first_entry;
}

void init_context(varname_t context_name) {

  VTABLE_ENTRY *entry = malloc(sizeof(VTABLE_ENTRY));
  strncpy(entry->varname, context_name, sizeof(varname_t));
  entry->ref = NULL;
  entry->next = NULL;
  entry->previous = last_entry;
  entry->scope = NEW_CONTEXT;

  last_entry->next = entry;
  last_entry = entry;
}

void finish_context(void) {
  last_entry = last_entry->previous;
  free(last_entry);
  last_entry->next = NULL;
}

VTABLE_ENTRY *declare_local_variable(varname_t varname, SQD3_OBJECT *value) {

  VTABLE_ENTRY *entry = malloc(sizeof(VTABLE_ENTRY));
  strncpy(entry->varname, varname, sizeof(varname_t));
  entry->ref = value;
  entry->next = NULL;
  entry->previous = last_entry;
  entry->scope = SCOPE_LOCAL;

  last_entry->next = entry;
  last_entry = entry;
  return entry;
}

void dispose_local_variables() {
  while (last_entry->scope == SCOPE_LOCAL) {
    last_entry = last_entry->previous;
    free(last_entry);
    last_entry->next = NULL;
  }
}

VTABLE_ENTRY *recover_variable(varname_t varname) {
  VTABLE_ENTRY *entry = last_entry;
  while (entry->previous != NULL) {
    if (!strcmp(varname, entry->varname) && entry->scope == SCOPE_LOCAL) {
      return entry;
    }
    entry = entry->previous;
  }
  return NULL;
}

SQD3_OBJECT *recover_from_stack_args(int pos) {
  VTABLE_ENTRY *local_entry = last_entry;
  while (pos--) {
    local_entry = last_entry->previous;
  }
  return local_entry->ref;
}

SQD3_OBJECT *read_value_from_ref(SQD3_OBJECT *object) {
  SQD3_OBJECT_REF_VALUE *ref = (SQD3_OBJECT_REF_VALUE *)object->value;
  VTABLE_ENTRY *entry = recover_variable(ref->varname);
  if (entry != NULL) {
    return entry->ref;
  }

  fprintf(stderr, "error: variable %s not declared\n", ref->varname);
  exit(-2);
}

SQD3_OBJECT *execute_operator_assign(SQD3_OBJECT *left, SQD3_OBJECT *right) {
  if (left->object_type != T_REF) {
    fprintf(stderr, "error: assign left operand should be a ref\n");
  }
  SQD3_OBJECT_REF_VALUE *ref = (SQD3_OBJECT_REF_VALUE *)left->value;

  declare_local_variable(ref->varname, right);
  return right;
}
