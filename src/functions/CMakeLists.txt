
#inspirert fra Lars Ivar sitt "factory_pattern" eksempel
set(functions_include_dir "${CMAKE_SOURCE_DIR}/include/functions")

set(functions_files
        "${functions_include_dir}/random_functions.hpp" "random_functions.cpp"
        "${functions_include_dir}/create_sprite.hpp" "create_sprite.cpp"
)

add_library(functions ${functions_files})

target_link_libraries(functions PUBLIC threepp::threepp)
target_include_directories(functions PUBLIC ${functions_include_dir})