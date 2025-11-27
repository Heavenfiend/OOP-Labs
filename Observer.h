//
// Created by Егор on 11/25/2025.
//
#ifndef OBSERVER_H
#define OBSERVER_H

#include "NPC.h"
// интерфейс наблюдателя и его реализации при убийстве
class Observer {
public:
    virtual ~Observer() = default;
    virtual void notify(const NPC& killer, const NPC& victim) = 0;
};
// запись в файл
class FileObserver : public Observer {
public:
    void notify(const NPC& killer, const NPC& victim) override;
};
// вывод в консоль
class ConsoleObserver : public Observer {
public:
    void notify(const NPC& killer, const NPC& victim) override;
};

#endif