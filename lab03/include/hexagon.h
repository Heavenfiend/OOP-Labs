// Made bu Egor 24/10/25
//
//
#ifndef HEXAGON_H
#define HEXAGON_H

#include "figure.h"
#include <vector>

class Hexagon : public Figure {
private:
    std::vector<Point> vertices;
public:
    Hexagon() = default;
    Hexagon(const std::vector<Point>& vertices) : vertices(vertices) {}
    Hexagon(const Hexagon& other) : vertices(other.vertices) {}
    Hexagon(Hexagon&& other) noexcept : vertices(std::move(other.vertices)) {}
    Hexagon& operator=(const Hexagon& other) {
        if (this != &other) {
            vertices = other.vertices;
        }
        return *this;
    }
    Hexagon& operator=(Hexagon&& other) noexcept {
        if (this != &other) {
            vertices = std::move(other.vertices);
        }
        return *this;
    }

    std::pair<double, double> center() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    operator double() const override;

    Figure* clone() const override;
    Figure* moveClone() override;
    bool operator==(const Figure& other) const override;
};

#endif