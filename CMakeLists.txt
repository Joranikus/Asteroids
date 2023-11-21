cmake_minimum_required(VERSION 3.15)
project(Asteroids)

set(CMAKE_CXX_STANDARD 17)

# need to add these when i split the headers
#add_subdirectory(src)
#add_subdirectory(include/collision_detectors)
#add_subdirectory(include/factories)
#add_subdirectory(include/functions)
#add_subdirectory(include/keylisteners)

file(COPY ${CMAKE_SOURCE_DIR}/data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(start_asteroids src/main.cpp)

target_include_directories(start_asteroids PRIVATE ${CMAKE_SOURCE_DIR}/include)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
target_link_libraries(start_asteroids PRIVATE threepp::threepp imgui::imgui)