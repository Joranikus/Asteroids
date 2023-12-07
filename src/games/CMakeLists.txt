
#inspirert fra Lars Ivar sitt "factory_pattern" eksempel
set(games_include_dir "${CMAKE_SOURCE_DIR}/include/games")

set(games_files
        "${games_include_dir}/game.hpp" "game.cpp"
)

add_library(games ${games_files})

target_link_libraries(games PUBLIC threepp::threepp)
target_link_libraries(games PUBLIC factories)
target_link_libraries(games PUBLIC collision_detectors)
target_link_libraries(games PUBLIC keylisteners)

target_include_directories(games PUBLIC ${games_include_dir})