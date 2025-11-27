//
// Created by Егор on 11/25/2025.
//
#ifndef NPC_H
#define NPC_H

#include <string>
#include <memory>

class NPC {
public:
    std::string name;
    double x, y;

    NPC(const std::string& name, double x, double y);

    virtual ~NPC() = default;

    double distance_to(const NPC& other) const;

    virtual bool can_kill(const NPC& other) const = 0;
    virtual std::string type() const = 0;
    virtual std::string to_string() const;

    static std::unique_ptr<NPC> from_string(const std::string& line);
};
// абстрактный класс для всех NPC
class Bear : public NPC {
public:
    Bear(const std::string& name, double x, double y);
    bool can_kill(const NPC& other) const override;
    std::string type() const override;
};

class Elf : public NPC {
public:
    Elf(const std::string& name, double x, double y);
    bool can_kill(const NPC& other) const override;
    std::string type() const override;
};

class Bandit : public NPC {
public:
    Bandit(const std::string& name, double x, double y);
    bool can_kill(const NPC& other) const override;
    std::string type() const override;
};
// три npc
#endif