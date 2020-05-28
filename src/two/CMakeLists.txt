# set source files
set(SOURCE_FILES
        two.cpp)

# create target
add_library(two STATIC ${SOURCE_FILES})

# include directory
target_include_directories(two PRIVATE
        ${PROJECT_SOURCE_DIR}/src/two # headers for library
        ${PROJECT_SOURCE_DIR}/src)    # other libraries

# link library to target
target_link_libraries(two PRIVATE one)
