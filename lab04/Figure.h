// Made by egor 29 10 2025
//
//
#ifndef FIGURE_H
#define FIGURE_H

#include "Point.h"
#include <memory>
#include <iostream>

// базовый класс для всех фигур
template<Scalar T>
class Figure {
public:
    virtual ~Figure() = default;

    // чисто виртуальные, надо переопределять
    virtual Point<T> center() const = 0;
    virtual double area() const = 0;
    virtual void print(std::ostream& os) const = 0;

    // для копирования фигуры
    virtual std::unique_ptr<Figure<T>> clone() const = 0;
    // сравнение фигур
    virtual bool operator==(const Figure<T>& other) const = 0;

    // приведение к double - возвращает площадь
    virtual operator double() const { return area(); }

    // перегрузка вывода
    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
        fig.print(os);
        return os;
    }
};

#endif