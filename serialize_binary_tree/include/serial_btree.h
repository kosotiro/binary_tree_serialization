#ifndef __SERIAL_BTREE__
#define __SERIAL_BTREE__

/*Serialization functions*/
void serialize_btree_t(btree_t *obj, ser_buff_t *b);
void serialize_tree_node_t(tree_node_t *obj, ser_buff_t *b);

/*DeSerialization function*/
btree_t *de_serialize_btree_t(ser_buff_t *b);
tree_node_t *de_serialize_tree_node_t(ser_buff_t *b);

#endif
