
#inspirert fra Lars Ivar sitt "factory_pattern" eksempel
set(factories_include_dir "${CMAKE_SOURCE_DIR}/include/factories")

set(factories_files
        "${factories_include_dir}/base_factory.hpp" "base_factory.cpp"
        "${factories_include_dir}/bullet_factory.hpp" "bullet_factory.cpp"
        "${factories_include_dir}/asteroid_factory.hpp" "asteroid_factory.cpp"
        "${factories_include_dir}/particle_factory.hpp" "particle_factory.cpp"
)

add_library(factories ${factories_files})

target_link_libraries(factories PUBLIC threepp::threepp)
target_link_libraries(factories PRIVATE controllers)

target_include_directories(factories PUBLIC ${factories_include_dir})