#include "ntru.h"
#include<jni.h>
#include<wchar.h>
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


unsigned char *yx;
char AlgName[] = "pqNTRUSign";
jstring charTojstring(JNIEnv *env, const char *str);

unsigned char pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES];
int ret_val;
void printtohex(JNIEnv *env, jstring jstr);

JNIEXPORT void JNICALL Java_ntrusign_Ntrusign_InitialKey(JNIEnv *env,
        jobject obj,
        jstring jstr) {
    unsigned char *yx;
    yx = (unsigned char *) (*env)->GetStringUTFChars(env, jstr, NULL);
    for (int i = 0; i < 48; i++) {
        entropy_input[i] = i;
    }
    randombytes_init(entropy_input, yx, 256);

    randombytes(seed, 48);

    if ((ret_val = crypto_sign_keypair(pk, sk)) != 0) {
//        printf("crypto_sign_keypair returned <%d>\n", ret_val);
        return KAT_CRYPTO_FAILURE;
    }
    //printf(" pk  =  \n");
    // printBstr(pk, CRYPTO_PUBLICKEYBYTES);
    // printf(" sk  =  \n");
    // printBstr(sk, CRYPTO_SECRETKEYBYTES);

   (*env)->ReleaseStringUTFChars(env, jstr, yx);
//    printf("Initial success!!\n");

}

JNIEXPORT jbyteArray JNICALL Java_ntrusign_Ntrusign_Sign(JNIEnv *env, jobject obj,
        jbyteArray jmsg,
        jbyteArray jsk) {
    unsigned long long smlen;
    unsigned char *lmsg;
    unsigned long long mlen;
    lmsg = (unsigned char *) (*env)->GetByteArrayElements(env, jmsg, NULL);


    unsigned char *privak =
            (unsigned char *) (*env)->GetByteArrayElements(env, jsk, NULL);


    //	printBstr(privak, CRYPTO_SECRETKEYBYTES);

    mlen = (*env)->GetArrayLength(env, jmsg);
//    printf("\n messsage == : ");
//    printBstr(lmsg, mlen);
//    printf("\n");
    unsigned char *sm, *m1;
    m1 = (unsigned char *) calloc(mlen + CRYPTO_BYTES, sizeof (unsigned char));
    sm = (unsigned char *) calloc(mlen + CRYPTO_BYTES, sizeof (unsigned char));

    if ((ret_val = crypto_sign(sm, &smlen, lmsg, mlen, privak)) != 0) {
//        printf("crypto_sign returned <%d>\n", ret_val);
        return KAT_CRYPTO_FAILURE;
    }
    //log
//    printf("\n  smlen ===  %llu \n\n", smlen);
//    printf("sign success\n signmessage == ");
//    printBstr(sm, smlen);
//    printf("\n");

    jcharArray smg = (*env)->NewByteArray(env, smlen);

    (*env)->SetByteArrayRegion(env, smg, 0, smlen, sm);
    (*env)->ReleaseByteArrayElements(env, jmsg, lmsg, NULL);
    (*env)->ReleaseByteArrayElements(env, jsk, privak, NULL);
    free(sm);
    free(m1);
    return smg;

}
// sign 


//getpublickey

JNIEXPORT jbyteArray JNICALL Java_ntrusign_Ntrusign_GetPublicKey(JNIEnv *env,
        jobject obj) {


    jcharArray kuri = (*env)->NewByteArray(env, CRYPTO_PUBLICKEYBYTES);
    (*env)->SetByteArrayRegion(env, kuri, 0, CRYPTO_PUBLICKEYBYTES, pk);



    return kuri;
}

//getprivatekey

JNIEXPORT jbyteArray JNICALL Java_ntrusign_Ntrusign_GetPrivateKey(JNIEnv *env,
        jobject obj) {
    jcharArray asu = (*env)->NewByteArray(env, CRYPTO_SECRETKEYBYTES);
    (*env)->SetByteArrayRegion(env, asu, 0, CRYPTO_SECRETKEYBYTES, sk);

    return asu;

}
// verify

JNIEXPORT jint JNICALL Java_ntrusign_Ntrusign_Verify(JNIEnv * env, jobject obj, jbyteArray jstr, jbyteArray mmm, jbyteArray jch) {

    unsigned long long  smlen,mlen1;
    unsigned char *smsg;
    unsigned long long mlen;
    smsg = (unsigned char *) (*env)->GetByteArrayElements(env, jstr, NULL);

    smlen = (*env)->GetArrayLength(env, jstr);

    unsigned char *jpk;
    jpk = (unsigned char *) (*env)->GetByteArrayElements(env, jch, NULL);

    unsigned char *mmmsg;
    mmmsg = (unsigned char *) (*env)->GetByteArrayElements(env, mmm, NULL);
    mlen = (*env)->GetArrayLength(env, mmm);
    unsigned char *m1;

    m1 = (unsigned char *) calloc(smlen, sizeof (unsigned char));


    if ((ret_val = crypto_sign_open(m1, &mlen1, smsg, smlen, jpk)) != 0) {
//        printf("crypto_sign_open returned <%d>\n", ret_val);
        return KAT_CRYPTO_FAILURE;
    }
    if (mlen != mlen1) {
//        printf(
//                "crypto_sign_open returned bad 'mlen': Got <%llu>, expected <%llu>\n",
//                mlen1, mlen);
        return KAT_CRYPTO_FAILURE;
    }
    if (memcmp(mmmsg, m1, mlen)) {
//        printf("crypto_sign_open returned bad 'm' value\n");
        return KAT_CRYPTO_FAILURE;
    }
//    printf("\n-----------verify success!");
    (*env)->ReleaseByteArrayElements(env, jstr, smsg, NULL);
    (*env)->ReleaseByteArrayElements(env, jch, jpk, NULL);
    (*env)->ReleaseByteArrayElements(env, mmm, mmmsg, NULL);
    free(m1);
    return KAT_SUCCESS;


}

JNIEXPORT jbyteArray JNICALL Java_ntrusign_Ntrusign_Secret2Public(JNIEnv * env,
        jobject obj, jbyteArray sk) {
    unsigned char *private =
            (unsigned char *) (*env)->GetByteArrayElements(env, sk, NULL);
    unsigned char public[CRYPTO_PUBLICKEYBYTES];
    Secret2Public(private, public);
    jcharArray kuri = (*env)->NewByteArray(env, CRYPTO_PUBLICKEYBYTES);
    (*env)->SetByteArrayRegion(env, kuri, 0, CRYPTO_PUBLICKEYBYTES, public);
//    printf("\ntransPublicKey == :");
//    printBstr(public, CRYPTO_PUBLICKEYBYTES);
    (*env)->ReleaseByteArrayElements(env, sk, private, NULL);
    return kuri;

}


