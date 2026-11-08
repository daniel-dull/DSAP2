cmake_minimum_required(VERSION 3.16)
project(DSAP2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(hash_table
        src/hash/hash.cpp
        src/hash/hash.h
        src/main.cpp
        src/main.cpp
)

add_library(trie
        src/trie/trie.cpp
        src/trie/trie.h
        src/main.cpp
)

include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.7.1
        GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(Catch2)

add_executable(hash_tests
        src/hash/hash_tests.cpp
        src/main.cpp
)

target_link_libraries(hash_tests
        PRIVATE hash_table Catch2::Catch2WithMain
)

enable_testing()
list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/extras")
include(Catch)
catch_discover_tests(hash_tests)

add_executable(dictionary_app src/main.cpp)
target_link_libraries(dictionary_app PRIVATE hash_table trie)