# set source files
set(SOURCE_FILES
        ProtoTest.cpp)

# create target
add_executable(ProtoTest ${SOURCE_FILES})

# include directory
target_include_directories(ProtoTest PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        ${CMAKE_BINARY_DIR}/src/proto
        )

# link library to target
target_link_libraries(ProtoTest PRIVATE proto)

# add test
add_gtest(ProtoTest)