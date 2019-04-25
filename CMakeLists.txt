cmake_minimum_required(VERSION 3.10)
# based on https://cliutils.gitlab.io/modern-cmake/

project(cmake VERSION 0.1
        DESCRIPTION "Example project by Jens Klimke"
        LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 14)

add_library(one STATIC include/one/lib.h)

add_library(two STATIC include/two/lib.h)
target_include_directories(two PRIVATE include)
target_link_libraries(two PRIVATE one)

add_executable(${PROJECT_NAME} apps/main.cpp src/one.cpp src/two.cpp)
target_link_libraries(${PROJECT_NAME} two)