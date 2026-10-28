// Made bu Egor 24/10/25
//
//
#ifndef PENTAGON_H
#define PENTAGON_H

#include "figure.h"
#include <vector>

class Pentagon : public Figure {
private:
    std::vector<Point> vertices;
public:
    Pentagon() = default;
    Pentagon(const std::vector<Point>& vertices) : vertices(vertices) {}
    Pentagon(const Pentagon& other) : vertices(other.vertices) {}
    Pentagon(Pentagon&& other) noexcept : vertices(std::move(other.vertices)) {}
    Pentagon& operator=(const Pentagon& other) {
        if (this != &other) {
            vertices = other.vertices;
        }
        return *this;
    }
    Pentagon& operator=(Pentagon&& other) noexcept {
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