IF (WIN32)
    cmake_minimum_required(VERSION 3.15)
    cmake_policy(SET CMP0091 NEW)
ELSE()
    cmake_minimum_required(VERSION 3.5)
ENDIF()

# set project title
project(DummyProject)

# set C++ standard
set(CMAKE_CXX_STANDARD 14)

# set options
option(BUILD_APPS "Build the executables of the project" ON)
option(BUILD_TESTS "Sets or unsets the option to generate the test target" OFF)
option(ENABLE_COVERAGE "Enable the coverage check of the module" OFF)

# add ./cmake to CMAKE_MODULE_PATH
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# update submodules
include(UpdateGitSubmodules)
set(GIT_SUBMODULE OFF)

# create and set binary directory
set(BIN_DIR ${PROJECT_SOURCE_DIR}/bin CACHE PATH "BIN_DIR")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})



# ------------------------------------------------------------------------------
# core sources
# ------------------------------------------------------------------------------

# add sources
add_subdirectory(src)



# ------------------------------------------------------------------------------
# Apps
# ------------------------------------------------------------------------------

# enable apps of the project
if(BUILD_APPS)

    # add subdirectory for apps
    add_subdirectory(apps)

endif(BUILD_APPS)



# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------

# enable google testing for project
if(BUILD_TESTS)

    message("-- Testing enabled")

    # enable testing
    enable_testing()

    # unset for all subprojects
    set(BUILD_TESTS OFF)

    # add gtest sources
    add_subdirectory(lib/gtest)

    # load macros for test
    include(AddGoogleTest)

    # add test folder
    add_subdirectory(test)

endif()



# ------------------------------------------------------------------------------
# Coverage
# ------------------------------------------------------------------------------

if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()
