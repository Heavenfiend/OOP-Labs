//
// Created by Егор on 11/25/2025.
//
#ifndef VISITOR_H
#define VISITOR_H

#include "NPC.h"
#include "Observer.h"
#include <vector>
#include <memory>
// объявление паттерна Visitor для боя
class BattleVisitor {
private:
    std::vector<std::shared_ptr<Observer>> observers;

public:
    BattleVisitor(const std::vector<std::shared_ptr<Observer>>& obs);
    void fight(std::vector<std::unique_ptr<NPC>>& npcs, double max_distance);
};

#endif