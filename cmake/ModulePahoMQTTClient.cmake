# searching for include directory
find_path(PAHO_MQTT3C_INCLUDE_DIR MQTTClient.h)
set(PAHO_MQTTPP3_INCLUDE_DIR ${PAHO_MQTT3C_INCLUDE_DIR})

# searching for library file
find_library(PAHO_MQTT3C_LIBRARY paho-mqtt3c-static)
find_library(PAHO_MQTTPP3_LIBRARY paho-mqttpp3)

if (PAHO_MQTT3C_INCLUDE_DIR AND PAHO_MQTT3C_LIBRARY)

    # you may need that if further action in your CMakeLists.txt depends
    # on detecting your library
    set(PAHO_MQTT3C_FOUND TRUE)

    # you may need that if you want to conditionally compile some parts
    # of your code depending on library availability
    add_definitions(-DHAVE_PAHO_MQTT3C=1)

endif ()

message(${PAHO_MQTT3C_INCLUDE_DIR})
message(${PAHO_MQTT3C_LIBRARY})
message(${PAHO_MQTTPP3_INCLUDE_DIR})
message(${PAHO_MQTTPP3_LIBRARY})