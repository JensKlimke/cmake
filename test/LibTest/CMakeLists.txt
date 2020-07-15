# set source files
set(SOURCE_FILES
        LibTest.cpp)

# create target
add_executable(LibTest ${SOURCE_FILES})

# include directory
target_include_directories(LibTest PRIVATE
        ${PROJECT_SOURCE_DIR}/include)

# link library to target
target_link_libraries(LibTest PRIVATE
        two
        three
    )

# add test
add_gtest(LibTest)