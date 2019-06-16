#include "vtable.h"

VTABLE_ENTRY *first_entry;

VTABLE_ENTRY *get_last_entry(VTABLE_ENTRY *entry) {
  if (entry->next != NULL) {
    return get_last_entry(entry->next);
  }
  return entry;
}

void init_vtable(void) {
  first_entry = malloc(sizeof(VTABLE_ENTRY));
  first_entry->varname[0] = '\0';
  first_entry->ref = NULL;
  first_entry->next = NULL;
  first_entry->previous = NULL;
  first_entry->scope = NEW_CONTEXT;
}

VTABLE_ENTRY *declare_local_variable(varname_t varname, SQD3_OBJECT *value) {
  VTABLE_ENTRY *last_entry = get_last_entry(first_entry);

  VTABLE_ENTRY *entry = malloc(sizeof(VTABLE_ENTRY));
  strncpy(entry->varname, varname, sizeof(varname_t));
  entry->ref = value;
  entry->next = NULL;
  entry->previous = last_entry;
  entry->scope = SCOPE_LOCAL;

  last_entry->next = entry;
  return entry;
}

void dispose_local_variables() {
  VTABLE_ENTRY *last_entry = get_last_entry(first_entry);

  while (last_entry->scope == SCOPE_LOCAL) {
    last_entry = last_entry->previous;
    free(last_entry->next);
    last_entry->next = NULL;
  }
}

VTABLE_ENTRY *recover_variable(varname_t varname) {
  VTABLE_ENTRY *entry = first_entry;
  while (entry->next != NULL) {
    entry = entry->next;
    if (!strcmp(varname, entry->varname)) {
      return entry;
    }
  }
  return NULL;
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
