// Made bu Egor 24/10/25
//
//
#include "hexagon.h"
#include <cmath>

std::pair<double, double> Hexagon::center() const {
    double x = 0, y = 0;
    for (const auto& p : vertices) {
        x += p.first;
        y += p.second;
    }
    int n = vertices.size();
    return {x / n, y / n};
}

void Hexagon::print(std::ostream& os) const {
    os << "Hexagon vertices: ";
    for (const auto& p : vertices) {
        os << "(" << p.first << "," << p.second << ") ";
    }
    os << std::endl;
}

void Hexagon::read(std::istream& is) {
    vertices.resize(6);
    for (int i = 0; i < 6; ++i) {
        is >> vertices[i].first >> vertices[i].second;
    }
}

Hexagon::operator double() const {
    double area = 0.0;
    int n = vertices.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += vertices[i].first * vertices[j].second;
        area -= vertices[j].first * vertices[i].second;
    }
    return std::abs(area) / 2.0;
}

Figure* Hexagon::clone() const {
    return new Hexagon(*this);
}

Figure* Hexagon::moveClone() {
    return new Hexagon(std::move(*this));
}

bool Hexagon::operator==(const Figure& other) const {
    const Hexagon* p = dynamic_cast<const Hexagon*>(&other);
    if (!p) return false;
    return vertices == p->vertices;
}