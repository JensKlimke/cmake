include(AddGoogleTest)

add_executable(SimpleTest SimpleTest.cpp)
target_include_directories(SimpleTest PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(SimpleTest PRIVATE one two)

add_gtest(SimpleTest)

# Note: add_gtest is just a macro that adds gtest, gmock, and gtest_main, and then runs add_test to create a test with the same name:
# target_link_libraries(SimpleTest gtest gmock gtest_main)
# add_test(SimpleTest SimpleTest)