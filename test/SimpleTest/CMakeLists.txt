# set source files
set(SOURCE_FILES
        SimpleTest.cpp)

# create target
add_executable(SimpleTest ${SOURCE_FILES})

# include directory
target_include_directories(SimpleTest PRIVATE
        ${PROJECT_SOURCE_DIR}/src)

# link librarym to target
target_link_libraries(SimpleTest PRIVATE two three)

# add test
add_gtest(SimpleTest)