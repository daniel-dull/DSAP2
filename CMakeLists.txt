cmake_minimum_required(VERSION 3.12)
project(DSAP2)

find_package(Catch2 3 REQUIRED)

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
add_executable(trie_tests
		src/trie/trietests.cpp
)

target_link_libraries(hash_tests
        PRIVATE hash_table Catch2::Catch2WithMain
)

target_link_libraries(trie_tests
        PRIVATE trie Catch2::Catch2WithMain
)

add_executable(dictionary_app
        src/main.cpp
)

target_link_libraries(dictionary_app
        PRIVATE hash_table trie
)
