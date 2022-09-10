#ifndef __DECLARATIONS_H // Include guards
#define __DECLARATIONS_H

void die(const char *message);
char *keysignature(char *key, int keylen);
char *readkeyfile(FILE *fp);
void check_sign(FILE *fp, char *key_sign, char *file_op);
FILE *run_algorithm(FILE *fp, char *key, int keylen, char *file_op);

#endif
