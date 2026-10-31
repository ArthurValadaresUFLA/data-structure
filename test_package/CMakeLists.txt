cmake_minimum_required(VERSION 3.23)

project(data-structure-tests CXX)

find_package(data-structure CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
     ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)

add_executable(unit_tests ${TEST_SOURCES})

target_link_libraries(unit_tests PRIVATE data-structure::data-structure
                                         Catch2::Catch2WithMain)

enable_testing()
include(Catch)
catch_discover_tests(unit_tests)
