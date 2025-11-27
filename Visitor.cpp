//
// Created by Егор on 11/25/2025.
//
#include "Visitor.h"
#include <algorithm>
// сохранение наблюдателей
BattleVisitor::BattleVisitor(const std::vector<std::shared_ptr<Observer>>& obs) : observers(obs) {}
// бой между NPC
void BattleVisitor::fight(std::vector<std::unique_ptr<NPC>>& npcs, double max_distance) {
    bool changed = true;
    while (changed) {
        changed = false;
        for (auto it1 = npcs.begin(); it1 != npcs.end(); ++it1) {
            for (auto it2 = npcs.begin(); it2 != npcs.end(); ) {
                if (it1 == it2) {
                    ++it2;
                    continue;
                }
                // проверка на расстояние и возможность атаки
                if ((*it1)->distance_to(**it2) <= max_distance) {
                    if ((*it1)->can_kill(**it2)) {
                        for (auto& obs : observers) {
                            obs->notify(**it1, **it2);
                        }
                        it2 = npcs.erase(it2);
                        changed = true;
                        continue;
                        // если не убил, то проверяем, может ли он убить другого
                    } else if ((*it2)->can_kill(**it1)) {
                        for (auto& obs : observers) {
                            obs->notify(**it2, **it1);
                        }
                        // удаляем убитого
                        it1 = npcs.erase(it1);
                        if (it1 == npcs.end()) break;
                        changed = true;
                        break;
                    }
                }
                ++it2;
            }
            if (it1 == npcs.end()) break;
        }
    }
}