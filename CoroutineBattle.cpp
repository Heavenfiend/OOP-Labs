#include "CoroutineBattle.h"
#include <iostream>

BattleTask fight_coro(NPC& attacker, NPC& defender, std::mutex& cout_mtx) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    int attack = std::uniform_int_distribution<>(1, 6)(gen);
    int defense = std::uniform_int_distribution<>(1, 6)(gen);

    {
        std::lock_guard<std::mutex> lock(cout_mtx);
        std::cout << attacker.name << " attacks " << defender.name << " ("
                  << attack << " vs " << defense << ")... ";
    }

    if (attack > defense) {
        {
            std::lock_guard<std::mutex> npc_lock(defender.mtx);
            defender.alive = false;
        }
        {
            std::lock_guard<std::mutex> lock(cout_mtx);
            std::cout << defender.name << " is killed!\n";
        }
    } else {
        std::lock_guard<std::mutex> lock(cout_mtx);
        std::cout << "miss!\n";
    }

    co_return;
}