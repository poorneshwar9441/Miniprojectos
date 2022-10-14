#include "client.h"


int main_client_func(){
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8000);
    const char *serv_addr = "127.0.0.1"; 

    if(inet_pton(AF_INET,serv_addr,&server_addr.sin_addr) <= 0){
        printf("Here");
        return -1;
    }

    int sockfd = socket(AF_INET,SOCK_STREAM,0); 
    if(sockfd < 0){
        return -1;
    }

    if(connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(server_addr)) < 0){
        printf("connect error");
        return -1;
    }


    // processing loop for client 
    char buffer[100] = {0}; // For Reply signals; 
   



    // Name and Password; 
     struct User user; 
    // user.username = {0}; 
    // user.password = {0}; 

    // User Info
    printf("Enter your name: ");
    scanf("%s",user.username);
    printf("Enter your password: ");
    scanf("%s",user.password);
    printf("Enter your Userid: "); 
    scanf("%d",&user.id);
    printf("Enter your Account Type: \n0 for Admin\n1 for Normal User: \n");
    scanf("%d",&user.UserType); 
    

    printf("%s %s\n",user.username,user.password);


    write(sockfd,&user,sizeof(struct User)); 
    read(sockfd,buffer,100); 


    if(buffer[0] == 'o' && buffer[1] == 'k'){
        printf("Login sucessfull\n"); 
    }
    else{
        printf("Login failed\n");
        return 0; 
    }


int flag = 1;
while(flag){

    if(user.UserType == 0){
        
        printf("Welcome to the admin panel\n");
        printf("Enter your choice \n");
        printf("1. Create a new account\n");
        printf("2. Delete an account\n");
        printf("3. View an account\n"); 
        printf("4. Exit\n");
        int choice;
        scanf("%d",&choice);
        struct Choice c;
        c.choice = choice;
        c.amount = 0;
    

        switch(choice){ 
             case 1:
                c.choice = 5;
                struct User user; 
                printf("Enter The User name: "); 
                scanf("%s",user.username); 
                printf("Enter The password: "); 
                scanf("%s",user.password); 
                printf("Enter User id: "); 
                scanf("%d",&user.id); 
                printf("Enter User Type 0 for admin 1 for Normal User : ");
                scanf("%d",&user.UserType); 
                c.user = user; 
                write(sockfd,&c,sizeof(struct Choice)); 
                read(sockfd,buffer,100); 
                if(buffer[0] == 'o' && buffer[1] == 'k'){
                    printf("Account created Sucessfully\n");
                }
                else if(buffer[0] == 'F' && buffer[1] == 'k'){
                    printf("Account creation Failed\n");
                }
                else{
                    printf("oops No Reply From the server\n");
                }
                break;


            case 2:
               c.choice = 6;
               printf("Enter the Userid That You want to delete: \n");
               scanf("%d",&c.amount);
               write(sockfd,&c,sizeof(struct Choice));
               break;

            case 3:
               c.choice = 7;
               printf("Enter the Userid of The account That you want to view Deatails about: \n");
               scanf("%d",&c.amount);
               write(sockfd,&c,sizeof(struct Choice));
               struct User u;
               read(sockfd,&u,sizeof(struct User));
               printf("--**UserDetails**--\n");
               printf("Username: %s\n",u.username);
               printf("Password: %s\n",u.password);
               if(u.UserType == 0){
                   printf("Account Type: admin\n");
               }
               else{
                   printf("Account Type: Normaluser\n");
               }
               printf("--**------**---\n");
               break;



            case 4:
               write(sockfd,&c,sizeof(struct Choice));
               read(sockfd,buffer,100); 
               printf("%s\n",buffer);
               flag = 0;
               break;
                
        }
        

    }

    else{

      printf("Enter your choice: \n");
      printf("1. Deposit\n");
      printf("2. Withdraw\n");
      printf("3. Balance\n");
      printf("4. Exit\n");

      int choice;
      struct Choice c;
      scanf("%d",&choice);
      c.choice = choice;
      c.amount = 0;

      switch(choice){
          case 1: 
            //struct Choice choice; 
            //choice.choice = 1;
            printf("Enter the amount to Deposit\n"); 
            int amount; 
            scanf("%d",&amount); 
            c.amount = amount;

            write(sockfd,&c,sizeof(struct Choice)); 
            read(sockfd,buffer,sizeof(buffer)); 
            if(buffer[0] == 'o' && buffer[1] == 'k'){
                printf("Amount Deposited Sucessfully\n");
            }

            if(buffer[0] == 'F' && buffer[1] == 'a'){
               printf("Error in Depositing Money\n");
            }
            break;  


          case 2:
             printf("Enter the amount to withdraw\n");
             scanf("%d",&amount); 
             c.amount = amount; 
             write(sockfd,&c,sizeof(struct Choice)); 
             read(sockfd,buffer,100); 
             printf("%s\n",buffer);
             break;

           case 3:
              write(sockfd,&c,sizeof(struct Choice));
              read(sockfd,&amount,sizeof(amount)); 
              printf("Your Balance Amount is %d\n",amount);
              break;


            case 4: 
               write(sockfd,&c,sizeof(struct Choice));
               read(sockfd,buffer,100); 
               printf("%s\n",buffer);
               flag = 0;
               break;

      }
    


     

    }
}

}

int main(int argc,const char *argv[]){
    main_client_func();

    return 0;
}