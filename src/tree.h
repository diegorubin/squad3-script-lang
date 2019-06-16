#ifndef __TREE_H__
#define __TREE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "consts.h"
#include "sqd3_types.h"
#include "vtable.h"

typedef enum {
  NODE_LEFT = 0,
  NODE_RIGHT,
} side_t;

typedef enum {
  OPERATOR = 0,
  VALUE,
} node_t;

typedef struct NODE {
  node_t nodetype;
  SQD3_OBJECT *value;
  operator_t op;
  struct NODE *left;
  struct NODE *right;
  struct NODE *parent;
} NODE;

NODE *tree_node_init(node_t nodetype);
void tree_node_free(NODE *node);
void tree_add(NODE *node, NODE *son, side_t side);
void print_tree(NODE *node, char *str);
SQD3_OBJECT *calculate_tree(NODE *node);
void tree_node_set_value(NODE *node, SQD3_OBJECT *value);
void tree_node_set_op(NODE *node, operator_t op);
NODE *tree_put_operation(NODE *root, operator_t operation, SQD3_OBJECT *value);

#endif
