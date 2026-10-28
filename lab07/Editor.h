//
// Created by Egor on 10 11 2025
//
#ifndef EDITOR_H
#define EDITOR_H

#include "NPC.h"
#include <vector>
#include <memory>

class DungeonEditor {
private:
    std::vector<std::unique_ptr<NPC>> npcs;

public:
    DungeonEditor();
    void add_npc(const std::string& type, const std::string& name, double x, double y);
    void print_npcs() const;
    std::vector<std::unique_ptr<NPC>>& get_npcs() { return npcs; }
};

#endif