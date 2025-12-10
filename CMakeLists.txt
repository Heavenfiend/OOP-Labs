cmake_minimum_required(VERSION 3.20)
project(BattleDungeonCoro)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(battle_dungeon
        main.cpp
        NPC.cpp
        Editor.cpp
        GameEngine.cpp
        CoroutineBattle.cpp
        CoroutineScheduler.cpp
)

target_compile_options(battle_dungeon PRIVATE -fcoroutines)

target_include_directories(battle_dungeon PRIVATE .)