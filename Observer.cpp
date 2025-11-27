//
// Created by Егор on 11/25/2025.
//
#include "Observer.h"
#include <fstream>
#include <iostream>
// открываем файл и пишем в него
void FileObserver::notify(const NPC& killer, const NPC& victim) {
    std::ofstream file("log.txt", std::ios::app);
    file << killer.name << " (" << killer.type() << ") killed " << victim.name << " (" << victim.type() << ")\n";
}
// выводим в консоль
void ConsoleObserver::notify(const NPC& killer, const NPC& victim) {
    std::cout << killer.name << " (" << killer.type() << ") killed " << victim.name << " (" << victim.type() << ")\n";
}