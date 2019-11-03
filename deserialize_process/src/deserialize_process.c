// Server side implementation of UDP client-server model 
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
  int sockfd; 
  char buffer[MAXLINE]; 
  int len, n, sum;
  btree_t *tree;
  ser_buff_t *b;
  struct sockaddr_in servaddr, cliaddr; 
      
  // Creating socket file descriptor 
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
    perror("socket creation failed"); 
    exit(EXIT_FAILURE); 
  } 
      
  memset(&servaddr, 0, sizeof(servaddr)); 
  memset(&cliaddr, 0, sizeof(cliaddr)); 
      
  // Filling server information 
  servaddr.sin_family    = AF_INET; // IPv4 
  servaddr.sin_addr.s_addr = INADDR_ANY; 
  servaddr.sin_port = htons(PORT); 
      
  // Bind the socket with the server address 
  if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) { 
    perror("bind failed"); 
    exit(EXIT_FAILURE); 
  } 
      
    
  n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
               MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
               &len); 

  init_serialized_buffer(&b);
  b->size = n;
  b->b = buffer;
  b->next = 0;
  tree = de_serialize_btree_t(b);
  printf("printing the deserialized object on receiving machine:\n");
  printf("In order printout:");
  print_in_order(tree->root);
  printf("\n");
  printf("Pre order printout:");
  print_pre_order(tree->root);
  printf("\n");
  printf("Post order printout:");
  print_post_order(tree->root);
  printf("\n");

  clean_tree(tree->root);
  free(tree);
  tree = NULL;
      
  return 0; 
}
