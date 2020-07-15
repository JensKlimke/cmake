# set source files
set(SOURCE_FILES
        BasicProtoTest.cpp)

# generate proto files
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS Example.proto)

# create target
add_executable(ProtoTest
        ${SOURCE_FILES}
        ${PROTO_SRCS}
        ${PROTO_HDRS}
    )


# include directory
target_include_directories(ProtoTest PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        ${CMAKE_BINARY_DIR}/src/proto
    )

# link library to target
target_link_libraries(ProtoTest PRIVATE
        ${Protobuf_LIBRARIES}
    )

target_include_directories(ProtoTest PRIVATE
        ${CMAKE_BINARY_DIR}/test
    )

# add test
add_gtest(ProtoTest)