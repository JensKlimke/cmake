# set source files
set(SOURCE_FILES
        SimpleThreadTest.cpp)

# create target
add_executable(ThreadTest ${SOURCE_FILES})

# add test
add_gtest(ThreadTest)