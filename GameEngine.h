#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Editor.h"
#include "CoroutineBattle.h"
#include "CoroutineScheduler.h"
#include <thread>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <sstream>

class GameEngine {
private:
    DungeonEditor editor;
    std::shared_mutex world_mtx;
    std::mutex cout_mtx;
    CoroutineScheduler scheduler;
    bool game_running = true;

    static constexpr int GAME_DURATION = 30;

public:
    void run();
    void print_map();
    void print_survivors();
};

#endif