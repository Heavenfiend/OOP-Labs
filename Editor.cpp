//
// Created by Егор on 11/25/2025.
//
#include "Editor.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

// при создании редактора добавляем обсерверы
DungeonEditor::DungeonEditor() {
    observers.push_back(std::make_shared<ConsoleObserver>());
    observers.push_back(std::make_shared<FileObserver>());
}

// проверяем на координаты и имя и добавляем NPC в вектор
void DungeonEditor::add_npc(const std::string& type, const std::string& name, double x, double y) {
    if (x < 0 || x > 500 || y < 0 || y > 500) {
        throw std::invalid_argument("Координаты должны быть в диапазоне 0–500");
    }
    if (std::any_of(npcs.begin(), npcs.end(), [&](const auto& npc) { return npc->name == name; })) {
        throw std::invalid_argument("Имя должно быть уникальным");
    }

    std::unique_ptr<NPC> npc = nullptr;
    if (type == "Bear") {
        npc = std::make_unique<Bear>(name, x, y);
    } else if (type == "Elf") {
        npc = std::make_unique<Elf>(name, x, y);
    } else if (type == "Bandit") {
        npc = std::make_unique<Bandit>(name, x, y);
    } else {
        throw std::invalid_argument("Неизвестный тип NPC: " + type);
    }

    npcs.push_back(std::move(npc));
}

// выводим список NPC (только живых)
void DungeonEditor::print_npcs() const {
    for (const auto& npc : npcs) {
        if (npc->alive) {
            std::cout << npc->getTypeChar() << "(name='" << npc->name << "', x=" << npc->x << ", y=" << npc->y << ")\n";
        }
    }
}

// сохраняем NPC в файл
void DungeonEditor::save_to_file(const std::string& filename) {
    NPCFactory::save_to_file(npcs, filename);
}

// загружаем NPC из файла (добавляем к существующим)
void DungeonEditor::load_from_file(const std::string& filename) {
    auto loaded_npcs = NPCFactory::load_from_file(filename);
    for (auto& npc : loaded_npcs) {
        npcs.push_back(std::move(npc));
    }
}

// запускаем бой между NPC
void DungeonEditor::battle_mode(double max_distance) {
    BattleVisitor visitor(observers);
    visitor.fight(npcs, max_distance);
}