/*
 * api.h
 *
 *  Created on: Sep 1, 2017
 *      Author: zhenfei
 */

#ifndef API_H_
#define API_H_

#define CRYPTO_ALGNAME "Uniform1024"
#define TEST_PARAM_SET  Uniform_1024_205
#define CRYPTO_SECRETKEYBYTES 2604
#define CRYPTO_PUBLICKEYBYTES 2065
#define CRYPTO_BYTES 2065
#define CRYPTO_RANDOMBYTES 32

int crypto_sign_keypair(
    unsigned char       *pk,
    unsigned char       *sk);

int crypto_sign(
    unsigned char       *sm,
    unsigned long long  *smlen,
    const unsigned char *m,
    unsigned long long  mlen,
    const unsigned char *sk);

int crypto_sign_open(
    unsigned char *m,
    unsigned long long  *mlen,
    const unsigned char *sm,
    unsigned long long  smlen,
    const unsigned char *pk);
/*
int crypto_sign_keypair_KAT(
    unsigned char       *pk,
    unsigned char       *sk,
    const unsigned char *randomness);

int crypto_sign_KAT(
    unsigned char       *sm,
    unsigned long long  *smlen,
    const unsigned char *m,
    unsigned long long  mlen,
    const unsigned char *sk,
    const unsigned char *randomness);
*/
#endif /* API_H_ */
