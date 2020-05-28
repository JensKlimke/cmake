# set source files
set(SOURCE_FILES
        proto.h)

# set proto files
set(PROTO_FIULES
        example.proto)

# generate proto files
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FIULES})

# create target
add_library(proto STATIC
        ${SOURCE_FILES}
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        )

target_link_libraries(proto PRIVATE
        ${Protobuf_LIBRARIES}
)

# include directory
target_include_directories(proto PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        ${CMAKE_BINARY_DIR}/src/proto
)