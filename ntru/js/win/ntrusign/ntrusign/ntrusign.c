#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ntrusign.h"
#include "api.h"
#include "rng.h"
#include "shred.h"

#define MAX_MARKER_LEN 50

#define KAT_SUCCESS 1
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR -3
#define KAT_CRYPTO_FAILURE -4

#if defined(WIN32) || defined(_WIN32)

#define EXPORT __declspec(dllexport)

#else

#define EXPORT

#endif



unsigned char seed[48];
unsigned char msg[3300];
unsigned char entropy_input[48];
unsigned char *sm, *m1;
unsigned long long smlen, mlen1;
unsigned char *yx;
char AlgName[] = "pqNTRUSign";

unsigned char pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES];
int ret_val;

EXPORT int Initial(char *str) {
  for (int i = 0; i < 48; i++) {
    entropy_input[i] = i;
  }
  randombytes_init(entropy_input, str, 256);
  randombytes(seed, 48);
  if ((ret_val = crypto_sign_keypair(pk, sk)) != 0) {
    printf("crypto_sign_keypair returned <%d>\n", ret_val);
    return KAT_CRYPTO_FAILURE;
  }
  printf("init success");
  return KAT_SUCCESS;
}

EXPORT unsigned char *Ntrusign(unsigned char *msg, unsigned char *ssk) {
  unsigned long long mlen = strlen(msg);
  m1 = (unsigned char *)calloc(mlen + CRYPTO_BYTES, sizeof(unsigned char));
  sm = (unsigned char *)calloc(mlen + CRYPTO_BYTES, sizeof(unsigned char));

  if ((ret_val = crypto_sign(sm, &smlen, msg, mlen, ssk)) != 0) {
    printf("crypto_sign returned <%d>\n", ret_val);
    return KAT_CRYPTO_FAILURE;
  }
  printf("\nlength of signed message  ===  %llu\n", smlen);
  printf("signed message == \n");
  printBstr(sm, smlen);
  printf("\n\n");
  return sm;
}

EXPORT unsigned char *GetPublicKey() {
  printf("\n");
  printf("public key == \n");
  printBstr(pk, 2065);
  printf("\n");
  return pk;
}

EXPORT unsigned char *GetPrivateKey() {
  printf("\n");
  printf("private key == \n");
  printBstr(sk, 2604);
  printf("\n");
  return sk;
}
EXPORT unsigned char *Secrect2Pub(unsigned char *skey) {
  unsigned char *publickey[CRYPTO_PUBLICKEYBYTES];
  Secret2Public(skey, publickey);
  printf("\n");
  printf("transpublic key == \n");
  printBstr(pk, 2065);
	return publickey;
}

EXPORT int Ntrusign_Verify(unsigned char *msg, unsigned char *sm,
                          unsigned char *spk,
                    int lenofsm) {
  smlen = lenofsm;
  unsigned long long mlen;
  mlen = strlen(msg);
  //    printf("\n");
  //    printf("smlen ==== %llu",smlen);
  //     printf("\nspk ==== %zu",strlen(spk));
  //     printf("\n");
  printf("\nlength of signed messege = %d", lenofsm);
  if (m1 == NULL) {
    m1 = (unsigned char *)calloc(smlen, sizeof(unsigned char));
  }
  if ((ret_val = crypto_sign_open(m1, &mlen1, sm, smlen, spk)) != 0) {
    printf("crypto_sign_open returned <%d>\n", ret_val);
    return KAT_CRYPTO_FAILURE;
  }
  if (mlen != mlen1) {
    printf(
        "crypto_sign_open returned bad 'mlen': Got <%llu>, expected <%llu>\n",
        mlen1, mlen);
    return KAT_CRYPTO_FAILURE;
  }
  if (memcmp(msg, m1, mlen)) {
    printf("crypto_sign_open returned bad 'm' value\n");
    return KAT_CRYPTO_FAILURE;
  }
  printf("message is ok\n");
  return KAT_SUCCESS;
}

// verify
