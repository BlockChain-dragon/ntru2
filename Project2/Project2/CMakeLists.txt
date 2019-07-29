cmake_minimum_required(VERSION 3.10)
project(Project2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Project2
        api.h
        crypto_hash_sha512.c
        crypto_hash_sha512.h
        crypto_stream.c
        crypto_stream_salsa20.h
        DGS.c
        fastrandombytes.c
        fastrandombytes.h
        misc.c
        ntru.h
        NTT.c
        NTT.h
        packing.c
        packing.h
        param.c
        param.h
        poly.c
        poly.h
        PQCgenKAT_sign.c
        pqNTRUSign.c
        pqNTRUSign.h
        project2.c
        rng.c
        rng.h
        shred.c
        shred.h
        sign.c)
