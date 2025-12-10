#include "CoroutineScheduler.h"
#include <iostream>

void CoroutineScheduler::submit(std::coroutine_handle<> h) {
    std::lock_guard<std::mutex> lock(mtx);
    tasks.push(h);
}

void CoroutineScheduler::run() {
    while (running || !tasks.empty()) {
        std::coroutine_handle<> h = nullptr;
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (!tasks.empty()) {
                h = tasks.front();
                tasks.pop();
            }
        }

        if (h) {
            h.resume();
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
}

void CoroutineScheduler::stop() {
    running = false;
}