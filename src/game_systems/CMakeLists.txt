
#inspirert fra Lars Ivar sitt "factory_pattern" eksempel
set(game_systems_include_dir "${CMAKE_SOURCE_DIR}/include/game_systems")

set(game_systems_files
        "${game_systems_include_dir}/game.hpp" "game.cpp"
        "${game_systems_include_dir}/HUD.hpp" "HUD.cpp"
)

add_library(game_systems ${game_systems_files})

target_link_libraries(game_systems PUBLIC threepp::threepp)
target_link_libraries(game_systems PUBLIC factories)
target_link_libraries(game_systems PUBLIC collision_detectors)
target_link_libraries(game_systems PUBLIC keylisteners)

target_include_directories(game_systems PUBLIC ${game_systems_include_dir})