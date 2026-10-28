//
// Created by Egor on 10 11 2025
//
#include "GameEngine.h"
#include <iostream>
#include <random>

void GameEngine::run() {
    // генер случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 500.0);

    // создаем 50 нппс
    for (int i = 0; i < 50; ++i) {
        // тип нпси
        char type = "BER"[i % 3];
        // имя
        std::string name = std::string(1, type) + std::to_string(i);
        // координаты
        double x = dis(gen);
        double y = dis(gen);
        editor.add_npc(type == 'B' ? "Bear" : (type == 'E' ? "Elf" : "Bandit"), name, x, y);
    }
    // запускаем планировщик
    std::thread scheduler_thread([this]() {
        scheduler.run();
    });
    // основной поток игры
    std::thread game_thread([this, &gen, &dis, &scheduler_thread]() {
        // хапоминаем время старта
        auto start_time = std::chrono::steady_clock::now();
        std::uniform_real_distribution<> move_dis(-1.0, 1.0);
        // 30 секунд игры
        while (true) {
            auto now = std::chrono::steady_clock::now();
            // проверяем, что время не вышло
            if (now - start_time >= std::chrono::seconds(GAME_DURATION)) {
                game_running = false; // останавливаем игру
                scheduler.stop(); // останавливаем планировщик
                break;
            }

            {
                // блокируем чтобы безопасно работать со списком NPC
                std::unique_lock<std::shared_mutex> lock(world_mtx);
                auto& npcs = editor.get_npcs();
                // перемещаем всех NPC
                for (auto& npc : npcs) {
                    // пропускаем мёртвых
                    if (!npc->alive) continue;

                    {   // блокируем чтобы безопасно работать c кордами
                        std::lock_guard<std::mutex> npc_lock(npc->mtx);
                        // двигаемся
                        npc->move_towards(npc->x + move_dis(gen), npc->y + move_dis(gen));
                    }
                    for (auto& other : npcs) {
                        if (npc.get() == other.get() || !other->alive) continue;
                        // проверяем, что расстояние меньше kill_distance
                        if (npc->distance_to(*other) <= npc->kill_distance) {
                            if (npc->can_kill(*other)) {
                                // создаём корутину и отправляем в планировщик
                                auto task = fight_coro(*npc, *other, cout_mtx);
                                scheduler.submit(task.handle);
                            }
                        }
                    }
                }
            }
            // спим 100 мс чтобы не перегружать процессор
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });
    // выводим карту каждую секунду только с живыми NPC
    std::thread display_thread([this]() {
        for (int i = 0; i < GAME_DURATION; ++i) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            print_map();
        }
    });
    // ждём завершения потоков
    game_thread.join();
    display_thread.join();
    scheduler_thread.join();
}
// вспомогательная функция для вывода карты
void GameEngine::print_map() {
    std::ostringstream oss;
    oss << "\n=== MAP ===\n";

    {   // бблокировка на чтение, безопасно читаем список NPC
        std::shared_lock<std::shared_mutex> lock(world_mtx);
        editor.print_npcs();
    }
    // блок вывода: чтобы не было гонки при выводе в консоль
    std::lock_guard<std::mutex> cout_lock(cout_mtx);
    std::cout << oss.str();
}
// выводим выживших после игры
void GameEngine::print_survivors() {
    std::lock_guard<std::mutex> cout_lock(cout_mtx);
    std::cout << "\n=== SURVIVORS ===\n";
    std::shared_lock<std::shared_mutex> lock(world_mtx);
    editor.print_npcs();
}