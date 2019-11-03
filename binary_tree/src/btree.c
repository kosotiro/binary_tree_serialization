#include <stdlib.h>
#include <stdio.h>

#include "btree.h"

void init_tree(btree_t *tree)
{
  tree->root = NULL;
}

tree_node_t* add_tree_node(btree_t *tree, tree_node_t *node, unsigned int key) 
{ 
  if (!tree)
    return NULL;

  /* If the tree is empty, return a new node */
  if (node == NULL) {
    tree_node_t *new_node = (tree_node_t *)malloc(sizeof(tree_node_t));
    
    if (!new_node) {
      perror("Allocation error!\n");
      return NULL;
    }
    
    new_node->key = key;
    new_node->right = new_node->left = NULL;

    if (!tree->root)
      tree->root = new_node;
  
    return new_node;
  } 
  
  if (key < node->key) 
    node->left  = add_tree_node(tree, node->left, key); 
  else if (key >= node->key) 
    node->right = add_tree_node(tree, node->right, key);    
  
  return node; 
} 

void print_node(tree_node_t *node)
{
  if (!node)
    return;

  printf("%d ",node->key);
}

void print_in_order(tree_node_t *node)
{ 
  if (node) { 
    print_in_order(node->left); 
  
    print_node(node);   
  
    print_in_order(node->right);
  } 
}


void print_pre_order(tree_node_t *node) 
{ 
  if (node) {
    print_node(node);   
  
    print_pre_order(node->left);   
  
    print_pre_order(node->right);
  } 
}

void print_post_order(tree_node_t *node)
{
  if (node) {
    print_post_order(node->left); 
   
    print_post_order(node->right); 
   
    print_node(node);
  }  
}

void clean_tree(tree_node_t *node)
{
  tree_node_t *current;

  if (!node)
    return;

  current = node;
  free(current);   
  
  clean_tree(node->left);   
  
  clean_tree(node->right);
}
