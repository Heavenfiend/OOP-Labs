//
// Created by Egor on 10 11 2025
//
#include "CoroutineBattle.h"
#include <iostream>

BattleTask fight_coro(NPC& attacker, NPC& defender, std::mutex& cout_mtx) {
    // инициализируем генератор случайных чисел
    static std::random_device rd;
    static std::mt19937 gen(rd());
    // бросаем кубики
    int attack = std::uniform_int_distribution<>(1, 6)(gen);
    int defense = std::uniform_int_distribution<>(1, 6)(gen);

    {
        // блок чтобы при выводе не было гонки
        std::lock_guard<std::mutex> lock(cout_mtx);
        std::cout << attacker.name << " attacks " << defender.name << " ("
                  << attack << " vs " << defense << ")... ";
    }
    // если атака больше защиты, то убиваем противника
    if (attack > defense) {
        {   // блок на изменение состояние нпс
            std::lock_guard<std::mutex> npc_lock(defender.mtx);
            defender.alive = false;
        }
        {   // блок на вывод против гонки
            std::lock_guard<std::mutex> lock(cout_mtx);
            std::cout << defender.name << " is killed!\n";
        }
        // иначе промах
    } else {
        std::lock_guard<std::mutex> lock(cout_mtx);
        std::cout << "miss!\n";
    }
    // завершаем корутину
    co_return;
}