# set proto files
set(PROTO_FILES simulation.proto)

# generate proto files
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
message("-- protobuf generated headers: " ${PROTO_HDRS})

# create target
add_library(simulation STATIC
        ${SOURCE_FILES}
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        )

# add libraries
target_link_libraries(simulation PRIVATE
        ${Protobuf_LIBRARIES}
)

# include directory
target_include_directories(simulation PUBLIC
        ${CMAKE_BINARY_DIR}/src/simulation    # protobuf generated content
)