//
// Created by Егор on 11/25/2025.
//
#include "Factory.h"
#include <fstream>
#include <string>

std::vector<std::unique_ptr<NPC>> NPCFactory::load_from_file(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::unique_ptr<NPC>> npcs;
    std::string line;
    while (std::getline(file, line)) {
        auto npc = NPC::from_string(line);
        if (npc) npcs.push_back(std::move(npc));
    }
    return npcs;
}

void NPCFactory::save_to_file(const std::vector<std::unique_ptr<NPC>>& npcs, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& npc : npcs) {
        file << npc->to_string() << '\n';
    }
}