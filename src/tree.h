#ifndef __TREE_H__
#define __TREE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "consts.h"
#include "sqd3_types.h"

typedef enum {
  NODE_LEFT = 0,
  NODE_RIGHT,
} side_t;

typedef enum {
  OPERATOR = 0,
  INTEGER,
} node_t;

typedef struct NODE {
  node_t nodetype;
  char value[LEXEME_MAX_SIZE];
  struct NODE *left;
  struct NODE *right;
  struct NODE *parent;
} NODE;

NODE *tree_node_init(node_t nodetype);
void tree_node_free(NODE *node);
void tree_add(NODE *node, NODE *son, side_t side);
void print_tree(NODE *node, char *str);
integer calculate_tree(NODE *node);
void tree_node_set_str(NODE *node, const char *str);
NODE *tree_put_operation(NODE *root, const char *operation, const char *value);

#endif
