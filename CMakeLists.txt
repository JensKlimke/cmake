cmake_minimum_required(VERSION 3.5)

# set project title
project(DummyProject VERSION 0.0.1)

# set C++ standard
set(CMAKE_CXX_STANDARD 14)

# set options
option(DUMMY_BUILD_APPS "Builds the executables of the project" ON)
option(DUMMY_BUILD_TESTS "Sets or unsets the option to generate the test target" OFF)
option(DUMMY_ENABLE_COVERAGE "Enables the coverage check of the module" OFF)
option(DUMMY_CREATE_DOXYGEN_TARGET "Enable to create a doxygen target" OFF)

# add ./cmake to CMAKE_MODULE_PATH
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})


# ------------------------------------------------------------------------------
# DOCUMENTATION
# ------------------------------------------------------------------------------
if(DUMMY_CREATE_DOXYGEN_TARGET)

    # exclude pattern
    set(DOCYGEN_EXCLUDE_PATTERN "")

    # load module for doxygen target
    include(ModuleDoxygen)

endif(DUMMY_CREATE_DOXYGEN_TARGET)



# ------------------------------------------------------------------------------
# COVERAGE
# ------------------------------------------------------------------------------
if (BUILD_FOR_COVERAGE)

    # load module for coverage
    include(ModuleCoverage)

endif (BUILD_FOR_COVERAGE)



# ------------------------------------------------------------------------------
# PROTOBUF
# ------------------------------------------------------------------------------
include(ModuleProtobuf)



# ------------------------------------------------------------------------------
# CORE SOURCES
# ------------------------------------------------------------------------------

# add source folder
add_subdirectory(src)



# ------------------------------------------------------------------------------
# APPS
# ------------------------------------------------------------------------------
if(DUMMY_BUILD_APPS)

    # add subdirectory for apps
    add_subdirectory(apps)

endif(DUMMY_BUILD_APPS)



# ------------------------------------------------------------------------------
# TESTING
# ------------------------------------------------------------------------------
if(DUMMY_BUILD_TESTS)

    # load module for testing
    include(ModuleGtest)

endif(DUMMY_BUILD_TESTS)