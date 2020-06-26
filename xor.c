#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/random.h>

unsigned int * keygen(void) {
	unsigned int * keys = malloc(256);
	if(keys == NULL) {
		fprintf(stderr, "[ERROR] Failed to allocate memory");
		return -1;
	}	
	if(getrandom(keys, 256, NULL) == -1) {
		fprintf(stderr, "[ERROR] Failed to generate random bytes for keys");
		return -1;
	}
	return keys;
}

char * crypt(char * message, unsigned int * keys) {
	/// Function to encrypt/decrypt data using XOR
	return -1;
}

int main(void) {
	char * message[] = "Ayylmao Testing";
	puts("Getting keys...");
	unsigned int * keys = keygen();
	printf("Encrypting %s\n", message);
	return 0;
}
