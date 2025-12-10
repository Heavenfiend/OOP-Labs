#ifndef NPC_H
#define NPC_H

#include <string>
#include <memory>
#include <mutex>

class NPC {
public:
    std::string name;
    char type; // 'B', 'E', 'R'
    double x, y;
    bool alive = true;
    mutable std::mutex mtx;

    // Новые поля для дистанций
    double move_distance;
    double kill_distance;

    NPC(const std::string& name, char type, double x, double y, double move_dist, double kill_dist);
    virtual ~NPC() = default;

    double distance_to(const NPC& other) const;
    virtual bool can_kill(const NPC& other) const = 0;
    virtual char getTypeChar() const = 0;

    void move_towards(double target_x, double target_y);

    // Методы для сохранения/загрузки
    std::string to_string() const;
    static std::unique_ptr<NPC> from_string(const std::string& line);
};

class Bear : public NPC {
public:
    Bear(const std::string& name, double x, double y);
    bool can_kill(const NPC& other) const override;
    char getTypeChar() const override;
};

class Elf : public NPC {
public:
    Elf(const std::string& name, double x, double y);
    bool can_kill(const NPC& other) const override;
    char getTypeChar() const override;
};

class Bandit : public NPC {
public:
    Bandit(const std::string& name, double x, double y);
    bool can_kill(const NPC& other) const override;
    char getTypeChar() const override;
};

#endif