#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/random.h>

// size of key in bytes created by keygen function
// currently set to maximum length of message to avoid key reuse
#define KEYSIZE 1024

unsigned int * keygen(void) {
	/// Function to generate random key data
	unsigned int * keys = malloc(KEYSIZE);
	if(keys == NULL) {
		fprintf(stderr, "[ERROR] Failed to allocate memory");
		exit(1);
	}	
	if(getrandom(keys, KEYSIZE, 0) == -1) {
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
	// attempt to ensure proper null termination
	ciphertext[textsize+1] = '\0';
	for(int i = 0; i < textsize; i++) {
		ciphertext[i] = message[i] ^ keys[i % 256];
	}
	// no character checks done here
	// this output may contain null characters
	// and other delimiters in random places after XOR unless manually removed
	return ciphertext;
}

int main(void) {
	// set to keysize to avoid key reuse
	char * message = malloc(KEYSIZE);
	unsigned int * keys = keygen();
	char * ciphertext;
	printf("Enter message to be encrypted: ");
	fgets(message, KEYSIZE, stdin);
	printf("Encrypting message: %s\n", message);
	ciphertext = crypt(message, keys);
	printf("Encrypted message: \"%s\"\n", ciphertext);
	// NOTE: this output may not be completely accurate
	// as no delimiters (such as null) are removed from ciphertext, and C string functions
	// such as strlen() rely on these delimiters to work, which results in
	// output being occasionally cut off or incorrectly displayed at times
	ciphertext = crypt(ciphertext, keys);
	printf("Decrypted: %s\n", ciphertext);
	// free dynamic allocations here
	// this isn't technically required but whatever it's in the spec
	free(ciphertext);
	free(keys);
	free(message);
	return 0;
}
