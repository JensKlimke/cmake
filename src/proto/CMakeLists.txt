# set source files
set(SOURCE_FILES
        PID_controller.cpp
        PID_controller.h
    )

# set proto files
set(PROTO_FILES
        Models.proto
    )

# generate proto files
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

# create target
add_library(proto STATIC
        ${SOURCE_FILES}
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        )

# link libraries
target_link_libraries(proto PUBLIC
        ${Protobuf_LIBRARIES}
)

# include directory
target_include_directories(proto PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        ${CMAKE_BINARY_DIR}/src
)