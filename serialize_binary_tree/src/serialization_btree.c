#include <stdlib.h>
#include "btree.h"
#include "serialize.h"
#include "serial_btree.h"
#include <stdio.h>
#include <memory.h>
#include "sentinel.h"

void serialize_btree_t(btree_t *obj, ser_buff_t *b)
{
  /* In the beginning of every Serialization routine, always encode 
   * 0XFFFFFFFF in the serialized buffer if the object being serialized
   * is NULL
   *
   * This is Sentinel insertion code*/
   SENTINEL_INSERTION_CODE(obj, b);
   serialize_tree_node_t(obj->root, b);
}

void serialize_tree_node_t(tree_node_t *obj, ser_buff_t *b)
{
  /* In the beginning of every Serialization routine, always encode     *
   * 0XFFFFFFFF in the serialized buffer if the object being serialized *
   * is NULL                                                            *
   * This is Sentinel insertion code                                    */
   SENTINEL_INSERTION_CODE(obj, b);
   serialize_data(b, (char *)&obj->key, sizeof(unsigned int));
   /* call recursively for the next node */
   serialize_tree_node_t(obj->right, b);
   serialize_tree_node_t(obj->left, b);
}

btree_t *de_serialize_btree_t(ser_buff_t *b)
{
  /* In the beginning of ever derialization routine, always write *
   * sentinel detection code                                     */
   SENTINEL_DETECTION_CODE(b);
   
   btree_t *tree = (btree_t *)malloc(sizeof(btree_t));
   tree->root = de_serialize_tree_node_t(b);
   
   return tree;
}

tree_node_t* de_serialize_tree_node_t(ser_buff_t* b)
{
  unsigned int sentinel = 0;
  
  SENTINEL_DETECTION_CODE(b);
  
  tree_node_t *obj = (tree_node_t *)malloc(sizeof(tree_node_t));
  
  de_serialize_data((char *)&obj->key, b, sizeof(unsigned int));
  de_serialize_data((char *)&sentinel, b, sizeof(unsigned int));
  
  if (sentinel == 0XFFFFFFFF)
    obj->right = NULL;
  else {
    serialize_buffer_skip(b, -1 * sizeof(unsigned int));
    obj->right = de_serialize_tree_node_t(b);    
  }
  
  sentinel = 0;
  de_serialize_data((char *)&sentinel, b, sizeof(unsigned int));
  
  if (sentinel == 0XFFFFFFFF)
    obj->left = NULL;
  else {
    serialize_buffer_skip(b, -1 * sizeof(unsigned int));
    obj->left = de_serialize_tree_node_t(b);    
  }
  
  return obj;
}
