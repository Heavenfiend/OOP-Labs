//
// Created by Egor on 10 11 2025
//
#include "CoroutineScheduler.h"
#include <iostream>
// кладем корутину в очередь
void CoroutineScheduler::submit(std::coroutine_handle<> h) {
    std::lock_guard<std::mutex> lock(mtx);
    tasks.push(h);
}
// достаем задачу из очереди и выполняем ее
void CoroutineScheduler::run() {
    while (running || !tasks.empty()) {
        std::coroutine_handle<> h = nullptr;
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (!tasks.empty()) {
                h = tasks.front(); // достаем задачу из очереди
                tasks.pop(); // удаляем ее из очереди
            }
        }

        if (h) {
            h.resume(); // выполняем задачу
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
}
// останавливаем работу
void CoroutineScheduler::stop() {
    running = false;
}