cmake_minimum_required(VERSION 3.15)
project(Asteroids)

set(CMAKE_CXX_STANDARD 17)

get_filename_component(SPRITE_DIR "data/" ABSOLUTE BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
file(COPY ${SPRITE_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(start_asteroids src/main.cpp)
target_link_libraries(start_asteroids PRIVATE threepp::threepp imgui::imgui)
