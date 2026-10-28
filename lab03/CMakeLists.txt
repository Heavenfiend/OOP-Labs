cmake_minimum_required(VERSION 3.10)
project(OOP3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Указываем, где искать заголовочные файлы
include_directories(include)

# Основная программа
add_executable(OOP3
        src/main.cpp
        src/figure.cpp
        src/pentagon.cpp
        src/hexagon.cpp
        src/octagon.cpp
)

target_include_directories(OOP3 PRIVATE include)

# Подключаем GoogleTest через FetchContent
include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        main  # или конкретный тег, например release-1.12.1
)

# Для Windows: предотвращаем переопределение настроек компилятора
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests
        tests/test_main.cpp
        src/figure.cpp
        src/pentagon.cpp
        src/hexagon.cpp
        src/octagon.cpp
)

target_include_directories(tests PRIVATE include)

target_link_libraries(tests gtest_main)

add_test(NAME UnitTests COMMAND tests)