//
// Created by Егор on 11/25/2025.
//
#include "Observer.h"
#include <fstream>
#include <iostream>

void FileObserver::notify(const NPC& killer, const NPC& victim) {
    std::ofstream file("log.txt", std::ios::app);
    file << killer.name << " (" << killer.getTypeChar() << ") killed " << victim.name << " (" << victim.getTypeChar() << ")\n";
}

void ConsoleObserver::notify(const NPC& killer, const NPC& victim) {
    std::cout << killer.name << " (" << killer.getTypeChar() << ") killed " << victim.name << " (" << victim.getTypeChar() << ")\n";
}