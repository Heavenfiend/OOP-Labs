// Made by egor 29 10 2025
//
//
#ifndef FIGURES_H
#define FIGURES_H

#include "Figure.h"
#include <cmath>
#include <memory>
#include <vector>

// базовый класс для фигур вращения
template<Scalar T>
class RotationalFigure : public Figure<T> {
protected:
    std::unique_ptr<Point<T>> center_;  // центр фигуры
    T radius_;                          // радиус
    std::vector<Point<T>> vertices_;    // вершины фигуры

public:
    RotationalFigure(Point<T> center, T radius)
        : center_(std::make_unique<Point<T>>(center)), radius_(radius) {}

    // возвращаем центр
    Point<T> center() const override { return *center_; }

    // геттер для вершин
    const std::vector<Point<T>>& get_vertices() const { return vertices_; }
};

// ромб - фигура вращения
template<Scalar T>
class Rhombus : public RotationalFigure<T> {
public:
    Rhombus(Point<T> center, T radius) : RotationalFigure<T>(center, radius) {
        // вычисляем 4 вершины ромба
        this->vertices_.push_back(Point<T>(center.x, center.y + radius));
        this->vertices_.push_back(Point<T>(center.x + radius, center.y));
        this->vertices_.push_back(Point<T>(center.x, center.y - radius));
        this->vertices_.push_back(Point<T>(center.x - radius, center.y));
    }

    // площадь ромба
    double area() const override {
        return 2.0 * this->radius_ * this->radius_;  // 2 * r^2
    }

    // вывод информации о ромбе
    void print(std::ostream& os) const override {
        os << "ромб - вершины: ";
        for(const auto& v : this->vertices_) {
            os << v << " ";
        }
        os << "центр: " << *this->center_ << " площадь: " << area();
    }

    // создание копии
    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Rhombus<T>>(*this->center_, this->radius_);
    }

    // сравнение ромбов
    bool operator==(const Figure<T>& other) const override {
        const auto* other_rhombus = dynamic_cast<const Rhombus<T>*>(&other);
        if(!other_rhombus) return false;  // если не ромб
        return *this->center_ == other_rhombus->center() &&
               this->radius_ == other_rhombus->radius_;
    }
};

// пятиугольник
template<Scalar T>
class Pentagon : public RotationalFigure<T> {
public:
    Pentagon(Point<T> center, T radius) : RotationalFigure<T>(center, radius) {
        // вычисляем 5 вершин через углы
        for(int i = 0; i < 5; ++i) {
            double angle = 2 * 3.14159 * i / 5;  // угол для вершины
            T x = center.x + radius * static_cast<T>(std::cos(angle));
            T y = center.y + radius * static_cast<T>(std::sin(angle));
            this->vertices_.push_back(Point<T>(x, y));
        }
    }

    // площадь пятиугольника
    double area() const override {
        return 0.5 * 5 * this->radius_ * this->radius_ * std::sin(2 * 3.14159 / 5);
    }

    void print(std::ostream& os) const override {
        os << "пятиугольник - вершины: ";
        for(const auto& v : this->vertices_) {
            os << v << " ";
        }
        os << "центр: " << *this->center_ << " площадь: " << area();
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Pentagon<T>>(*this->center_, this->radius_);
    }

    bool operator==(const Figure<T>& other) const override {
        const auto* other_pentagon = dynamic_cast<const Pentagon<T>*>(&other);
        if(!other_pentagon) return false;
        return *this->center_ == other_pentagon->center() &&
               this->radius_ == other_pentagon->radius_;
    }
};

// шестиугольник
template<Scalar T>
class Hexagon : public RotationalFigure<T> {
public:
    Hexagon(Point<T> center, T radius) : RotationalFigure<T>(center, radius) {
        // вычисляем 6 вершин шестиугольника
        for(int i = 0; i < 6; ++i) {
            double angle = 2 * 3.14159 * i / 6;
            T x = center.x + radius * static_cast<T>(std::cos(angle));
            T y = center.y + radius * static_cast<T>(std::sin(angle));
            this->vertices_.push_back(Point<T>(x, y));
        }
    }

    // площадь шестиугольника
    double area() const override {
        return (3 * std::sqrt(3) / 2) * this->radius_ * this->radius_;
    }

    void print(std::ostream& os) const override {
        os << "шестиугольник - вершины: ";
        for(const auto& v : this->vertices_) {
            os << v << " ";
        }
        os << "центр: " << *this->center_ << " площадь: " << area();
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Hexagon<T>>(*this->center_, this->radius_);
    }

    bool operator==(const Figure<T>& other) const override {
        const auto* other_hexagon = dynamic_cast<const Hexagon<T>*>(&other);
        if(!other_hexagon) return false;
        return *this->center_ == other_hexagon->center() &&
               this->radius_ == other_hexagon->radius_;
    }
};

// явные инстанцирования для double
template class RotationalFigure<double>;
template class Rhombus<double>;
template class Pentagon<double>;
template class Hexagon<double>;

#endif