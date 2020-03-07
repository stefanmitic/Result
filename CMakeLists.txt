cmake_minimum_required(VERSION 3.5)

project(Result LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define targets with source files
add_library(Result STATIC
  src/result.h
)
set_target_properties(Result PROPERTIES LINKER_LANGUAGE CXX)
target_compile_definitions(Result PRIVATE RESULT_LIBRARY)

add_executable(Result_tests
    tests/main.cpp
    tests/result_tests.cpp)

# Download and build external projects
include(ExternalProject)
ExternalProject_Add(project_googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.10.0
    SOURCE_DIR "${CMAKE_SOURCE_DIR}/libs/googletest"
    BINARY_DIR "${CMAKE_BINARY_DIR}/libs/googletest"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND cmake ${CMAKE_SOURCE_DIR}/libs/googletest COMMAND make -j
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)

# Add dependencies for Result_tests
# Result
add_dependencies(Result_tests Result)

# googletest
add_library(googletest STATIC IMPORTED)
set_property(TARGET googletest PROPERTY IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/libs/googletest/lib/libgtest.a)
add_dependencies(googletest project_googletest)
add_library(googletest_main STATIC IMPORTED)
set_property(TARGET googletest_main PROPERTY IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/libs/googletest/lib/libgtest_main.a)
add_dependencies(googletest_main project_googletest)
add_library(googlemock STATIC IMPORTED)
set_property(TARGET googlemock PROPERTY IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/libs/googletest/lib/libgmock.a)
add_dependencies(googlemock project_googletest)
add_library(googlemock_main STATIC IMPORTED)
set_property(TARGET googlemock_main PROPERTY IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/libs/googletest/lib/libgmock_main.a)
add_dependencies(googlemock_main project_googletest)

target_link_libraries(Result_tests PRIVATE Result googletest googletest_main googlemock googlemock_main pthread)
target_include_directories(Result_tests PRIVATE ${CMAKE_SOURCE_DIR}/libs/googletest/googletest/include ${CMAKE_SOURCE_DIR}/libs/googletest/googlemock/include)
