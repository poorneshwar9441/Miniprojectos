int Init_Socket(struct Socket_Info *sock_info){
  sock_info->Socketfd = socket(AF_INET,SOCK_STREAM,0); 
  sock_info->server_addr.sin_family = AF_INET;
  sock_info->server_addr.sin_port = htons(8000);
  sock_info->server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  
 return 0;
}