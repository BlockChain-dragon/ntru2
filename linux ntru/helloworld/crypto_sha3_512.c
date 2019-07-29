/* -------------------------------------------------------------------------
 * Works when compiled for either 32-bit or 64-bit targets, optimized for 
 * 64 bit.
 *
 * Canonical implementation of Init/Update/Finalize for SHA-3 byte input. 
 *
 * SHA3-256, SHA3-384, SHA-512 are implemented. SHA-224 can easily be added.
 *
 * Based on code from http://keccak.noekeon.org/ .
 *
 * I place the code that I wrote into public domain, free to use. 
 *
 * I would appreciate if you give credits to this work if you used it to 
 * write or test * your code.
 *
 * Aug 2015. Andrey Jivsov. crypto@brainhub.org
 * ---------------------------------------------------------------------- */

/* *************************** Self Tests ************************ */

/* 
 * There are two set of mutually exclusive tests, based on SHA3_USE_KECCAK,
 * which is undefined in the production version.
 *
 * Known answer tests are from NIST SHA3 test vectors at
 * http://csrc.nist.gov/groups/ST/toolkit/examples.html
 *
 * SHA3-256:
 *   http://csrc.nist.gov/groups/ST/toolkit/documents/Examples/SHA3-256_Msg0.pdf
 *   http://csrc.nist.gov/groups/ST/toolkit/documents/Examples/SHA3-256_1600.pdf
 * SHA3-384: 
 *   http://csrc.nist.gov/groups/ST/toolkit/documents/Examples/SHA3-384_1600.pdf 
 * SHA3-512: 
 *   http://csrc.nist.gov/groups/ST/toolkit/documents/Examples/SHA3-512_1600.pdf 
 *
 * These are refered to as [FIPS 202] tests.
 *
 * -----
 *
 * A few Keccak algorithm tests (when M and not M||01 is hashed) are
 * added here. These are from http://keccak.noekeon.org/KeccakKAT-3.zip,
 * ShortMsgKAT_256.txt for sizes even to 8. There is also one test for 
 * ExtremelyLongMsgKAT_256.txt.
 *
 * These will work with this code when SHA3_USE_KECCAK converts Finalize
 * to use "pure" Keccak algorithm.
 *
 *
 * These are referred to as [Keccak] test.
 *
 * -----
 *
 * In one case the input from [Keccak] test was used to test SHA3
 * implementation. In this case the calculated hash was compared with
 * the output of the sha3sum on Fedora Core 20 (which is Perl's based).
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "sha3.h"
void printBstr(unsigned char *A, unsigned long long L);
int mystrlen(unsigned char *str) {
  unsigned char *temp = str;
  while ('\0' != *str) str++;
  return str - temp;
}
int crypto_hash_sha512(unsigned char *out, const unsigned char *in,
                       unsigned long long inlen)
{
  sha3_context c;
  uint8_t *hash;
  sha3_Init512(&c);
  sha3_Update(&c, in, inlen);
  hash = sha3_Finalize(&c);
  for (int i = 0; i < 64; i++) {
    out[i] = hash[i];
  }
  return 1;
}

