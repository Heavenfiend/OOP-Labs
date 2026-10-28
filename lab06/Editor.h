//
// Created by Егор on 11/25/2025.
//
#ifndef EDITOR_H
#define EDITOR_H

#include "NPC.h"
#include "Observer.h"
#include "Factory.h"
#include "Visitor.h"
#include <vector>
#include <memory>
// хранит NPC и Observer
class DungeonEditor {
private:
    std::vector<std::unique_ptr<NPC>> npcs;
    std::vector<std::shared_ptr<Observer>> observers;

public:
    DungeonEditor();
    void add_npc(const std::string& type, const std::string& name, double x, double y);
    void print_npcs() const;
    void save_to_file(const std::string& filename);
    void load_from_file(const std::string& filename);
    void battle_mode(double max_distance);
};

#endif