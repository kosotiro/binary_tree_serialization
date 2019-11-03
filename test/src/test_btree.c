#include <stdlib.h>
#include <stdio.h>

#include "btree.h"

int main()
{
  btree_t tree;
  tree_node_t *node = NULL;
  
  init_tree(&tree);
  node = add_tree_node(&tree, node, 1);
  add_tree_node(&tree, node, 2);
  add_tree_node(&tree, node, 3);
  add_tree_node(&tree, node, 4);
  add_tree_node(&tree, node, 5);
  
  
  printf("In order printout:");
  print_in_order(tree.root);
  printf("\n");
  printf("Pre order printout:");
  print_pre_order(tree.root);
  printf("\n");
  printf("Post order printout:");
  print_post_order(tree.root);
  printf("\n");
  clean_tree(tree.root);
    
  return 0;
}
