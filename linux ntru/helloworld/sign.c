/*
 * sign.c
 *
 * this document contains a wrapper to the signing algorithms
 *
 *
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pqNTRUSign.h"
#include "param.h"
#include "api.h"
#include "crypto_hash_sha512.h"
#include "packing.h"
#include "shred.h"
/*  generate a pair of keys */
int crypto_sign_keypair(
    unsigned char       *pk,
    unsigned char       *sk)
{
    /* load the parameters */
    PQ_PARAM_SET    *param;
    param           = pq_get_param_set_by_id(TEST_PARAM_SET);

    /* memory allocations */
    int64_t         *mem, *buf;
    int64_t         *f, *g, *g_inv, *h;

    buf = malloc(sizeof(int64_t)*param->padded_N*4);
    mem = malloc(sizeof(int64_t)*param->padded_N*4);

    if (!buf ||!mem)
    {
//        printf("malloc error!\n");
        return -1;
    }

    f       = mem;
    g       = f     + param->padded_N;
    g_inv   = g     + param->padded_N;
    h       = g_inv + param->padded_N;


    /* call key generation functions */
    keygen(f,g,g_inv,h,buf,param);

    /* pack the public key h into pk*/
    pack_public_key(pk, param, h );

    /*
     * pack the secret key f, g, g_inv and
     * the public key h into sk
     *
     * Alternatively, pack f and g only,
     * and recover h and g_inv during
     * signing
     */

    pack_secret_key(sk, param, f, g, g_inv, h);

    memset(buf, 0, sizeof(int64_t)*param->padded_N*4);
    memset(mem, 0, sizeof(int64_t)*param->padded_N*4);
    free(buf);
    free(mem);

    return 0;
}

/* wrapper of signing algorithm */
int crypto_sign(
    unsigned char       *sm,
    unsigned long long  *smlen,
    const unsigned char *m,
    unsigned long long  mlen,
    const unsigned char *sk)
{
    /* load the parameters */
    PQ_PARAM_SET    *param;
    param           = pq_get_param_set_by_id(TEST_PARAM_SET);


    /* memory allocations */
    int64_t         *mem, *buf;
    int64_t         *f, *g, *g_inv, *h, *sig;
    int             counter;
    uint64_t        temp;
    buf = malloc(sizeof(int64_t)*param->padded_N*11);
    mem = malloc(sizeof(int64_t)*param->padded_N*5);

    if (!buf ||!mem)
    {
//        printf("malloc error!\n");
        return -1;
    }
    memset(buf,0, sizeof(int64_t)*param->padded_N*11);
    memset(mem,0, sizeof(int64_t)*param->padded_N*5);


    f       = mem;
    g       = f     + param->padded_N;
    g_inv   = g     + param->padded_N;
    h       = g_inv + param->padded_N;
    sig     = h     + param->padded_N;

    /* unpack the keys */
    unpack_secret_key(sk, param, f, g, g_inv, h);

    /*
     * signing the message, return the number of
     * rejections
     */
    counter = sign(sig, m,mlen, f,g,g_inv,h, buf,param);

    memcpy(sm, m, mlen);

    /* pack the signature */
    pack_public_key(sm+mlen, param, sig);
    *smlen = CRYPTO_BYTES + mlen ;


    memset(buf,0, sizeof(int64_t)*param->padded_N*11);
    memset(mem,0, sizeof(int64_t)*param->padded_N*5);
    free(mem);
    free(buf);

    return 0;
}


/* wrapper of verification algorithm */
int crypto_sign_open(
    unsigned char *m,
    unsigned long long  *mlen,
    const unsigned char *sm,
    unsigned long long  smlen,
    const unsigned char *pk)
{

    /* load the parameters */
    PQ_PARAM_SET    *param;
    param           = pq_get_param_set_by_id(TEST_PARAM_SET);

    /* memory allocations */
    int64_t         *mem, *buf;
    int64_t         *f, *g, *g_inv, *h, *sig;

    buf = malloc(sizeof(int64_t)*param->padded_N*7);
    mem = malloc(sizeof(int64_t)*param->padded_N*5);

    if (!buf ||!mem)
    {
//        printf("malloc error!\n");
        return -1;
    }
    memset(buf,0, sizeof(int64_t)*param->padded_N*7);
    memset(mem,0, sizeof(int64_t)*param->padded_N*5);

    f       = mem;
    g       = f     + param->padded_N;
    g_inv   = g     + param->padded_N;
    h       = g_inv + param->padded_N;
    sig     = h     + param->padded_N;



    /* unpack the key and the signature */
    unpack_public_key(pk, param,  h);

    *mlen = smlen-CRYPTO_BYTES;
   // printf("===== %llu \n", *mlen);
    memcpy(m, sm, *mlen);
    printBstr(m, *mlen);
    unpack_public_key(sm+(*mlen), param,  sig);


    /* verification process */
    if(verify(sig, m, *mlen, h,buf,param)!=0)
    {
//        printf("verification error\n");

        memset(buf,0, sizeof(int64_t)*param->padded_N*7);
        memset(mem,0, sizeof(int64_t)*param->padded_N*5);

        free(buf);
        free(mem);
        return -1;
    }

    else
    {
        /* signature verified */
        memset(buf,0, sizeof(int64_t)*param->padded_N*7);
        memset(mem,0, sizeof(int64_t)*param->padded_N*5);

        free(buf);
        free(mem);

        return 0;
    }
}
