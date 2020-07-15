# set source files
set(SOURCE_FILES
        three.cpp)

# create target
add_library(three SHARED ${SOURCE_FILES})
add_definitions(-DTHREELIB_EXPORTS)


