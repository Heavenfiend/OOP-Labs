//
// Created by Егор on 11/25/2025.
//
#ifndef FACTORY_H
#define FACTORY_H

#include "NPC.h"
#include <vector>
#include <memory>
// реализуем паттерн Factory который будет создавать NPC
class NPCFactory {
public:
    static std::vector<std::unique_ptr<NPC>> load_from_file(const std::string& filename);
    static void save_to_file(const std::vector<std::unique_ptr<NPC>>& npcs, const std::string& filename);
};

#endif