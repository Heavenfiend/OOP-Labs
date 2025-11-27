//
// Created by Егор on 11/25/2025.
//
#include "NPC.h"
#include <sstream>
#include <cmath>
// рассчитывает евклидово расстояние между двумя NPC
NPC::NPC(const std::string& name, double x, double y) : name(name), x(x), y(y) {}

double NPC::distance_to(const NPC& other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}
// преобразует NPC в строку для записи в файл
std::string NPC::to_string() const {
    std::ostringstream oss;
    oss << type() << " " << name << " " << x << " " << y;
    return oss.str();
}
// создает NPC из строки и в зависимости от типа создает соответствующий класс
std::unique_ptr<NPC> NPC::from_string(const std::string& line) {
    std::istringstream iss(line);
    std::string type, name;
    double x, y;

    iss >> type >> name >> x >> y;

    if (type == "Bear") {
        return std::make_unique<Bear>(name, x, y);
    }
    if (type == "Elf") {
        return std::make_unique<Elf>(name, x, y);
    }
    if (type == "Bandit") {
        return std::make_unique<Bandit>(name, x, y);
    }
    return nullptr;
}

// реализуем классы наследников
Bear::Bear(const std::string& name, double x, double y) : NPC(name, x, y) {}
bool Bear::can_kill(const NPC& other) const { return other.type() == "Elf"; }
std::string Bear::type() const { return "Bear"; }

Elf::Elf(const std::string& name, double x, double y) : NPC(name, x, y) {}
bool Elf::can_kill(const NPC& other) const { return other.type() == "Bandit"; }
std::string Elf::type() const { return "Elf"; }

Bandit::Bandit(const std::string& name, double x, double y) : NPC(name, x, y) {}
bool Bandit::can_kill(const NPC& other) const { return other.type() == "Bandit" || other.type() == "Elf"; }
std::string Bandit::type() const { return "Bandit"; }