cmake_minimum_required(VERSION 3.20)
project(BattleDungeonCoro)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines")

add_executable(battle_dungeon
        main.cpp
        NPC.cpp
        Observer.cpp
        Factory.cpp
        Visitor.cpp
        Editor.cpp
        GameEngine.cpp
        CoroutineBattle.cpp
        CoroutineScheduler.cpp  # <-- добавлен
)

target_include_directories(battle_dungeon PRIVATE .)