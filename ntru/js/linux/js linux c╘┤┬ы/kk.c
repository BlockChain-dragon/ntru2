/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


//
//  PQCgenKAT_sign.c
//
//  Created by Bassham, Lawrence E (Fed) on 8/29/17.
//  Copyright © 2017 Bassham, Lawrence E (Fed). All rights reserved.
//
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rng.h"
#include "api.h"
#include "shred.h"
#define MAX_MARKER_LEN 50

#define KAT_SUCCESS 0
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR -3
#define KAT_CRYPTO_FAILURE -4




char AlgName[] = "pqNTRUSign";

int main() {
	
  unsigned char seed[48];
  unsigned char msg[3300];
  unsigned char entropy_input[48];
  unsigned char *m, *sm, *m1;
  unsigned long long mlen, smlen, mlen1;
  unsigned char *yx;


  unsigned char pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES];
  int ret_val;

  clock_t start, end;
  clock_t total_keygen = 0;
  clock_t total_sign = 0;
  clock_t total_verify = 0;

  // Create the REQUEST file
  /*sprintf(fn_req, "PQCsignKAT_%d.req", CRYPTO_SECRETKEYBYTES);
  if ((fp_req = fopen(fn_req, "w")) == NULL) {
    printf("Couldn't open <%s> for write\n", fn_req);
    return KAT_FILE_OPEN_ERROR;
  }
  sprintf(fn_rsp, "PQCsignKAT_%d.rsp", CRYPTO_SECRETKEYBYTES);
  if ((fp_rsp = fopen(fn_rsp, "w")) == NULL) {
    printf("Couldn't open <%s> for write\n", fn_rsp);
    return KAT_FILE_OPEN_ERROR;
  }
  */
  for (int i = 0; i < 48; i++) entropy_input[i] = i;
  yx = "12313";
  randombytes_init(entropy_input, yx, 256);

  randombytes(seed, 48);

  mlen = 33;
  unsigned char mmm[33];
  randombytes(msg, mlen);

  printf(" msg  =  \n");
  printBstr(msg, mlen);

  /*randombytes(mmm, mlen);
  printf(" mmm  =  \n");
  printBstr(mmm, mlen);*/
  // Create the RESPONSE file based on what's in the REQUEST file


  printf(" seed  =  \n");
  printBstr(seed, 48);

  //randombytes_init(seed, yx, 256);


  m = (unsigned char *)calloc(mlen, sizeof(unsigned char));
  m1 = (unsigned char *)calloc(mlen + CRYPTO_BYTES, sizeof(unsigned char));
  sm = (unsigned char *)calloc(mlen + CRYPTO_BYTES, sizeof(unsigned char));


  // Generate the public/private keypair
  start = clock();
  if ((ret_val = crypto_sign_keypair(pk, sk)) != 0) {
    printf("crypto_sign_keypair returned <%d>\n", ret_val);
    return KAT_CRYPTO_FAILURE;
  }
  end = clock();
  total_keygen += (end - start);
  printf(" pk  =  \n");
  printBstr(pk, CRYPTO_PUBLICKEYBYTES);
  printf(" sk  =  \n");
  printBstr(pk, CRYPTO_SECRETKEYBYTES);


  start = clock();
  if ((ret_val = crypto_sign(sm, &smlen, m, mlen, sk)) != 0) {
    printf("crypto_sign returned <%d>\n", ret_val);
    return KAT_CRYPTO_FAILURE;
  }
  end = clock();
  total_sign += (end - start);


  start = clock();
  if ((ret_val = crypto_sign_open(m1, &mlen1, sm, smlen, pk)) != 0) {
    printf("crypto_sign_open returned <%d>\n", ret_val);
    return KAT_CRYPTO_FAILURE;
  }
  end = clock();
  total_verify += (end - start);
  if (mlen != mlen1) {
    printf(
        "crypto_sign_open returned bad 'mlen': Got <%llu>, expected <%llu>\n",
        mlen1, mlen);
    return KAT_CRYPTO_FAILURE;
  }

  if (memcmp(m, m1, mlen)) {
    printf("crypto_sign_open returned bad 'm' value\n");
    return KAT_CRYPTO_FAILURE;
  }

  free(m);
  free(m1);
  free(sm);


  printf("finished test: keygen %fs; sign %fs; verify %fs\n",
         (double)total_keygen / CLOCKS_PER_SEC / 100,
         (double)total_sign / CLOCKS_PER_SEC / 100,
         (double)total_verify / CLOCKS_PER_SEC / 100);
  return KAT_SUCCESS;
}

//
// ALLOW TO READ HEXADECIMAL ENTRY (KEYS, DATA, TEXT, etc.)
//


//
// ALLOW TO READ HEXADECIMAL ENTRY (KEYS, DATA, TEXT, etc.)
//


