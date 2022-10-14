#include "Server.h" 
#include "Bank.h" 

int Login(struct user user){
    int id = user.id;
    
  
    struct User user1;
    Read_User(id,&user1); 

   
    

   if(strcmp(user1.name,user.username) == 0){
      
      if(strcmp(user1.password,user.password) == 0){
         if(user1.UserType == user.UserType){
               struct Account acc; 
               if(user1.havingaccount == 1)
                  return 1;

                else
                   return -1;

                return 1;
            }
           else{
                 
                 return -1;
               }
         }

         
         return -1;
        
    }
    
     return -1; 
}


int Choice_Handler(struct user user,struct Choice choice){
    if((user.UserType == 0) || (user.UserType == 1)){
        // Normal User;
        struct User u;
        Read_User(user.id,&u); 
        if(choice.choice == 1){
            int amount = choice.amount; 
            u.Account.Amount += amount; 
            Write_User(user.id,&u); 
            return -5;
        }

        if(choice.choice == 2){
            int amount = choice.amount; 
            if(u.Account.Amount < amount){
                return -1;
            }
            else{
               u.Account.Amount -= amount;
               Write_User(user.id,&u); 
               return -5;
            }
          
        }


        if(choice.choice == 5){
             // create an Account
             struct User u; 
             u.id = choice.user.id;
             u.havingaccount = 1;
             u.UserType = choice.user.UserType; 

             strcpy(u.name,choice.user.username);
             strcpy(u.password,choice.user.password);
          
             struct Account a;
             a.id = u.id;
             a.Amount = 0;
             u.Account = a;
             Write_User(u.id,&u);
             return -5;
        }

        if(choice.choice == 6){
            // Deletes The account;

           struct User u;
           Read_User(choice.amount,&u);
           u.havingaccount = 0;
           Write_User(choice.amount,&u);
        }

        if(choice.choice == 7){
           return -7;

        }



        if(choice.choice == 3){
             return u.Account.Amount;
        }
        return -1;
    }

   

    return 0;
}


void * handle_Client(void *client_fd){
   
   
  int clientdes = *(int *)client_fd;
   //free(client_fd);
 
 
  
   if(clientdes != -1){
    struct Choice choice; 
    struct user user; 
   
    const char *ok_sig = "ok"; // ok signal; 
    const char *failed = "Fail"; // Failed Signal; 
    read(clientdes,&user,sizeof(struct user)); 
    int Loginstatus = Login(user); 
    if(Loginstatus == 1){
         write(clientdes,ok_sig,5);
    }
    else{
         write(clientdes,failed,5); 
         close(clientdes); 
         return NULL;
    }

    while(1){
         read(clientdes,&choice,sizeof(struct Choice)); 
         printf("choice values %d %d\n",choice.choice,choice.amount);
       
         int Choice_status = Choice_Handler(user,choice); 
         printf("%d\n",Choice_status);

         
         if(choice.choice == 4){
             write(clientdes,"Bye From Server",50); 
             close(clientdes);
             return NULL;
         }

         if(Choice_status == -7){
              struct user user; 
              struct User u;
              Read_User(choice.amount,&u);
              strcpy(user.username,u.name);
              strcpy(user.password,u.password);
              user.id = u.id;
              user.UserType = u.UserType;
              
              write(clientdes,&user,sizeof(struct user));

         }

         if(Choice_status == -5){
            
             write(clientdes,ok_sig,5); 
             
         }
         else if((Choice_status != -5) && (Choice_status != -1) && (Choice_status != -7)){
            
             write(clientdes,&Choice_status,sizeof(Choice_status));
         }
         else if((Choice_status == 0) || (Choice_status == -1)){
            
             write(clientdes,failed,5); 
         }

    }

    printf("%s %s\n",user.username,user.password);  
    close(clientdes);
    return NULL;

  } 

  return NULL; 
  
  
  

}


int Main_Server_loop(struct Socket_Info *sock_info){


    sock_info->Socketfd = socket(AF_INET,SOCK_STREAM,0); 
    sock_info->server_addr.sin_family = AF_INET;
    sock_info->server_addr.sin_port = htons(8000);
    sock_info->server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  
        
   if(bind(sock_info->Socketfd,(struct sockaddr *)(&sock_info->server_addr),sizeof(sock_info->server_addr)) < 0){
      printf("Hererror in binding");
      return -1;
   }
   if(listen(sock_info->Socketfd,100)){
       // back log of 100
       return -1;
   }

   while(1){
       int client_fd = accept(sock_info->Socketfd,(struct sockaddr *)NULL,NULL); 
       printf("%d Client connected\n",client_fd);

       // assigning a new thread for the client;
       if(client_fd != -1){
        pthread_t t; 
        int *clientfd = (int *)malloc(sizeof(int)); 
        *clientfd = client_fd; 
        pthread_create(&t,NULL,handle_Client,clientfd);         
       }
           
   }
}




int main(int argv,const char *args[]){


     // Making The Adminstrator and User(we can create accounts ,Delete and View Accounts form Admin Panel also);
    
    struct Socket_Info sock_info;
    struct User u;
    strcpy(u.name, "Honey"); 
    strcpy(u.password ,"Pass");
    u.id = 0;
    u.havingaccount = 1;
    u.UserType = 0;
    struct Account account; 
    account.id = 0;
    account.Amount = 0;
    account.Account_Type = 1;
    u.Account = account;


    struct User u1;
    strcpy(u1.name,"NewUser"); 
    strcpy(u1.password,"NewPassoword");
    u1.id = 1;
    u1.havingaccount = 1;
    u1.UserType = 1;
    struct Account account1; 
    account1.id = 0;
    account1.Amount = 0;
    account1.Account_Type = 1;
    u1.Account = account1;

    
    //

    int fd = open("User.db",O_RDWR); 
    lseek(fd,0,SEEK_SET);
    write(fd,&u,sizeof(struct User));
    write(fd,&u1,sizeof(struct User));
    
    Main_Server_loop(&sock_info);


    return 0; 
}








