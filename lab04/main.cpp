// Made by Egor
//
//
#include <iostream>
#include <memory>
#include <cstdlib>
#include "Array.h"
#include "Figures.h"

// очистка буфера ввода
void clearInput() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

// функция добавления новой фигуры
void addFigure(Array<std::shared_ptr<Figure<double>>>& figures) {
    std::cout << "введите тип фигуры (Rhombus/Pentagon/Hexagon): ";
    std::string type;
    std::cin >> type;

    std::cout << "введите центр (x y) и радиус: ";
    double x, y, r;
    if(std::cin >> x >> y >> r) {
        Point<double> center(x, y);

        if(type == "Rhombus") {
            figures.push_back(std::make_shared<Rhombus<double>>(center, r));
            std::cout << "ромб добавлен!\n";
        } else if(type == "Pentagon") {
            figures.push_back(std::make_shared<Pentagon<double>>(center, r));
            std::cout << "пятиугольник добавлен!\n";
        } else if(type == "Hexagon") {
            figures.push_back(std::make_shared<Hexagon<double>>(center, r));
            std::cout << "шестиугольник добавлен!\n";
        } else {
            std::cout << "неизвестный тип! доступно: Rhombus, Pentagon, Hexagon\n";
        }
    } else {
        std::cout << "неверный ввод!\n";
        clearInput();
    }
}

// демонстрация move между массивами из основного массива
void demonstrateMoveFromMainArray(Array<std::shared_ptr<Figure<double>>>& mainArray) {
    std::cout << "\n=== демонстрация move из основного массива ===\n";

    if(mainArray.size() == 0) {
        std::cout << "основной массив пуст! сначала создайте фигуры.\n";
        return;
    }

    std::cout << "в основном массиве " << mainArray.size() << " фигур\n";
    std::cout << "сколько фигур переместить? (1-" << mainArray.size() << "): ";
    int count;
    std::cin >> count;

    if(count <= 0 || count > mainArray.size()) {
        std::cout << "неверное количество!\n";
        return;
    }

    // создаем большой массив (емкость = count + 2)
    int largeCapacity = count + 2;
    Array<std::shared_ptr<Figure<double>>> largeArray(largeCapacity);
    std::cout << "создан массив largeArray с емкостью: " << largeArray.capacity() << "\n";

    // перемещаем элементы из основного массива в большой
    std::cout << "перемещаем " << count << " элементов из основного массива в largeArray:\n";
    for(int i = 0; i < count; ++i) {
        std::cout << "move элемент [" << i << "]: ";
        mainArray[i]->print(std::cout);
        std::cout << "\n";
        largeArray.push_back(std::move(mainArray[i]));  // перемещаем из основного массива
    }

    // проверка основного массива после move
    std::cout << "проверка основного массива после move:\n";
    std::cout << "основной массив размер: " << mainArray.size() << "\n";
    for(size_t i = 0; i < mainArray.size(); ++i) {
        if(mainArray.is_moved(i)) {
            std::cout << "[" << i << "]: nullptr (элемент перемещен)\n";
        } else {
            std::cout << "[" << i << "]: " << *mainArray[i] << "\n";
        }
    }

    std::cout << "результат:\n";
    std::cout << "largeArray: размер " << largeArray.size() << ", емкость " << largeArray.capacity() << "\n";
    for(size_t i = 0; i < largeArray.size(); ++i) {
        std::cout << "[" << i << "]: " << *largeArray[i] << "\n";
    }

    // удаляем перемещенные элементы из основного массива
    for(int i = 0; i < count; ++i) {
        mainArray.remove(0);  // удаляем первый элемент (после move он nullptr)
    }

    std::cout << "после очистки основной массив: размер " << mainArray.size() << "\n";
    std::cout << "демонстрация завершена!\n\n";
}

void demonstrateArrayWithRawPointersAndDerived() {
    std::cout << "\n=== Демонстрация Array с Figure<double>* и Rhombus<double> ===\n";

    std::cout << "\n1. Работа с Array<Figure<double>*> (указатели на базовый класс):\n";
    Array<Figure<double>*> figure_ptrs(4);

    auto* rhombus_ptr = new Rhombus<double>(Point<double>(0, 0), 5.0);
    auto* pentagon_ptr = new Pentagon<double>(Point<double>(1, 1), 3.0);

    figure_ptrs.push_back(rhombus_ptr);
    figure_ptrs.push_back(pentagon_ptr);

    std::cout << "Размер массива указателей: " << figure_ptrs.size() << "\n";
    for (size_t i = 0; i < figure_ptrs.size(); ++i) {
        std::cout << "[" << i << "]: " << *figure_ptrs[i] << "\n";
    }

    std::cout << "\n2. Работа с Array<Rhombus<double>> (массив объектов наследника):\n";
    Array<Rhombus<double>> rhombus_array(3); // Массив объектов ромбов

    rhombus_array.push_back(Rhombus<double>(Point<double>(2, 2), 4.0));
    rhombus_array.push_back(Rhombus<double>(Point<double>(3, 3), 6.0));

    std::cout << "Размер массива ромбов: " << rhombus_array.size() << "\n";
    for (size_t i = 0; i < rhombus_array.size(); ++i) {
        std::cout << "[" << i << "]: " << rhombus_array[i] << "\n";
    }

    for (size_t i = 0; i < figure_ptrs.size(); ++i) {
        delete figure_ptrs[i];
    }

    std::cout << "\nКонец.\n";
}

int main() {
    system("chcp 65001");

    Array<std::shared_ptr<Figure<double>>> figures;

    std::cout << "сколько фигур создать изначально? ";
    int n;
    std::cin >> n;

    // создание начальных фигур
    for(int i = 0; i < n; ++i) {
        std::cout << "фигура " << i+1 << " - введите тип (Rhombus/Pentagon/Hexagon): ";
        std::string type;
        std::cin >> type;

        std::cout << "введите центр (x y) и радиус: ";
        double x, y, r;
        if(std::cin >> x >> y >> r) {
            Point<double> center(x, y);

            if(type == "Rhombus") {
                figures.push_back(std::make_shared<Rhombus<double>>(center, r));
            } else if(type == "Pentagon") {
                figures.push_back(std::make_shared<Pentagon<double>>(center, r));
            } else if(type == "Hexagon") {
                figures.push_back(std::make_shared<Hexagon<double>>(center, r));
            } else {
                std::cout << "неизвестный тип! доступно: Rhombus, Pentagon, Hexagon\n";
                --i;
            }
        } else {
            std::cout << "неверный ввод!\n";
            clearInput();
            --i;
        }
    }

    int choice;
    do {
        std::cout << "\n=== меню ===\n";
        std::cout << "1. показать все фигуры\n";
        std::cout << "2. вычислить общую площадь\n";
        std::cout << "3. удалить фигуру по индексу\n";
        std::cout << "4. добавить новую фигуру\n";
        std::cout << "5. демонстрация move между массивами\n";
        std::cout << "6. демонстрация Array с Figure<double>* и Rhombus<double>\n";
        std::cout << "0. выход\n";
        std::cout << "выбор: ";
        std::cin >> choice;

        switch(choice) {
            case 1:
                if(figures.size() == 0) {
                    std::cout << "нет фигур для отображения.\n";
                } else {
                    std::cout << "\n--- все фигуры ---\n";
                    for(size_t i = 0; i < figures.size(); ++i) {
                        std::cout << "[" << i << "]: " << *figures[i] << std::endl;
                    }
                }
                break;

            case 2:
                if(figures.size() == 0) {
                    std::cout << "нет фигур для вычисления площади.\n";
                } else {
                    double total = 0;
                    for(size_t i = 0; i < figures.size(); ++i) {
                        total += static_cast<double>(*figures[i]);
                    }
                    std::cout << "общая площадь всех фигур: " << total << std::endl;
                }
                break;

            case 3:
                if(figures.size() == 0) {
                    std::cout << "нет фигур для удаления.\n";
                } else {
                    std::cout << "текущее количество фигур: " << figures.size() << std::endl;
                    std::cout << "введите индекс для удаления (0-" << figures.size()-1 << "): ";
                    size_t idx;
                    if(std::cin >> idx && idx < figures.size()) {
                        figures.remove(idx);
                        std::cout << "фигура удалена!\n";
                    } else {
                        std::cout << "неверный индекс!\n";
                        clearInput();
                    }
                }
                break;

            case 4:
                addFigure(figures);
                break;

            case 5:
                demonstrateMoveFromMainArray(figures);
                break;
            case 6:
                demonstrateArrayWithRawPointersAndDerived();
                break;

            case 0:
                std::cout << "выход из программы. пока!\n";
                break;

            default:
                std::cout << "неверный выбор! попробуйте снова.\n";
                break;
        }
    } while(choice != 0);
    return 0;
}