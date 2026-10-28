cmake_minimum_required(VERSION 3.10)
project(GeometricFigures)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
        main.cpp
)

set(HEADERS
        Point.h
        Figure.h
        Figures.h
        Array.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})