cmake_minimum_required(VERSION 3.25)
project(DSAP2)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare( #Fetches Catch2, so other fetches dont interfere with tests anymore
        Catch2
        URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.5.0.zip
)
FetchContent_MakeAvailable(Catch2)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

FetchContent_Declare( #Fetches SFML lib
        SFML
        URL https://github.com/SFML/SFML/archive/refs/tags/2.6.1.zip
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare( #Fetches ImGui lib
        imgui
        URL https://github.com/ocornut/imgui/archive/refs/tags/v1.90.zip
)
FetchContent_MakeAvailable(imgui)
set(IMGUI_DIR "${imgui_SOURCE_DIR}" CACHE PATH "ImGui directory" FORCE)    #locates the ImGui source files

FetchContent_Declare(   #Fetches ImGui integration with SFML
        ImGui-SFML
        URL https://github.com/eliasdaler/imgui-sfml/archive/refs/tags/v2.6.zip
)
set(IMGUI_SFML_FIND_SFML OFF) #stops ImGui from looking for SFML in the file since its also being fetched
FetchContent_MakeAvailable(ImGui-SFML)


add_executable(hash_tests
        src/hash/hash_tests.cpp
        src/hash/hash.cpp
)
target_link_libraries(hash_tests PRIVATE Catch2::Catch2WithMain)

add_executable(DSAP2_UI
        src/main.cpp
        src/hash/hash.cpp
        src/trie/trie.cpp
)

target_link_libraries(DSAP2_UI PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        ImGui-SFML::ImGui-SFML
)