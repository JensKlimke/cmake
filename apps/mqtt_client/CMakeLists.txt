# set source files
set(SOURCE_FILES
        main.cpp)

# create target
add_executable(mqtt_client ${SOURCE_FILES})

# include directory
target_include_directories(mqtt_client PRIVATE
        ../../lib/cxxopts/include      # cxxopts
        ${PROJECT_SOURCE_DIR}/include  # other libraries
        )

target_link_libraries(mqtt_client PRIVATE
        paho-mqtt3c
)
