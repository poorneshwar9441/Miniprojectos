#include"Bank.h" 


int  Read_Account(int id,struct Account *Read_Info){
   /**
    * Flile Locking parms; 
    * 
    * 
    */

    int fd = open("Account.db",O_RDWR); 
    struct flock *lock = (struct flock *)malloc(sizeof(struct flock)); 
    lock->l_type  = F_WRLCK; 
    lock->l_whence = SEEK_SET;
    lock->l_start = 0; 
    lock->l_len = 0; 
    lock->l_pid = getpid();

    fcntl(fd,F_SETLKW,lock); 
    printf("Inside The critial section\n"); 
    lseek(fd,id*sizeof(struct Account),SEEK_SET); 
    read(fd,Read_Info,sizeof(struct Account)); 

    lock->l_type = F_UNLCK;
    fcntl(fd,F_SETLKW,lock); 
    free(lock); 

    return 0; 


}


int Write_Account(int id,struct Account *Write_Info){
   /**
    * Flile Locking parms; 
    * 
    * 
    */

    int fd = open("Account.db",O_RDWR); 
    struct flock *lock = (struct flock *)malloc(sizeof(struct flock)); 
    lock->l_type  = F_WRLCK; 
    lock->l_whence = SEEK_SET;
    lock->l_start = 0; 
    lock->l_len = 0; 
    lock->l_pid = getpid();

    fcntl(fd,F_SETLKW,lock); 
    printf("Inside The critial section\n"); 
    lseek(fd,id*sizeof(struct Account),SEEK_SET); 

    write(fd,Write_Info,sizeof(struct Account)); 

    lock->l_type = F_UNLCK;
    fcntl(fd,F_SETLKW,lock); 
    free(lock); 
     

    return 0; 

}


int  Read_User(int id,struct User *Read_Info){
   /**
    * Flile Locking parms; 
    * 
    * 
    */

    int fd = open("User.db",O_RDWR); 
    struct flock *lock = (struct flock *)malloc(sizeof(struct flock)); 
    lock->l_type  = F_WRLCK; 
    lock->l_whence = SEEK_SET;
    lock->l_start = 0; 
    lock->l_len = 0; 
    lock->l_pid = getpid();

    fcntl(fd,F_SETLKW,lock); 
    printf("Inside The critial section\n"); 
    lseek(fd,id*sizeof(struct User),SEEK_SET); 

    struct User temp;
    read(fd,&temp,sizeof(struct User)); 
    printf("\nHere Bank file is User name %s And %d\n",temp.name,temp.id);
    *Read_Info = temp;

    lock->l_type = F_UNLCK;
    fcntl(fd,F_SETLKW,lock); 
    free(lock); 

    return 0; 


}


int Write_User(int id,struct User *Write_Info){
   /**
    * Flile Locking parms; 
    * 
    * 
    */

    int fd = open("User.db",O_RDWR); 
    struct flock *lock = (struct flock *)malloc(sizeof(struct flock)); 
    lock->l_type  = F_WRLCK; 
    lock->l_whence = SEEK_SET;
    lock->l_start = 0; 
    lock->l_len = 0; 
    lock->l_pid = getpid();

    fcntl(fd,F_SETLKW,lock); 
    printf("Inside The critial section\n"); 
    
    lseek(fd,id*sizeof(struct User),SEEK_SET); 
    write(fd,Write_Info,sizeof(struct User)); 
    lock->l_type = F_UNLCK;
    fcntl(fd,F_SETLKW,lock); 
    free(lock);
   
    

    return 0; 
}