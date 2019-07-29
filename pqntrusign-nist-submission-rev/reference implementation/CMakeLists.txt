cmake_minimum_required(VERSION 3.10)
project(reference_implementation C)

set(CMAKE_C_STANDARD 11)

include_directories(common)
include_directories(Gaussian-1024)
include_directories(Uniform-1024)

add_executable(reference_implementation
        common/crypto_hash_sha512.c
        common/crypto_hash_sha512.h
        common/crypto_stream.c
        common/crypto_stream_salsa20.h
        common/DGS.c
        common/fastrandombytes.c
        common/fastrandombytes.h
        common/misc.c
        common/NTT.c
        common/NTT.h
        common/packing.c
        common/packing.h
        common/param.c
        common/param.h
        common/poly.c
        common/poly.h
        common/pqNTRUSign.c
        common/pqNTRUSign.h
        common/rng.c
        common/rng.h
        common/shred.c
        common/shred.h
        Gaussian-1024/api.h
        Gaussian-1024/PQCgenKAT_sign.c
        Gaussian-1024/sign.c
        Uniform-1024/api.h
        Uniform-1024/PQCgenKAT_sign.c
        Uniform-1024/sign.c)
