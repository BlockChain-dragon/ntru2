#include "ntru.h"
#include<jni.h>
#include<wchar.h>
#include<Windows.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rng.h"
#include "api.h"
#include "shred.h"

#define MAX_MARKER_LEN 50

#define KAT_SUCCESS 1
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR -3
#define KAT_CRYPTO_FAILURE -4

unsigned char seed[48];
unsigned char msg[3300];
unsigned char entropy_input[48];
unsigned char  *sm, *m1;
unsigned long long smlen, mlen1;
unsigned char *yx;

jstring charTojstring(JNIEnv *env, const char *str);

unsigned char pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES];
int ret_val;
void printtohex(JNIEnv *env, jstring jstr);

JNIEXPORT void JNICALL Java_ntrusign_Ntrusign_InitialKey(JNIEnv *env,
                                                         jobject obj,
                                                         jstring jstr) {
  char *yx;
  yx = (char *)(*env)->GetStringUTFChars(env, jstr, NULL);
  for (int i = 0; i < 48; i++) entropy_input[i] = i;
  randombytes_init(entropy_input, yx, 256);
  randombytes(seed, 48);

  if ((ret_val = crypto_sign_keypair(pk, sk)) != 0) {
    printf("crypto_sign_keypair returned <%d>\n", ret_val);
    return KAT_CRYPTO_FAILURE;
  }
  //printf(" pk  =  \n");
 // printBstr(pk, CRYPTO_PUBLICKEYBYTES);
 // printf(" sk  =  \n");
 // printBstr(sk, CRYPTO_SECRETKEYBYTES);
 
 (*env)->ReleaseStringUTFChars(env, jstr, yx);
  printf("initial success\n");


}

JNIEXPORT jbyteArray JNICALL Java_ntrusign_Ntrusign_Sign(JNIEnv *env, jobject obj,
                                                        jbyteArray jmsg,
                                                        jbyteArray jsk) {
  unsigned char *lmsg;
  lmsg = (unsigned char *)(*env)->GetByteArrayElements(env, jmsg, NULL);


  unsigned char *privak =
      (unsigned char *)(*env)->GetByteArrayElements(env, jsk, NULL);


//	printBstr(privak, CRYPTO_SECRETKEYBYTES);

  unsigned long long mlen = (*env)->GetArrayLength(env, jmsg);
  printf("\n message == :");
  printBstr(lmsg, mlen);
  m1 = (unsigned char *)calloc(mlen + CRYPTO_BYTES, sizeof(unsigned char));
  sm = (unsigned char *)calloc(mlen + CRYPTO_BYTES, sizeof(unsigned char));

  if ((ret_val = crypto_sign(sm, &smlen, lmsg, mlen, privak)) != 0) {
    printf("crypto_sign returned <%d>\n", ret_val);
    return KAT_CRYPTO_FAILURE;
  }
  printf("\nlength signed message  ===  %d \nsigned message == ", smlen);
  printBstr(sm, smlen);
  jcharArray smg = (*env)->NewByteArray(env, smlen);
  (*env)->SetByteArrayRegion(env, smg, 0, smlen, sm);
  return smg;
    
}
// sign 


//getpublickey
JNIEXPORT jbyteArray JNICALL Java_ntrusign_Ntrusign_GetPublicKey(JNIEnv *env,
                                                               jobject obj) {


  jcharArray kuri = (*env)->NewByteArray(env, CRYPTO_PUBLICKEYBYTES);
  (*env)->SetByteArrayRegion(env, kuri, 0, CRYPTO_PUBLICKEYBYTES, pk);

  printf("\nPublicKey == :");
  printBstr(pk, CRYPTO_PUBLICKEYBYTES);


	return kuri;
}

//getprivatekey
JNIEXPORT jbyteArray JNICALL Java_ntrusign_Ntrusign_GetPrivateKey(JNIEnv *env,
                                                               jobject obj)
{
  jcharArray asu = (*env)->NewByteArray(env, CRYPTO_SECRETKEYBYTES);
  (*env)->SetByteArrayRegion(env, asu, 0, CRYPTO_SECRETKEYBYTES, sk);
  printf("\nPrivateKey == :");
  printBstr(sk, CRYPTO_SECRETKEYBYTES);
  return asu;

}
// verify
JNIEXPORT jint JNICALL Java_ntrusign_Ntrusign_Verify(JNIEnv * env, jobject obj, jbyteArray jstr, jbyteArray mmm, jbyteArray jch) {


  unsigned char *smsg;
  unsigned long long mlen;
  smsg = (unsigned char *)(*env)->GetByteArrayElements(env, jstr, NULL);

  smlen = (*env)->GetArrayLength(env,jstr);
  
  unsigned char *jpk;
  jpk = (unsigned char *)(*env)->GetByteArrayElements(env, jch, NULL);
 
  unsigned char *mmmsg;
  mmmsg = (unsigned char *)(*env)->GetByteArrayElements(env, mmm, NULL);
  mlen = (*env)->GetArrayLength(env, mmm);
  
  if (m1 == NULL) {
    m1 = (unsigned char *)calloc(smlen, sizeof(unsigned char));
  }

  if ((ret_val = crypto_sign_open(m1, &mlen1, smsg, smlen, jpk)) != 0) {
    printf("crypto_sign_open returned <%d>\n", ret_val);
    return KAT_CRYPTO_FAILURE;
  } 
    if (mlen != mlen1) {
    printf(
        "crypto_sign_open returned bad 'mlen': Got <%llu>, expected <%llu>\n",
        mlen1, mlen);
    return KAT_CRYPTO_FAILURE;
  }
  if (memcmp(mmmsg, m1, mlen)) {
    printf("crypto_sign_open returned bad 'm' value\n");
    return KAT_CRYPTO_FAILURE;
  }
  //printf("\n-----------verify success!");
  return KAT_SUCCESS;

}

void printtohex(JNIEnv *env, jstring jstr) {
  char *lol;
  lol = (char *)(*env)->GetStringUTFChars(env, jstr, NULL);
  printf(" what I get  =  \n ");
  printBstr(lol, CRYPTO_SECRETKEYBYTES);
}

JNIEXPORT jbyteArray JNICALL Java_ntrusign_Ntrusign_Secret2Public(JNIEnv * env,
	jobject obj,jbyteArray sk) {
  unsigned char *private =
      (unsigned char *)(*env)->GetByteArrayElements(env, sk, NULL);
  unsigned char public[CRYPTO_PUBLICKEYBYTES];
  Secret2Public(private, public);
  jcharArray kuri = (*env)->NewByteArray(env, CRYPTO_PUBLICKEYBYTES);
  (*env)->SetByteArrayRegion(env, kuri, 0, CRYPTO_PUBLICKEYBYTES, public);
  printf("\ntransPublicKey == :");
  printBstr(public, CRYPTO_PUBLICKEYBYTES);
  return kuri;

}
jstring charTojstring(JNIEnv *env, const char *str) {
  jstring rtn = 0;
  int slen = strlen(str);
  unsigned short *buffer = 0;
  if (slen == 0)
    rtn = (*env)->NewStringUTF(env, str);
  else {
    int length = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str, slen, NULL, 0);
    buffer = (unsigned short *)malloc(length * 2 + 1);
    if (MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str, slen, (LPWSTR)buffer,
                            length) > 0)
      rtn = (*env)->NewString(env, (jchar *)buffer, length);

    free(buffer);
  }
  return rtn;
}