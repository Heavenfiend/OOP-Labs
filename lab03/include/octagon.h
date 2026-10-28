// Made bu Egor 24/10/25
//
//
#ifndef OCTAGON_H
#define OCTAGON_H

#include "figure.h"
#include <vector>

class Octagon : public Figure {
private:
    std::vector<Point> vertices;
public:
    Octagon() = default;
    Octagon(const std::vector<Point>& vertices) : vertices(vertices) {}
    Octagon(const Octagon& other) : vertices(other.vertices) {}
    Octagon(Octagon&& other) noexcept : vertices(std::move(other.vertices)) {}
    Octagon& operator=(const Octagon& other) {
        if (this != &other) {
            vertices = other.vertices;
        }
        return *this;
    }
    Octagon& operator=(Octagon&& other) noexcept {
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