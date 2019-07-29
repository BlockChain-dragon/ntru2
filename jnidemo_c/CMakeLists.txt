cmake_minimum_required(VERSION 3.10)
project(jnidemo_c C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(jnidemo_c
        com_zz_demo_JNIDemo.h)
