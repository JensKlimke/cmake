# set source files
set(SOURCE_FILES
        main.cpp
        )

# set proto files
set(PROTO_FILES
        ../../src/proto/Models.proto
        )

# generate proto files
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
PROTOBUF_GENERATE_GRPC_CPP(PROTO_GRPC_SRCS PROTO_GRPC_HDRS ${PROTO_FILES})

# create target
add_executable(client
        ${SOURCE_FILES}
        ${PROTO_SRCS}
        ${PROTO_GRPC_SRCS}
        )

# link protobuf
target_link_libraries(client PRIVATE
        ${Protobuf_LIBRARIES}
        ${gRPC_LIBRARIES}
        )

# include directory
target_include_directories(client PRIVATE
        ../../lib/cxxopts/include      # cxxopts
        ${CMAKE_BINARY_DIR}/apps
        )
