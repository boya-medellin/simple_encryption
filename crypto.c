#include "crypto.h"

char* GenKeychar(int LENGTH){
  char *key=malloc(LENGTH);
  FILE *fpointer;
  fpointer = fopen("/dev/urandom", "r");
  fread(key, sizeof(char)*LENGTH, 1, fpointer);
  fclose (fpointer);
  return key;
}

char* xor_words(char* cipher1, char* cipher2){
  int i;
  char* xor = malloc(strlen(cipher1));
  for (i=0; i<strlen(cipher1); ++i){
    xor[i] = (cipher1[i] ^ cipher2[i]);
  }
  return xor;
}

char* one_time_pad_encr(char* plain, char* key){
  int i;
  char * cipher = malloc(strlen(plain));
  for (i=0; i<strlen(plain); ++i){ 
    cipher[i] = (char)(plain[i] ^ key[i]);
  }
  cipher[i] = '\0';
  return cipher;
}

char* one_time_pad_decr(char* cipher, char*key){
  int i;
  char * plain = malloc(strlen(cipher));
  for(i=0; i<strlen(cipher); ++i){
    plain[i] = (char)(cipher[i] ^ key[i]);
  }
  plain[i] = '\0';
  return plain;
}


void word_decryption(char* cipher1, char* cipher2){
  char * xor_cipher = xor_words(cipher1, cipher2);

  char word1[2048], word2[2048];

  FILE *f1 = fopen("words.txt", "r");
  while (fgets(word1, 2048, f1) != NULL){
    FILE *f2 = fopen("words.txt", "r");
    while (fgets(word2, 2048, f2) != NULL){
      char * xor_current = xor_words(word1, word2);
      if (!(strcmp(xor_current, xor_cipher))){
        puts(word1);
        puts(word2);
      }
    }
    fclose(f2);
  }
  fclose(f1);
}

char * rail_fence_encr(char * plain){
  int length = strlen(plain);

  char matrix[DEPTH][length];
  for (int i=0; i<DEPTH; ++i){
    for (int j=0; j<length; ++j){
      matrix[i][j] = '\n';
    }
  }

  int row=0;
  int k=-1;
  for (int i=0; i<length; ++i){
    matrix[row][i] = plain[i];
    if (row==0 || row == DEPTH-1){
      k *= -1;
    }
    row = row + k;
  }

  char * cipher = malloc(length);
  for (int i=0; i<DEPTH; ++i){
    for (int j=0; j<length; ++j){
      if (matrix[i][j] != '\n'){
        strncat(cipher, &matrix[i][j], 1);
      }
    }
  }
  return cipher;
}

char * rail_fence_decr(char * cipher){
  int length = strlen(cipher);

  char matrix[DEPTH][length];
  for (int i=0; i<DEPTH; ++i){
    for (int j=0; j<length; ++j){
      matrix[i][j] = '\n';
    }
  }

  int row=0;
  int k=-1;
  for (int i=0; i<length; ++i){
    matrix[row][i] = '*';
    if (row==0 || row == DEPTH-1){
      k *= -1;
    }
    row = row + k;
  }

  int m = 0;
  for (int i=0; i<DEPTH; ++i){
    for (int j=0; j<length; ++j){
      if (matrix[i][j] == '*'){
        matrix[i][j] = cipher[m++];
      }
    }
  }

  char * plain = malloc(length);
  row=0;
  k=-1;
  for (int i=0; i<length; ++i){
    strncat(plain, &matrix[row][i], 1);
    if (row==0 || row == DEPTH-1){
      k *= -1;
    }
    row = row + k;
  }

  return plain;
}

int function_affine(int a, int b , int m, int x){
  return (5*x+8)%26;
}

int modular_multiplicative_inverse_mod(int m, int a){
  for (int i=0; i<m; ++i){
    if ( (a*i)%m == 1){
      return i;
    }
  }
}

int inverse_function_affine(int a, int b, int m, int x){
  int mmi = modular_multiplicative_inverse_mod(m, a);
  return mmi * ( (x-b) % m );
}

char * affine_encr(char * plain, int a, int b, int m){
  int length = strlen(plain);
  char * cipher = malloc(length);

  for (int i=0; i<length; ++i){
    int x;
    int new_x;
    for (int j=0; j<26; ++j){
      if (plain[i] == abc[j]){
        x = j;
        new_x = function_affine(a, b, m, x);
        strncat(cipher, &abc[new_x], 1);
        break;
      }
    }
  }
  return cipher;
}

char * affine_decr(char * cipher, int a, int b, int m){
  int length = strlen(cipher);
  char * plain = malloc(length);

  for (int i=0; i<length; ++i){
    int x;
    int new_x;
    for (int j=0; j<26; ++j){
      if (cipher[i] == abc[j]){
        x = j;
        new_x = inverse_function_affine(a, b, m, x);
        strncat(plain, &abc[new_x], 1);
        break;
      }
    }
  }
  return plain;
}

void GenBeaufort(){
  for (int i=0; i<26; ++i){
    for (int j=0; j<26; ++j){ 
      int index = (i+j)%26;
      beaufort_matrix[i][j] = abc[index];
    }
  }
}

char * beaufort_encr(char * plain, char * key){
  int length = strlen(plain);
  char * cipher = malloc(length);

  for (int i=0; i<length; ++i){
    for (int j=0; j<26; ++j){
      if (beaufort_matrix[0][j] == plain[i]){
        for (int k=0; k<26; ++k){
          if ( beaufort_matrix[k][j] == key[i] ){
            strncat(cipher, &beaufort_matrix[k][0], 1);
            break;
          }
        }
        break;
      }
    }
  }
  return cipher;
}

char * beaufort_decr(char * cipher, char * key){
  int length = strlen(cipher);
  char * plain = malloc(length);

  for (int i=0; i<length; ++i){
    for (int j=0; j<26; ++j){
      if (beaufort_matrix[0][j] == cipher[i]){
        for (int k=0; k<26; ++k){
          if ( beaufort_matrix[k][j] == key[i] ){
            strncat(plain, &beaufort_matrix[k][0], 1);
            break;
          }
        }
        break;
      }
    }
  }
  return plain;
}

uint64_t GenKey(){
  uint64_t key;
  FILE *fpointer;
  fpointer = fopen("/dev/urandom", "r");
  fread(&key, sizeof(uint64_t), 1, fpointer);
  fclose (fpointer);
  return key;
}

uint64_t f(uint32_t block, uint32_t key){
  return (block^key);
}

uint64_t feistel_encr(char *plain){
  uint64_t left, right, i, left_tmp, right_tmp, key;;
  int len = strlen(plain), len1=len/2;
  char * leftstr=malloc(KEY_SIZE), *rightstr=malloc(KEY_SIZE);

  strncpy(leftstr, plain, len1);
  strncpy(rightstr, plain + len1, len1);
  
  left = (uint64_t)leftstr;
  right = (uint64_t)rightstr;
  free(leftstr);
  free(rightstr);

  for (i=0; i<ROUNDS; ++i){
    key = GenKey();
    left_tmp =  (f(left, key) ^ right);
    right_tmp = left;
    left = right_tmp;
    right = left_tmp;
  }

  return (uint64_t)left | right;
}

int main(){
  return 0;
}
