#ifndef CLIENT
#define CLIENT


#include<stdio.h> 
#include<fcntl.h> 
#include<stdlib.h> 
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<unistd.h>
#include<string.h> 


struct User{
  char username[100];
  char password[100];
  int UserType;
  int id;
};

struct Choice{
    int choice; 
    int amount; 
    struct User user;
    
}; 





#endif 