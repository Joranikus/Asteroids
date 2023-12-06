add_library(factories
            base_factory.cpp
            bullet_factory.cpp
            asteroid_factory.cpp)

target_include_directories(factories PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})