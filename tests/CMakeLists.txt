add_executable(tests base_controller_tests.cpp)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain threepp::threepp)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

include(Catch)
catch_discover_tests(tests)
