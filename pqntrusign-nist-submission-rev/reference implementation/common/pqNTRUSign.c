/*
 *  Copyright 2017 Zhenfei Zhang @ onboard security
 *
 *  This file is part of pqNTRUSign signature scheme with bimodal
 *  Gaussian sampler (Gaussian-pqNTRUSign).
 *
 *  This software is released under GPL:
 *  you can redistribute it and/or modify it under the terms of the
 *  GNU General Public License as published by the Free Software
 *  Foundation, either version 2 of the License, or (at your option)
 *  any later version.
 *
 *  You should have received a copy of the GNU General Public License.
 *  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "param.h"
#include "poly.h"
#include "fastrandombytes.h"
#include "crypto_hash_sha512.h"


/*
 * input a polynomial a(x)
 * compute a polynomial a(x)*x mod x^N+1
 */

static
void rotate(
            int64_t     *poly,
    const   PQ_PARAM_SET*param)
{
    int64_t tmp;
    tmp = poly[param->N-1];
    memmove(poly+1, poly, (param->N-1)*sizeof(int64_t));
    poly[0] = -tmp;
}

/*
 * compute the F norm of the secret keys
 * rejecting the keys if they are too big
 */

static
int64_t normf(
    const   int64_t   *f,
    const   PQ_PARAM_SET*param)
{
    int64_t *buf;
    int64_t *rotate_f;
    int64_t *sum;
    int64_t norm;
    int16_t i,j;
    buf = malloc(sizeof(int64_t)*param->padded_N*3);

    rotate_f    = buf;
    sum         = rotate_f + param->padded_N;
    memcpy(rotate_f, f, sizeof(int64_t)*param->padded_N);
    memcpy(sum,      f, sizeof(int64_t)*param->padded_N);

    for (i=0;i<param->N-1;i++)
    {
        rotate(rotate_f, param);
        for (j=0;j<param->N;j++)
            sum[j] += rotate_f[j];
    }
    norm = 0;
    for (i=0;i<param->N;i++)
    {
        if (norm < abs(sum[i]))
            norm = abs(sum[i]);
    }
    free(buf);
    return norm;

}


/*
 * generate a set of private/public key pairs.
 * requires a buffer for 4 padded polynomials
 */

void keygen(
            int64_t     *f,         /* output - secret key */
            int64_t     *g,         /* output - secret key */
            int64_t     *g_inv,     /* output - secret key */
            int64_t     *h,         /* output - public key */
            int64_t     *buf,       /* input  - buffer     */
    const   PQ_PARAM_SET*param)     /* input  - parameters */
{
    int64_t i;
    int64_t *fntt = buf;
    int64_t *gntt = buf  + param->padded_N;
    int64_t *hntt = gntt + param->padded_N;
    int64_t *tmp  = hntt + param->padded_N;  ;
    int     flag  = 0;


    memset(buf, 0, sizeof(int64_t)*param->padded_N*4);
    flag = 0;
    /*
     * generate flat trianry polynomials f and g
     * also compute g^-1 mod 2
     */
    while (flag != 1)
    {
        flag = 1;

        do {
            pol_gen_flat(f, param->N, param->d);
        }while (normf(f, param)>param->B_k);
        /* set f = pf */
        for (i=0;i<param->N;i++)
            tmp[i] = 2*f[i];
        /* convert f into NTT form */
        NTT(param,  tmp,    fntt);
        /* regenerate f if fntt has any 0 coeffs */
        for (i=0;i<param->N;i++)
        {
            if (fntt[i]==0)
                flag = 0;
        }
    }

    do{
        do{
            pol_gen_flat(g, param->N, param->d);
        }while (normf(g, param)>param->B_k);

    }while (pol_inv_mod2(g_inv, g, param->N) == -1);


    /* convert g into NTT form */
    NTT(param,  g,      gntt);

    for (i=0;i<param->N;i++)
    {
        /* compute f^-1 mod q */
        fntt[i] = InvMod(fntt[i],param->q);
        /* compute h = gf^-1 mod q */
        hntt[i] = gntt[i]*fntt[i] % param->q;
    }

    Inv_NTT(param, h, hntt);

    /* printf("normf %d %d  \n", normf(f, param), normf(g,param));*/
    return;
}


/*
 * rejection sampling on a bimodal sample
 * "sig" with sig = r \pm sec for r sampled from Gaussian
 * reject into a Gaussian
 */

int rejection_sampling(
    const   int64_t     *sec,
    const   int64_t     *sig,
    const   PQ_PARAM_SET*param)
{
    uint64_t    t;
    uint64_t    norm;
    uint64_t    scala;
    double      rate = param->Ms;
    long        bignum = 0xfffffff;

    norm    = get_scala (sec, sec, param->N);
    /* reject if |af|_2 > B_s */
    if (norm> param->B_s*param->B_s)
        return 0;

    scala   = abs(get_scala (sec, sig, param->N));

    /*
     * rate = 1/ M / exp(-norm/sigma^2/2) / cosh(scala/sigma^2)
     */
    rate *= exp(-(double)norm/(double)param->stdev/(double)param->stdev/2);
    rate *= cosh(scala/(double)param->stdev/(double)param->stdev);
    rate = 1/rate;

    /*
     * sample a random float between 0 and 1
     * accept if this float is small than rate
     */
    rng_uint64(&t);
    if ((1+(t&bignum))/((double)bignum+1)< rate)
        return 1;
    else
        return 0;   /* reject */
}





int
challenge(
            int64_t         *msg_dig,       /* output message digest */
    const   int64_t         *public_key,    /* input public key h */
    const   unsigned char   *msg,           /* input message */
    const   size_t          msg_len,        /* input message length */
    const   PQ_PARAM_SET    *param)         /* input  - parameters */
 
{
    uint16_t      i;
    uint16_t      j;
    uint16_t      k;
    uint8_t       r;

    unsigned char input[2*HASH_BYTES];
    unsigned char pool[HASH_BYTES];

    /* pool = hash(hash(msg) || hash(public key)) */
    crypto_hash_sha512(input, msg, msg_len);
    memcpy(input+HASH_BYTES, public_key, HASH_BYTES);
    crypto_hash_sha512(pool, input, 2*HASH_BYTES);

    j = 0;
    i = 0;
    k = 0;
    r = 0;
    while(i < param->N*2)
    {
        if(j == HASH_BYTES)
        {
            memcpy(input, pool, HASH_BYTES);
            crypto_hash_sha512(pool, input, HASH_BYTES);
            j = 0;
        }
        if(k == 8)
        {
            r = (uint8_t) pool[j++];
            k = 0;
        }
        msg_dig[i] = r&1;
        k++;
        r >>= 1;
        i++;
    }

    return 0;
}

/*
 * sign a message using rejection sampling method
 * returns the number of repetitions
 * buf memory requirement: 11 polynomials.
 */
int sign(
            int64_t     *sig,       /* output - signature  */
    const unsigned char *msg,       /* input  - message    */
    const   size_t      msg_len,    /* input  - length of msg */
    const   int64_t     *f,         /* input  - secret key */
    const   int64_t     *g,         /* input  - secret key */
    const   int64_t     *g_inv,     /* input  - secret key */
    const   int64_t     *h,         /* input  - public key */
            int64_t     *buf,       /* input  - buffer     */
    const   PQ_PARAM_SET*param)     /* input  - parameters */
{

    int64_t i;
    int64_t *r      = buf;
    int64_t *u1     = r      +  param->padded_N;
    int64_t *v1     = u1     +  param->padded_N;
    int64_t *v      = v1     +  param->padded_N;
    int64_t *a      = v      +  param->padded_N;
    int64_t *b      = a      +  param->padded_N;
    int64_t *buffer = b      +  param->padded_N;    /* 3 polynomials */
    int64_t *sptp   = buffer +  param->padded_N*3;  /* 2 polynomials */
    int     bit     = 0;    /* flip a bit for bimodal Gaussian */
    int     counter = 0;    /* number of samples to get a signature */

    int a1,a2,a3;
    a1 = 0;
    a2 = 0;
    a3 = 0;

    challenge (sptp, h, msg, 32, param);
/*    int total = 0;
    for (i=0;i<param->N*2;i++)
        total = total+sptp[i];
    printf("%d \n", total);
  */  
    sample:


        if(counter> 2000)
        {
            /* sign algorithm failed */
            /*
            printf("%d %d %d %d %d %d\n",counter, a1, a2, a3, normf(f, param), normf(g, param));

            for (i=0;i<param->N;i++)
                printf("%d, ", f[i]);
            printf("\n\n");

            for (i=0;i<param->N;i++)
                printf("%d, ", g[i]);
            printf("\n"); */

            printf("signature failed\n");
            return -1;
        }
        counter = counter+1;
        memset(buf, 0, sizeof(int64_t)*param->padded_N*9);

        /* sample r from discrete Gaussian and b from binary*/
        if (param->id==Gaussian_1024_205)
        {
            DGS(r, param->N, param->stdev);

            /* flipping bit for bimodal Gaussian */
            bit = rand()%2;
            if (bit==0)
                bit = -1;
        }
        /* or sample r from uniform and set b = 1*/
        else if (param->id== Uniform_1024_205)
        {
            pol_unidrnd(r,param->N,param->q/param->p);
            bit = 1;
        }


        
        /* u1 = p*r + u0 */
        for (i=0;i<param->N;i++)
            u1[i] = r[i]*param->p+sptp[i];

        /* v1 = u1 * h */
        pol_mul_coefficients( v1, h, u1, param, buffer);

        /* a = (v0-v1)/g  mod p*/
        for (i=0;i<param->N;i++)
            a[i] = cmod(sptp[i+param->N]-v1[i], param->p);
        
        pol_mul_mod_p(a, a, g_inv, param, buffer);

        /* v= v1+ag */
        pol_mul_coefficients(v, a, g, param, buffer);
        
        /* rejection sampling on t side, step 1 */
        if (max_norm(v, param->N)> param->B_t)
        {
            a1 ++;
            goto sample;
        }

        for (i=0;i<param->N;i++)
            v[i] = v1[i] + bit * v[i];
        /* rejection sampling on t side, step 2 */
        if (max_norm(v, param->N)> param->norm_bound_t)
        {
            a2 ++;
            goto sample;
        }

        /* b = af; sig = af +r   */
        pol_mul_coefficients(b, a, f, param, buffer);
        

        for (i=0;i<param->N;i++)
            sig[i] = r[i] + bit * b[i];
        
        /* now perform rejection sampling on Gaussian*/
        if (param->id==Gaussian_1024_205)
        {
            /* rejection sampling to make signature into a Gaussian */
            if (rejection_sampling(b, sig, param) == 0)
            {
                a3++;
                goto sample;
            }
        }
        else if (param->id== Uniform_1024_205)
        {
            /* rejection sampling to make signature into a uniform */
            if (max_norm(sig, param->N)>param->norm_bound_s)
            {
                a3++;
                goto sample;
            }
        }
        /* printf("%d %d %d %d\n",counter, a1, a2, a3); */
    return counter;
}

/*
 * verifies a signature, returns 0 if valid
 * buf memory requirement: 7 polynomials.
 */
int verify(
    const   int64_t     *sig,       /* input  - signature  */
    const unsigned char *msg,       /* input  - message    */
    const   size_t      msg_len,    /* input  - length of msg */
    const   int64_t     *h,         /* input  - public key */
            int64_t     *buf,       /* input  - buffer     */
    const   PQ_PARAM_SET*param)     /* input  - parameters */
{
    int64_t i;
    int64_t *u      = buf;
    int64_t *v      = u     + param->padded_N;
    int64_t *sptp   = v     + param->padded_N;    /* 2 polynomials */
    int64_t *buffer = sptp  + param->padded_N*2;

    challenge (sptp, h, msg, 32, param);



    /* check norm constrains */
    if (param->id==Gaussian_1024_205)
    {
        /* check if |s| is smaller than sigma*11 */
        if (max_norm(sig, param->N)>param->stdev*11)
        {
            printf("max norm failed\n");
            return -1;
        }
    }
    else if (param->id== Uniform_1024_205)
    {
        /* check if |s| is smaller than norm_bound_t */
        if (max_norm(sig, param->N)>param->norm_bound_s)
        {
            printf("max norm failed\n");
            return -1;
        }
    }


    /* reconstruct u = 2s + u_p */
    for (i=0;i<param->N;i++)
        u[i] = sig[i]*param->p + sptp[i];

    /* v = u * h */
    pol_mul_coefficients(v, u, h, param, buffer);

    /* check if v \equiv v_p mod p */
    for (i=0;i<param->N;i++)
    {
        if ((v[i]-sptp[i+param->N]) % param->p != 0)
        {
            printf("congruent condition failed for param %s \nv:\n", param->name);

            printf("sig:\n");
            for (i=0;i<param->padded_N;i++)
                printf("%lld,", (long long) sig[i]);
            printf("\nu:\n");
            for (i=0;i<param->padded_N;i++)
                printf("%lld,", (long long) u[i]);
            printf("\nv:\n");
            for (i=0;i<param->padded_N;i++)
                printf("%lld,", (long long) v[i]);
            printf("\nh:\n");
            for (i=0;i<param->padded_N;i++)
                printf("%lld,", (long long) h[i]);
            printf("\nmsg:\n");
            for (i=0;i<param->padded_N;i++)
                printf("%lld, ", (long long) sptp[i+param->N]);
            printf("\n\n");

            return -1;
        }
    }
    return 0;
}


