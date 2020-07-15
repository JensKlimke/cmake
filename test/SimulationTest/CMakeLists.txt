# set source files
set(SOURCE_FILES
        ModelTest.cpp)

# create target
add_executable(SimulationTest ${SOURCE_FILES})

# include directory
target_include_directories(SimulationTest PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        )

# link library to target
target_link_libraries(SimulationTest PRIVATE
        simulation)

# add test
add_gtest(SimulationTest)