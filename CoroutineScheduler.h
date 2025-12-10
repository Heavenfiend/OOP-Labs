//
// Created by Егор on 12/10/2025.
//

#ifndef COROUTINESCHEDULER_H
#define COROUTINESCHEDULER_H

#include <queue>
#include <coroutine>
#include <thread>
#include <mutex>

class CoroutineScheduler {
private:
    std::queue<std::coroutine_handle<>> tasks;
    std::mutex mtx;
    bool running = true;

public:
    void submit(std::coroutine_handle<> h);
    void run();
    void stop();
};

#endif