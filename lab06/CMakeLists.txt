cmake_minimum_required(VERSION 3.10)

# Название проекта
project(BalagurFate3Editor)

# Установка C++17 стандарта
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Список исходных файлов
set(SOURCES
        main.cpp
        NPC.cpp
        Observer.cpp
        Factory.cpp
        Visitor.cpp
        Editor.cpp
)

set(HEADERS
        NPC.h
        Observer.h
        Factory.h
        Visitor.h
        Editor.h
)

# Создание исполняемого файла
add_executable(editor ${SOURCES} ${HEADERS})

# Опционально: указать флаги компилятора
target_compile_options(editor PRIVATE -Wall -Wextra)