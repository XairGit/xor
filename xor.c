#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/random.h>

unsigned int * keygen(void) {
	/// Function to generate random key data
	unsigned int * keys = malloc(256);
	if(keys == NULL) {
		fprintf(stderr, "[ERROR] Failed to allocate memory");
		exit(1);
	}	
	if(getrandom(keys, 256, 0) == -1) {
		fprintf(stderr, "[ERROR] Failed to generate random bytes for keys");
		exit(2);
	}
	return keys;
}

char * crypt(char * message, unsigned int * keys) {
	/// Function to encrypt/decrypt data using XOR
	int textsize = strlen(message);
	char * ciphertext = malloc(textsize+1);
	if(ciphertext == NULL) {
		fprintf(stderr, "[ERROR] Failed to allocate memory");
		exit(1);
	}
	// ensure proper null termination
	ciphertext[textsize+1] = '\0';
	for(int i = 0; i < textsize; i++) {
		ciphertext[i] = message[i] ^ keys[i % 256];
	}
	return ciphertext;
}

int main(void) {
	char message[] = "Ayylmao Testing";
	puts("Getting keys...");
	unsigned int * keys = keygen();
	printf("Encrypting message: \"%s\"\n", message);
	char * ciphertext = crypt(message, keys);
	printf("Encrypted message: \"%s\"\n", ciphertext);
	puts("Decrypting message...");
	ciphertext = crypt(ciphertext, keys);
	printf("Decrypted: \"%s\"\n", ciphertext);
	free(ciphertext);
	free(keys);
	return 0;
}
