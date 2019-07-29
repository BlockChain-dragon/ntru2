cmake_minimum_required(VERSION 3.10)
project(Project2 C)

set(CMAKE_C_STANDARD 11)

include_directories(Project2)

add_executable(Project2
        Project2/api.h
        Project2/crypto_hash_sha512.c
        Project2/crypto_hash_sha512.h
        Project2/crypto_stream.c
        Project2/crypto_stream_salsa20.h
        Project2/DGS.c
        Project2/fastrandombytes.c
        Project2/fastrandombytes.h
        Project2/misc.c
        Project2/ntru.h
        Project2/NTT.c
        Project2/NTT.h
        Project2/packing.c
        Project2/packing.h
        Project2/param.c
        Project2/param.h
        Project2/poly.c
        Project2/poly.h
        Project2/PQCgenKAT_sign.c
        Project2/pqNTRUSign.c
        Project2/pqNTRUSign.h
        Project2/project2.c
        Project2/rng.c
        Project2/rng.h
        Project2/shred.c
        Project2/shred.h
        Project2/sign.c)
