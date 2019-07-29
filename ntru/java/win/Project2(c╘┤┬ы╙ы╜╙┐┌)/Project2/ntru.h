/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class ntrusign_Ntrusign */

#ifndef _Included_ntrusign_Ntrusign
#define _Included_ntrusign_Ntrusign
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     ntrusign_Ntrusign
 * Method:    InitialKey
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_ntrusign_Ntrusign_InitialKey
  (JNIEnv *, jobject, jstring);

/*
 * Class:     ntrusign_Ntrusign
 * Method:    Sign
 * Signature: ([B[B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_ntrusign_Ntrusign_Sign
  (JNIEnv *, jobject, jbyteArray, jbyteArray);

/*
 * Class:     ntrusign_Ntrusign
 * Method:    Verify
 * Signature: ([B[B[B)Z
 */
JNIEXPORT jint JNICALL Java_ntrusign_Ntrusign_Verify
  (JNIEnv *, jobject, jbyteArray, jbyteArray, jbyteArray);

/*
 * Class:     ntrusign_Ntrusign
 * Method:    GetPrivateKey
 * Signature: ()[B
 */
JNIEXPORT jbyteArray JNICALL Java_ntrusign_Ntrusign_GetPrivateKey
  (JNIEnv *, jobject);

/*
 * Class:     ntrusign_Ntrusign
 * Method:    GetPublicKey
 * Signature: ()[B
 */
JNIEXPORT jbyteArray JNICALL Java_ntrusign_Ntrusign_GetPublicKey
  (JNIEnv *, jobject);

/*
 *class:		ntrusign_Ntrusign
 *Method:		Secret3public
 *Signatutre: ()[B
 */
JNIEXPORT jbyteArray JNICALL Java_ntrusign_Ntrusign_Secret2Public
(JNIEnv *,jobject,jbyteArray);


#ifdef __cplusplus
}
#endif
#endif
