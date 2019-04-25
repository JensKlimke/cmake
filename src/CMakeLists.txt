add_library(one STATIC ${CMAKE_SOURCE_DIR}/include/one/lib.h one.cpp)
target_include_directories(one PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_library(two STATIC ${CMAKE_SOURCE_DIR}/include/two/lib.h two.cpp)
target_include_directories(two PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(two PRIVATE one)