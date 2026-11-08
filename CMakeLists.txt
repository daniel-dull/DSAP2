cmake_minimum_required(VERSION 3.12)
project(DSAP2)

add_subdirectory(Catch2)

add_library(hash_table
        src/hash/hash.cpp
        src/hash/hash.h
)

add_library(trie
        src/trie/trie.cpp
        src/trie/trie.h
)

add_executable(hash_tests
        src/hash/hash_tests.cpp
)

target_link_libraries(hash_tests
        PRIVATE hash_table Catch2::Catch2WithMain
)

add_executable(dictionary_app
        src/main.cpp
)

target_link_libraries(dictionary_app
        PRIVATE hash_table trie
)
