#include "tree.h"

NODE *tree_node_init(node_t nodetype) {
  NODE *node = malloc(sizeof(NODE));
  node->nodetype = nodetype;
  node->left = NULL;
  node->right = NULL;
  node->parent = NULL;

  return node;
}

void tree_node_free(NODE *node) {
  if (node->left != NULL)
    tree_node_free(node->left);

  if (node->right != NULL)
    tree_node_free(node->right);

  free(node);
}

void tree_add(NODE *node, NODE *son, side_t side) {
  son->parent = node;
  if (side == NODE_LEFT)
    node->left = son;
  if (side == NODE_RIGHT)
    node->right = son;
}

void print_tree(NODE *node, char *str) {

  if (node->left != NULL) {
    print_tree(node->left, str);
  }

  if (node->nodetype == OPERATOR) {
    sprintf(str, "%s %s ", str, node->op);
  }

  if (node->right != NULL) {
    print_tree(node->right, str);
  }

  if (node->nodetype == VALUE) {
    sprintf(str, "%s%llu", str, read_integer_from_object(node->value));
  }
}

SQD3_OBJECT *calculate_tree(NODE *node) {
  SQD3_OBJECT *left;
  SQD3_OBJECT *right;

  if (node->left != NULL)
    left = calculate_tree(node->left);
  if (node->right != NULL)
    right = calculate_tree(node->right);

  if (node->nodetype == OPERATOR) {
    if (!strcmp(node->op, "*"))
      return execute_operator_multi(left, right);
    if (!strcmp(node->op, "/"))
      return execute_operator_division(left, right);
    if (!strcmp(node->op, "+"))
      return execute_operator_plus(left, right);
    if (!strcmp(node->op, "-"))
      return execute_operator_minus(left, right);
    if (!strcmp(node->op, "="))
      return execute_operator_assign(left, right);
  }

  return node->value;
}

void tree_node_set_value(NODE *node, SQD3_OBJECT *value) {
  node->value = value;
}

void tree_node_set_op(NODE *node, operator_t op) { strcpy(node->op, op); }

NODE *most_left_node(NODE *root) {
  if (root->left != NULL) {
    return most_left_node(root->left);
  }
  return root;
}

NODE *most_right_node(NODE *root) {
  if (root->right != NULL) {
    return most_right_node(root->right);
  }
  return root;
}

NODE *tree_put_operation(NODE *root, operator_t operation, SQD3_OBJECT *value) {
  NODE *operation_node = tree_node_init(OPERATOR);
  tree_node_set_op(operation_node, operation);

  NODE *value_node = tree_node_init(VALUE);
  tree_node_set_value(value_node, value);

  if (!strcmp(operation, "*") || !strcmp(operation, "/")) {
    NODE *old_right = most_right_node(root);
    NODE *old_right_parent = old_right->parent;

    tree_add(operation_node, old_right, NODE_LEFT);
    tree_add(operation_node, value_node, NODE_RIGHT);

    if (old_right_parent != NULL) {
      operation_node->parent = old_right_parent;
      old_right_parent->right = operation_node;
      return root;
    }
  } else {
    tree_add(operation_node, root, NODE_LEFT);
    tree_add(operation_node, value_node, NODE_RIGHT);
  }

  return operation_node;
}
