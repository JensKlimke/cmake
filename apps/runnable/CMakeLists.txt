# set source files
set(SOURCE_FILES
        main.cpp)

# create target
add_executable(runnable ${SOURCE_FILES})

# include directory
target_include_directories(runnable PRIVATE
        ../../lib/cxxopts/include      # cxxopts
        )

# link library to target
target_link_libraries(runnable PRIVATE two)
