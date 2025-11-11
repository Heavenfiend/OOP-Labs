//
// Made by Egor
// 11 11 2025
//
#include <iostream>
#include <string>
#include "FixedBlockMemoryResource.h"
#include "DoublyLinkedList.h"

struct Person {
    std::string name;
    int age;

    Person(const std::string& n, int a) : name(n), age(a) {}

    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << "Person{name='" << p.name << "', age=" << p.age << "}";
        return os;
    }
};

int main() {
    FixedBlockMemoryResource memory_resource(50);

    std::cout << "=== int ===" << std::endl;

    DoublyLinkedList<int> int_list(&memory_resource);

    int_list.push_back(10);
    int_list.push_back(20);
    int_list.push_front(5);
    int_list.push_back(30);

    std::cout << "Elements: ";
    for (auto it = int_list.begin(); it != int_list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    int_list.pop_front();

    std::cout << "After pop_front: ";
    for (const auto& value : int_list) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    std::cout << "\n=== Person ===" << std::endl;

    DoublyLinkedList<Person> person_list(&memory_resource);

    person_list.push_back(Person("Alice", 25));
    person_list.push_back(Person("Bob", 30));
    person_list.push_front(Person("Charlie", 35));

    std::cout << "Elements:" << std::endl;
    for (auto it = person_list.begin(); it != person_list.end(); ++it) {
        std::cout << "  " << *it << std::endl;
    }

    std::cout << "\n=== Memory reuse ===" << std::endl;
    std::cout << "Free blocks before clear: " << memory_resource.free_count() << std::endl;

    int_list.clear();
    person_list.clear();

    std::cout << "Free blocks after clear: " << memory_resource.free_count() << std::endl;

    DoublyLinkedList<int> new_list(&memory_resource);
    for (int i = 0; i < 10; ++i) {
        new_list.push_back(i * 10);
    }

    std::cout << "Free blocks after new list: " << memory_resource.free_count() << std::endl;

    std::cout << "\nNew list elements: ";
    for (auto it = new_list.begin(); it != new_list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "\n=== Done ===" << std::endl;

    return 0;
}