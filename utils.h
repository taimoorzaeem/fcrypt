#ifndef __UTILS_H 
#define __UTILS_H

void die(const char *message);
char *keysignature(const char *key, const int keylen);
char *readkeyfile(FILE *fp);
void check_sign(FILE *fp, char *key_sign, const char *file_op);
FILE *run_algorithm(FILE *fp, const char *key, const int keylen, const char *file_op);

#endif
