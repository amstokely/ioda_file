cmake_minimum_required(VERSION 3.10)

enable_testing()
include(FetchContent)

project(ioda-file LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

FETCHCONTENT_DECLARE(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FETCHCONTENT_MAKEAVAILABLE(googletest)
FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG 0.8.0
)
FetchContent_MakeAvailable(yaml-cpp)

list( APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include("add_cpp_test")

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory("${CMAKE_SOURCE_DIR}/src")
add_subdirectory("${CMAKE_SOURCE_DIR}/config")
