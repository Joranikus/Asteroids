add_library(collision_detectors
            base_collision_detector.cpp
            asteroid_bullet_collision_detector.cpp)

target_include_directories(collision_detectors PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})