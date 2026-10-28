#include "Editor.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

DungeonEditor::DungeonEditor() {
}
// метод добавления нового нпс
void DungeonEditor::add_npc(const std::string& type, const std::string& name, double x, double y) {
    if (x < 0 || x > 500 || y < 0 || y > 500) {
        throw std::invalid_argument("Координаты должны быть в диапазоне 0–500");
    }
    // проверка на уникальность имени
    if (std::any_of(npcs.begin(), npcs.end(), [&](const auto& npc) { return npc->name == name; })) {
        throw std::invalid_argument("Имя должно быть уникальным");
    }
    // создание нпс
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
    // добавление нпс в вектор
    npcs.push_back(std::move(npc));
}
// метод вывода всех нпс
void DungeonEditor::print_npcs() const {
    for (const auto& npc : npcs) {
        if (npc->alive) {
            std::cout << npc->getTypeChar() << "(name='" << npc->name << "', x=" << npc->x << ", y=" << npc->y << ")\n";
        }
    }
}