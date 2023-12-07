
add_executable(Asteroids main.cpp)
target_include_directories(Asteroids PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(Asteroids PRIVATE threepp::threepp
                                        collision_detectors
                                        controllers
                                        factories
                                        functions)

add_subdirectory(collision_detectors)
add_subdirectory(controllers)
add_subdirectory(factories)
add_subdirectory(functions)
add_subdirectory(games)
add_subdirectory(keylisteners)