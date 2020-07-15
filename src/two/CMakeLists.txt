# set source files
set(SOURCE_FILES
        two.cpp)

# create target
add_library(two STATIC ${SOURCE_FILES})

# link library to target
target_link_libraries(two PRIVATE one)
