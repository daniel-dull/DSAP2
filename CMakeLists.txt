cmake_minimum_required(VERSION 3.16)
project(DSAP2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(hash_table
        src/hash/hash.cpp
        src/hash/hash.h
)