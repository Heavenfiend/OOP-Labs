// Made by egor 29 10 2025
//
//
#ifndef POINT_H
#define POINT_H

#include <type_traits>
#include <iostream>

// типа концепт для скаляров, чтоб только числа можно было
template<typename T>
concept Scalar = std::is_arithmetic_v<T>;

// точка с координатами x y
template<Scalar T>
struct Point {
    T x, y;
    Point(T x = 0, T y = 0) : x(x), y(y) {}

    // сравниваем точки
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    // не равны
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }

    // вывод в поток
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << "," << p.y << ")";
        return os;
    }

    // ввод с потока
    friend std::istream& operator>>(std::istream& is, Point& p) {
        is >> p.x >> p.y;
        return is;
    }
};

#endif