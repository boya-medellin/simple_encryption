# Simple Encryption Algorithms


## One Time Pad

  one_time_pad_encr(char*, char*) :

  one_time_pad_decr(char*, char*) :

  word_decryption(char*, char*) :


##  Rail Fence

  rail_fence_encr(char *) :

  rail_fence_decr(char *) :

##  Beaufort

  beaufort_encr(char *, char *) :

  beaufort_decr(char *, char *) :

##  Affine
  
  affine_encr(char*, int, int, int) :

  affine_decr(char*, int, int, int) :

##  Feistel
  
  uint64_t feistel_encr(char*):


## Helper Functions:

  DEPTH :
    The number of rows in the Rail Fence implementation.

  ROUNDS :
    The number of rounds in the Feistel implementation.

  BLOCK_SIZE :
    Block size used for the plaintext and cipertext in the Feistel implementation.

  KEY_SIZE :
    Block size used for the key in the Feistel implementation.

  char abc[26] :
    Helper meta in the implementation of the Beaufort and Affine algorithms

  char beaufort_matrix[26][26] :
    The Beaufort tableau.

  char* GenKeychar(int) :
    Used by One Time Pad to generate a random string key from /dev/urandom.

  char* xor_word(char *, char*) :
    Used by One Time Pad to XOR strings of the same length.

  int function_affine(int, int, int ,int) :
    Used by Affine algorithm to implement the char mapping.

  int modular_multiplicative_inverse_mod(int, int):
    Used by Affine decryption to find the modular multiplicative inverse of mod m.

  int function_inverse_affine(int, int, int, int) :
    Used by Affine algorithm to implement the inverse char mapping needed to implement decryption.

  void GenBeaufort() :
    Used by Beaufort algorithm to generate the beaufort tableau.

  uint64_t GenKey() :
    Used by Feistel algorithm to generate a random 64-bit key from /dev/urandom.

  uint64_t f(uint64_t, uint64_t) :
    Used by Feistel algorithm to implement the f(Ri, Ki) function.

