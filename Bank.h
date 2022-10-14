#ifndef BANK
#define BANK

#include<stdio.h>
#include<fcntl.h> 
#include<unistd.h> 
#include<stdlib.h> 
#include<string.h>

// we will strore User Information in User.db
struct Account{
   int id; 
   int Amount;         // Amount The User Had
   int Account_Type;    // 0 for Normal // 1 for JointAccount; // In case of Joint Account Two users Will Point to this account;
}; 



struct User{
    int id;
    char name[100]; 
    char password[100]; 
    int havingaccount; // BECOMES -1 if User Deletes The account;
    int UserType; // 1 for Administrator and 2 for Normal User; 
    struct Account Account; 
};





// Readwrite operations on Read_Account and Write_Account;
int Read_Account(int id,struct Account *ReadInfo); 
int Write_Account(int id,struct Account *WriteInfo); 

int Read_User(int id,struct User *ReadInfo); 
int Write_User(int id,struct User *WriteInfo); 



#endif