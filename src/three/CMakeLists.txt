# set source files
set(SOURCE_FILES
        three.cpp)

# create target
add_library(three SHARED ${SOURCE_FILES})
add_definitions(-DTHREELIB_EXPORTS)

# include directory
target_include_directories(three PRIVATE
        ${PROJECT_SOURCE_DIR}/include/three # headers for library
        ${PROJECT_SOURCE_DIR}/include)      # other libraries

