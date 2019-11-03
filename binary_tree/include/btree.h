#ifndef __BTREE__
#define __BTREE__

typedef struct tree_node
{
  unsigned int key;
  struct tree_node *left;
  struct tree_node *right;
}tree_node_t;

typedef struct btree_
{
  tree_node_t *root;
}btree_t;

void init_tree(btree_t *tree);
tree_node_t* add_tree_node(btree_t *tree, tree_node_t *node, unsigned int key);
void print_in_order(tree_node_t *root);
void print_pre_order(tree_node_t *root);
void print_post_order(tree_node_t *root);
void clean_tree(tree_node_t *root);
#endif
