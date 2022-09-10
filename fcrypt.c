#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int main(int argc, char *argv[]) {
	if (argc < 4) {
		printf("USAGE: fcrypt <-e/-d> <file> <key_file>\n");
		return 1;
	}
	
	// Copying the arguments
	char *file_op = argv[1];
	char *filename = argv[2];
	char *keyfilename = argv[3];
	
	printf("\nFile Op: %s\n", file_op);
	printf("Filename: %s\n", filename);
	printf("Key Filename: %s\n", keyfilename);
	
	FILE *fp1, *fp2;
	fp1 = fopen(filename, "rb+");
	if (!fp1)
		die("Cannot open file");

	fp2 = fopen(keyfilename, "r");
	if (!fp2) {
		fclose(fp1);
		die("Cannot open keyfile");
	}
	if (strcmp(file_op, "-e") != 0 && strcmp(file_op, "-d") != 0) {
		fclose(fp1);
		fclose(fp2);
		die("Enter valid command line argument <-e/-d>");
	}
	
	fseek(fp2, 0, SEEK_END);
	int keylen = ftell(fp2);
	char *key = readkeyfile(fp2);

	fclose(fp2);

	char *key_sign = keysignature(key, keylen); // Generate Key Signature

	check_sign(fp1, key_sign, file_op); // Verify Key Signature from the file

	fp1 = run_algorithm(fp1, key, keylen, file_op); // Runs the encryption/Decryption Algorithm

	free(key); // Freeing memory off the heap
	// Append Key Signature
	int i;
	if (strcmp(file_op, "-e") == 0)
	{
		for(i = 0; key_sign[i] != '\0'; i++)
			fputc(key_sign[i], fp1);
	}
	
	free(key_sign); // Freeing memory off the heap
	
	// Remove key signature
	
	if (strcmp(file_op, "-d") == 0)
	{
		FILE *ftemp;
		char *temp = "temp.txt";
		int c;
	
		fseek(fp1, 0, SEEK_END);
		long file_size = ftell(fp1);
		file_size -= 5;

		if ((ftemp = fopen(temp, "wb+")) != NULL)
		{
			fseek(fp1, 0, SEEK_SET);
			for (i = 0; i < file_size; ++i)
			{
				c = fgetc(fp1);
				fputc(c, ftemp);
			}
			
			fclose(ftemp);
		}
		fclose(fp1);
		remove(filename);
		rename(temp, filename);
	}
	
	if (strcmp(file_op, "-e") == 0) fclose(fp1);
	printf("\nThe operation completed successfully!\n");	

	return 0;
}
