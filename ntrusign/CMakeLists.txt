cmake_minimum_required(VERSION 3.10)
project(ntrusign C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(build)
include_directories(build/classes)
include_directories(build/classes/ntrusign)

add_executable(ntrusign
        build/classes/ntrusign/ntru.h)
