# set source files
set(SOURCE_FILES
        ModelProtoTest.cpp
    )

# create target
add_executable(ModelProtoTest
        ${SOURCE_FILES}
    )


# link library
target_link_libraries(ModelProtoTest PRIVATE
        proto
        )

# include directory
target_include_directories(ModelProtoTest PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        )

# add test
add_gtest(ModelProtoTest)