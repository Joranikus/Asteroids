cmake_minimum_required(VERSION 3.15)
project(Asteroids)
set(CMAKE_CXX_STANDARD 17)

file(COPY ${CMAKE_SOURCE_DIR}/data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src/)

# adding dependencies
find_package(threepp CONFIG REQUIRED)

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)
enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
