#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declarations.h"

void die(const char *message) {
	printf("ERROR: %s\n", message);

	exit(1);
}

/* Function generates key signature */
char *keysignature(char *key, int keylen) {
	int i, c, bit_c = 0;
	char *keysign = malloc(sizeof(char) * 6);
	
	// Counting number of 1 bits in the key
	for (i = 0; i < keylen; i++)
	{
		c = key[i];
		while(c > 0)
		{
			if((c & 1) > 0) // Using bit wise AND operator
				bit_c++;
			c = c >> 1; // Using right shift bit-wise operator
		}
	}
	
	keysign[0] = bit_c;  // Number of 1 bits in the key
	// Right Rotating the bits of my initials
	keysign[1] = (char)((255 & 'M') << 4) | ('M' >> 4);
	keysign[2] = (char)((255 & 'T') << 4) | ('T' >> 4);
	keysign[3] = (char)((255 & 'Z') << 4) | ('Z' >> 4);
	keysign[4] = keylen;
	keysign[5] = '\0';
	return keysign;
}


// stores the key in a memory block and returns a pointer to it
char *readkeyfile(FILE *fp) {
	fseek(fp, 0, SEEK_END);
	int keylen = ftell(fp);
	// allocate memory on heap to store the key
	char *key = malloc(sizeof(char) * keylen);
	fseek(fp, 0, SEEK_SET);
	int i, c;
	for (i = 0; i < keylen; i++) {
		c = fgetc(fp);
		key[i] = c;
	}
	return key;
}


// Checks the key signature present in the encrypted file
void check_sign(FILE *fp, char *key_sign, char *file_op) {
	char file_key_sign[6];
	fseek(fp, -5, SEEK_END);
	fgets(file_key_sign, 6, fp);
	if ((strcmp(file_key_sign, key_sign)) == 0) {
		if (strcmp(file_op, "-e") == 0) {
			fclose(fp);
			free(key_sign);
			die("File is already encrypted with this key.");
		}
	} else {
		if (strcmp(file_op, "-d") == 0) {
			fclose(fp);
			free(key_sign);
			die("Cannot decrypt, wrong key!");
		}
	}
}


// Runs the encryption / decryption algorithm
FILE *run_algorithm(FILE *fp, char *key, int keylen, char *file_op) {
	fseek(fp, 0, SEEK_END);
	long file_size = ftell(fp);
	if (strcmp(file_op, "-d") == 0)
		file_size -= 5;
	
	fseek(fp, 0, SEEK_SET);
	int i, j = 0, c;
	unsigned long foffset;
	for (i = 0; i < file_size; i++) {		
		c = fgetc(fp);
		c = ~(c ^ key[j]);
		foffset = ftell(fp);
		fseek(fp, foffset -1, SEEK_SET);
		fputc(c,fp);
		fseek(fp, foffset, SEEK_SET);
	
		j++;
		// set j to starting position of key
		if ( j >= keylen)
			j = 0;
	}
	return fp;
}