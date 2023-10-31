cmake_minimum_required(VERSION 3.15)
project(Asteroids)

set(CMAKE_CXX_STANDARD 17)

get_filename_component(SPRITE_DIR "data/" ABSOLUTE BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
file(COPY ${SPRITE_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(start_asteroids src/main.cpp
        include/spaceship_keylistener.hpp
        include/spaceship_controller.hpp
        include/spaceship.hpp
        include/physics_handler.hpp
        include/sprite_generator.hpp
        include/bullet.hpp
)

target_link_libraries(start_asteroids PRIVATE threepp::threepp imgui::imgui)
