# set source files
set(SOURCE_FILES
        SimpleTest.cpp)

# create target
add_executable(SimpleTest ${SOURCE_FILES})

# include directory
target_include_directories(SimpleTest PRIVATE
        ${PROJECT_SOURCE_DIR}/include/two # headers for library
        ${PROJECT_SOURCE_DIR}/include)    # other libraries

# link librarym to target
target_link_libraries(SimpleTest PRIVATE two)

# set runtime library
set_property(TARGET SimpleTest PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

# add test
add_gtest(SimpleTest)

# Note: add_gtest is just a macro that adds gtest, gmock, and gtest_main, and then runs add_test to create a test with the same name:
# target_link_libraries(SimpleTest gtest gmock gtest_main)
# add_test(SimpleTest SimpleTest)