#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#include "btree.h"
#include "serialize.h"
#include "serial_btree.h"
  
#define PORT     8080 
#define MAXLINE 1024 
  
// Driver code 
int main() { 
  ser_buff_t *b;
  btree_t tree;
  tree_node_t *node = NULL;
  int sockfd; 
  char buffer[MAXLINE];
  int n, len, sum;
  struct sockaddr_in servaddr; 

  init_tree(&tree);
  node = add_tree_node(&tree, node, 20);
  add_tree_node(&tree, node, 12);
  add_tree_node(&tree, node, 3);
  add_tree_node(&tree, node, 41);
  add_tree_node(&tree, node, 52);

  printf("printing the object to be serialized on sending machine:\n");
  printf("In order printout:");
  print_in_order(tree.root);
  printf("\n");
  printf("Pre order printout:");
  print_pre_order(tree.root);
  printf("\n");
  printf("Post order printout:");
  print_post_order(tree.root);
  printf("\n");

  init_serialized_buffer(&b);
  serialize_btree_t(&tree, b);
  
  // Creating socket file descriptor 
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
    perror("socket creation failed"); 
    exit(EXIT_FAILURE); 
  } 
  
  memset(&servaddr, 0, sizeof(servaddr)); 
      
  // Filling server information 
  servaddr.sin_family = AF_INET; 
  servaddr.sin_port = htons(PORT); 
  servaddr.sin_addr.s_addr = INADDR_ANY; 
          
  sendto(sockfd, (const char *)b->b, get_serialize_buffer_data_size(b), 
         MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
         sizeof(servaddr)); 
   
  clean_tree(tree.root);
  
  close(sockfd); 
  return 0; 
} 
