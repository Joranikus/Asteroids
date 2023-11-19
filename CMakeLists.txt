cmake_minimum_required(VERSION 3.15)
project(Asteroids)

set(CMAKE_CXX_STANDARD 17)

set(SPRITE_DIR "${CMAKE_SOURCE_DIR}/data/")
file(COPY ${SPRITE_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(start_asteroids src/main.cpp
        include/spaceship_keylistener.hpp
        include/controllers/spaceship_controller.hpp
        include/controllers/base_controller.hpp
        include/functions/create_sprite.hpp
        include/controllers/asteroid_controller.hpp
        include/functions/random_functions.hpp
        include/factories/asteroid_factory.hpp
        include/factories/base_factory.hpp
        include/factories/bullet_factory.hpp
        include/collision_detectors/base_collision_detector.hpp
        include/collision_detectors/asteroid_bullet_collision_detector.hpp
)

target_include_directories(start_asteroids PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(start_asteroids PRIVATE threepp::threepp imgui::imgui)