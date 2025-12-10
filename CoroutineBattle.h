#ifndef COROUTINEBATTLE_H
#define COROUTINEBATTLE_H

#include "NPC.h"
#include <coroutine>
#include <random>
#include <mutex>

struct BattleTask {
    struct promise_type {
        BattleTask get_return_object() { return {std::coroutine_handle<promise_type>::from_promise(*this)}; }
        std::suspend_always initial_suspend() { return {}; }  // <-- изменено
        std::suspend_always final_suspend() noexcept { return {}; }  // <-- изменено
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };

    std::coroutine_handle<promise_type> handle;

    bool await_ready() const noexcept { return false; }
    void await_suspend(std::coroutine_handle<>) const noexcept {}
    void await_resume() const noexcept {}
};

BattleTask fight_coro(NPC& attacker, NPC& defender, std::mutex& cout_mtx);

#endif