cmake_minimum_required(VERSION 3.15)
project(Asteroids)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(start_asteroids src/main.cpp)
target_link_libraries(start_asteroids PRIVATE threepp::threepp imgui::imgui)
