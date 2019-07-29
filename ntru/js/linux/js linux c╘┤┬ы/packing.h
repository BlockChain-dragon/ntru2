/*
 * packing.h
 *
 *  Created on: Sep 1, 2017
 *      Author: zhenfei
 */

#ifndef PACKING_H_
#define PACKING_H_

/*
 * unpack the secret key and the public key
 * from char string
 */

int unpack_secret_key(
    const unsigned char   *blob,
    PQ_PARAM_SET       *param,
    int64_t        *f,
    int64_t        *g,
    int64_t        *g_inv,
    int64_t        *h);

/*
 * pack the secret key and the public key
 * into char string
 */
int pack_secret_key(
    unsigned char   *blob,
    const PQ_PARAM_SET *param,
    const int64_t  *f,
    const int64_t  *g,
     int64_t  *g_inv,
    const int64_t  *h);

/*
 * unpack the public key or the signature
 * from char string
 */
int unpack_public_key(
    const unsigned char   *blob,
    PQ_PARAM_SET *param,
    int64_t  *h);

/*
 * pack the public key or the signature
 * into char string
 */
int pack_public_key(
    unsigned char   *blob,
    const PQ_PARAM_SET *param,
    const int64_t  *h);

#endif /* PACKING_H_ */
