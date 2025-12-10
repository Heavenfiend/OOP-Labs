//
// Created by Egor on 10 11 2025
//
#include "NPC.h"
#include <cmath>
// сохраняет имя, тип, координаты, расстояние перемещения и расстояние убийства
NPC::NPC(const std::string& name, char type, double x, double y, double move_dist, double kill_dist)
    : name(name), type(type), x(x), y(y), move_distance(move_dist), kill_distance(kill_dist) {}

// вычисляет расстояние между двумя NPC
double NPC::distance_to(const NPC& other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}
// перемещает NPC в направлении цели
void NPC::move_towards(double target_x, double target_y) {
    if (!alive) return;
    double dx = target_x - x;
    double dy = target_y - y;
    double dist = std::sqrt(dx * dx + dy * dy);
    // если расстояние больше максимального, перемещаемся на максимальное
    if (dist > move_distance) {
        x += (dx / dist) * move_distance;
        y += (dy / dist) * move_distance;
    } else {
        // иначе перемещаемся к цели
        x = target_x;
        y = target_y;
    }
    // наши максимальные координаты 500.0
    x = std::max(0.0, std::min(500.0, x));
    y = std::max(0.0, std::min(500.0, y));
}
// медведь дальность перемещения 5.0, дальность убийства 10.0
Bear::Bear(const std::string& name, double x, double y) : NPC(name, 'B', x, y, 5.0, 10.0) {}
bool Bear::can_kill(const NPC& other) const { return other.type == 'E' && other.alive; }
char Bear::getTypeChar() const { return 'B'; }
// эльф дальность перемещения 10.0, дальность убийства 50.0
Elf::Elf(const std::string& name, double x, double y) : NPC(name, 'E', x, y, 10.0, 50.0) {}
bool Elf::can_kill(const NPC& other) const { return other.type == 'R' && other.alive; }
char Elf::getTypeChar() const { return 'E'; }
// разбойник дальность перемещения 10.0, дальность убийства 10.0
Bandit::Bandit(const std::string& name, double x, double y) : NPC(name, 'R', x, y, 10.0, 10.0) {}
bool Bandit::can_kill(const NPC& other) const { return (other.type == 'R' || other.type == 'E') && other.alive; }
char Bandit::getTypeChar() const { return 'R'; }