#ifndef Server
#define Server

#include<sys/socket.h> 
#include<arpa/inet.h>
#include<pthread.h> 

struct Socket_Info{
  int Socketfd;
  struct sockaddr_in server_addr;
}; 



struct user{
  char username[100];
  char password[100];
  int UserType;
  int id;
};

struct Choice{
  int choice; 
  int amount; 
  struct user user;
};


int Init_Socket(struct Socket_Info *sock_info); 





#endif 