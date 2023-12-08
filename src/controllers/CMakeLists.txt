
#inspirert fra Lars Ivar sitt "factory_pattern" eksempel
set(controllers_include_dir "${CMAKE_SOURCE_DIR}/include/controllers")

set(controller_files
        "${controllers_include_dir}/base_controller.hpp" "base_controller.cpp"
        "${controllers_include_dir}/spaceship_controller.hpp" "spaceship_controller.cpp"
        "${controllers_include_dir}/asteroid_controller.hpp" "asteroid_controller.cpp"
        "${controllers_include_dir}/bullet_controller.hpp" "bullet_controller.cpp"
        "${controllers_include_dir}/particle_controller.hpp" "particle_controller.cpp"
)

add_library(controllers ${controller_files})

target_link_libraries(controllers PUBLIC threepp::threepp)
target_include_directories(controllers PUBLIC ${controllers_include_dir})