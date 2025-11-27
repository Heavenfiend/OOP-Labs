#include "Editor.h"
#include <iostream>
#include <string>
#include <limits>

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    DungeonEditor editor;
    int choice;

    std::cout << "=== Balagur Fate 3: Dungeon Editor ===\n\n";

    while (true) {
        std::cout << "\n--- Menu ---\n";
        std::cout << "1. Add NPC\n";
        std::cout << "2. Show all NPCs\n";
        std::cout << "3. Save to file\n";
        std::cout << "4. Load from file\n";
        std::cout << "5. Battle mode\n";
        std::cout << "6. Exit\n";
        std::cout << "Choose an option: ";

        if (!(std::cin >> choice)) {
            clearInput();
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                std::cout << "Enter NPC type (Bear / Elf / Bandit): ";
                std::string type;
                std::cin >> type;

                std::cout << "Enter name (no spaces): ";
                std::string name;
                std::cin >> name;

                double x, y;
                std::cout << "Enter x (0-500): ";
                std::cin >> x;
                std::cout << "Enter y (0-500): ";
                std::cin >> y;

                try {
                    editor.add_npc(type, name, x, y);
                    std::cout << "NPC added successfully!\n";
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 2:
                std::cout << "\n--- Current NPCs ---\n";
                editor.print_npcs();
                break;

            case 3: {
                std::string filename;
                std::cout << "Enter filename to save (e.g. dungeon.txt): ";
                std::cin >> filename;
                editor.save_to_file(filename);
                std::cout << "Saved to " << filename << ".\n";
                break;
            }
            case 4: {
                std::string filename;
                std::cout << "Enter filename to load (e.g. dungeon.txt): ";
                std::cin >> filename;
                try {
                    editor.load_from_file(filename);
                    std::cout << "Loaded from " << filename << ".\n";
                } catch (const std::exception& e) {
                    std::cout << "Error loading file: " << e.what() << "\n";
                }
                break;
            }
            case 5: {
                double dist;
                std::cout << "Enter battle distance: ";
                std::cin >> dist;
                std::cout << "\n--- Battle Mode (distance " << dist << ") ---\n";
                editor.battle_mode(dist);
                std::cout << "Battle finished.\n";
                break;
            }
            case 6:
                std::cout << "Goodbye!\n";
                return 0;

            default:
                std::cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}