cmake_minimum_required(VERSION 3.5)

project(Result LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

enable_testing()
find_package(GTest CONFIG REQUIRED)

add_executable(Result_tests
    tests/main.cpp
    tests/result_tests.cpp
    src/result.h)

set_target_properties(Result_tests PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(Result_tests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)