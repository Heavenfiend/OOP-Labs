cmake_minimum_required(VERSION 3.20)
project(five)

set(CMAKE_CXX_STANDARD 17)

add_executable(five
        src/main.cpp
        src/Five.cpp
)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(five_tests
        src/five_test.cpp
        src/Five.cpp
)

target_link_libraries(five_tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(five_tests)