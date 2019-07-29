/*
 * CPQREF/shred.c
 *
 *  Copyright 2014 John M. Schanck
 *
 *  This file is part of CPQREF.
 *
 *  CPQREF is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  CPQREF is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with CPQREF.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include "shred.h"
#include "param.h"
#include "poly.h"
#include "fastrandombytes.h"
#include "crypto_hash_sha512.h"
#include "api.h"

void shred( void *v, size_t n )
{
  volatile unsigned char *p = ( volatile unsigned char * )v;
  while( n-- ) *p++ = 0;
}
void printBstr(unsigned char *A, unsigned long long L) {
  unsigned long long i;

  for (i = 0; i < L; i++) printf("%hhX", A[i]);

  if (L == 0) printf("00");

  printf("\n\n");
}
void Secret2Public(unsigned char *sk, unsigned char *pk) {
  PQ_PARAM_SET *param;
  param = pq_get_param_set_by_id(TEST_PARAM_SET);
  int64_t *mem, *buf;
  int64_t *f, *g, *g_inv, *h;
  buf = malloc(sizeof(int64_t) * param->padded_N * 11);
  mem = malloc(sizeof(int64_t) * param->padded_N * 5);

  if (!buf || !mem) {
    printf("malloc error!\n");
    return -1;
  }
  memset(buf, 0, sizeof(int64_t) * param->padded_N * 11);
  memset(mem, 0, sizeof(int64_t) * param->padded_N * 5);

  f = mem;
  g = f + param->padded_N;
  g_inv = g + param->padded_N;
  h = g_inv + param->padded_N;

  unpack_secret_key(sk, param, f, g, g_inv, h);
  pack_public_key(pk, param, h);
}