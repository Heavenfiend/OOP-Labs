#include "GameEngine.h"
#include <iostream>
#include <random>

void GameEngine::run() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 500.0);

    // Создаём 50 NPC в случайных местах
    for (int i = 0; i < 50; ++i) {
        char type = "BER"[i % 3];
        std::string name = std::string(1, type) + std::to_string(i);
        double x = dis(gen);
        double y = dis(gen);
        editor.add_npc(type == 'B' ? "Bear" : (type == 'E' ? "Elf" : "Bandit"), name, x, y);
    }

    std::thread scheduler_thread([this]() {
        scheduler.run();
    });

    std::thread game_thread([this, &gen, &dis, &scheduler_thread]() {
        auto start_time = std::chrono::steady_clock::now();
        std::uniform_real_distribution<> move_dis(-1.0, 1.0);
        // 30 секунд
        while (true) {
            auto now = std::chrono::steady_clock::now();
            if (now - start_time >= std::chrono::seconds(GAME_DURATION)) {
                game_running = false;
                scheduler.stop();
                break;
            }

            {
                // захватываем мьютекс для доступа к миру
                std::unique_lock<std::shared_mutex> lock(world_mtx);
                auto& npcs = editor.get_npcs();
                // перемещаем всех NPC
                for (auto& npc : npcs) {
                    // пропускаем мёртвых
                    if (!npc->alive) continue;

                    {
                        std::lock_guard<std::mutex> npc_lock(npc->mtx);
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

    {
        std::shared_lock<std::shared_mutex> lock(world_mtx);
        editor.print_npcs();
    }

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