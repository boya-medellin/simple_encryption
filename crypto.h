#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <inttypes.h>

#define DEPTH 3
#define BLOCK_SIZE 128
#define KEY_SIZE 64
#define ROUNDS 4

char abc[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
char beaufort_matrix[26][26];

char* GenKeychar(int );

char* xor_words(char* , char* );

char* one_time_pad_encr(char*, char* );

char* one_time_pad_decr(char* , char*);

void word_decryption(char* , char* );

char * rail_fence_encr(char * );

char * rail_fence_decr(char * );

int function_affine(int , int , int , int );

int inverse_function_affine(int , int , int , int );

char * affine_encr(char * , int , int , int );

char * affine_decr(char * , int , int , int );

void GenBeaufort();

char * beaufort_encr(char * , char * );

char * beaufort_decr(char * , char * );

uint64_t GenKey();

uint64_t f(uint32_t , uint32_t );

uint64_t feistel_encr(char *);
