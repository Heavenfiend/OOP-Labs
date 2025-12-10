#include "NPC.h"
#include <sstream>
#include <cmath>

NPC::NPC(const std::string& name, char type, double x, double y, double move_dist, double kill_dist)
    : name(name), type(type), x(x), y(y), move_distance(move_dist), kill_distance(kill_dist) {}

double NPC::distance_to(const NPC& other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

void NPC::move_towards(double target_x, double target_y) {
    if (!alive) return;
    double dx = target_x - x;
    double dy = target_y - y;
    double dist = std::sqrt(dx * dx + dy * dy);
    if (dist > move_distance) {
        x += (dx / dist) * move_distance;
        y += (dy / dist) * move_distance;
    } else {
        x = target_x;
        y = target_y;
    }
    // Ограничение границами
    x = std::max(0.0, std::min(500.0, x));
    y = std::max(0.0, std::min(500.0, y));
}

// Реализация to_string
std::string NPC::to_string() const {
    std::ostringstream oss;
    oss << getTypeChar() << " " << name << " " << x << " " << y;
    return oss.str();
}

// Реализация from_string
std::unique_ptr<NPC> NPC::from_string(const std::string& line) {
    std::istringstream iss(line);
    std::string type_str, name;
    double x, y;

    iss >> type_str >> name >> x >> y;

    char type = type_str[0];

    if (type == 'B') {
        return std::make_unique<Bear>(name, x, y);
    }
    if (type == 'E') {
        return std::make_unique<Elf>(name, x, y);
    }
    if (type == 'R') {
        return std::make_unique<Bandit>(name, x, y);
    }
    return nullptr;
}

// Bear: 5 (ход), 10 (убийство)
Bear::Bear(const std::string& name, double x, double y) : NPC(name, 'B', x, y, 5.0, 10.0) {}
bool Bear::can_kill(const NPC& other) const { return other.type == 'E' && other.alive; }
char Bear::getTypeChar() const { return 'B'; }

// Elf: 10 (ход), 50 (убийство)
Elf::Elf(const std::string& name, double x, double y) : NPC(name, 'E', x, y, 10.0, 50.0) {}
bool Elf::can_kill(const NPC& other) const { return other.type == 'R' && other.alive; }
char Elf::getTypeChar() const { return 'E'; }

// Bandit: 10 (ход), 10 (убийство)
Bandit::Bandit(const std::string& name, double x, double y) : NPC(name, 'R', x, y, 10.0, 10.0) {}
bool Bandit::can_kill(const NPC& other) const { return (other.type == 'R' || other.type == 'E') && other.alive; }
char Bandit::getTypeChar() const { return 'R'; }