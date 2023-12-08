
#inspirert fra Lars Ivar sitt "factory_pattern" eksempel
set(collision_detectors_include_dir "${CMAKE_SOURCE_DIR}/include/collision_detectors")

set(collision_detectors_files
        "${collision_detectors_include_dir}/asteroid_bullet_collision_detector.hpp" "asteroid_bullet_collision_detector.cpp"
        "${collision_detectors_include_dir}/base_collision_detector.hpp" "base_collision_detector.cpp"
        "${collision_detectors_include_dir}/asteroid_collision_detector.hpp" "asteroid_collision_detector.cpp"
)

add_library(collision_detectors ${collision_detectors_files})

target_link_libraries(collision_detectors PUBLIC threepp::threepp)
target_include_directories(collision_detectors PUBLIC ${collision_detectors_include_dir})