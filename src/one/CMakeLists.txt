# set source files
set(SOURCE_FILES
        one.cpp)

# create target
add_library(one STATIC ${SOURCE_FILES})

# include directory
target_include_directories(one PRIVATE
        ${PROJECT_SOURCE_DIR}/src/one)
