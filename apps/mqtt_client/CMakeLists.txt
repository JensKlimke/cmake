# set source files
set(SOURCE_FILES
        main.cpp)

# create target
add_executable(mqtt_client ${SOURCE_FILES})


# include directory
target_include_directories(mqtt_client PRIVATE
        ${PROJECT_SOURCE_DIR}/lib/cxxopts/include # cxxopts
        ${PAHO_MQTTPP3_INCLUDE_DIR}               # paho mqtt client
        ${PROJECT_SOURCE_DIR}/include             # other libraries
        )

# link libraries
target_link_libraries(mqtt_client PRIVATE
        paho-mqttpp3
        )