
add_executable(tests base_controller_tests.cpp)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tests PRIVATE threepp::threepp)
target_link_libraries(tests PRIVATE controllers)

include(Catch)
catch_discover_tests(tests)
