#include "Five.h"
#include <iostream>

int main() {
    system("chcp 65001");
    try {
        Five num1("333");
        Five num2("322");

        Five sum = num1.add(num2);
        Five diff = num1.subtract(num2);
        Five num3 = num1.assign(num2);

        std::cout << "num1: ";
        num1.print();
        std::cout << "num2: ";
        num2.print();
        std::cout << "sum: ";
        sum.print();
        std::cout << "diff: ";
        diff.print();
        std::cout << "num3: ";
        num3.print();

        std::cout << "equal: " << (num1.equals(num2) ? "yes" : "no") << std::endl;
        std::cout << "less: " << (num1.less(num2) ? "yes" : "no") << std::endl;
        std::cout << "greater: " << (num1.greater(num2) ? "yes" : "no") << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}