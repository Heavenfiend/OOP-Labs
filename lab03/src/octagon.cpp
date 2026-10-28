// Made bu Egor 24/10/25
//
//
#include "octagon.h"
#include <cmath>

std::pair<double, double> Octagon::center() const {
    double x = 0, y = 0;
    for (const auto& p : vertices) {
        x += p.first;
        y += p.second;
    }
    int n = vertices.size();
    return {x / n, y / n};
}

void Octagon::print(std::ostream& os) const {
    os << "Octagon vertices: ";
    for (const auto& p : vertices) {
        os << "(" << p.first << "," << p.second << ") ";
    }
    os << std::endl;
}

void Octagon::read(std::istream& is) {
    vertices.resize(8);
    for (int i = 0; i < 8; ++i) {
        is >> vertices[i].first >> vertices[i].second;
    }
}

Octagon::operator double() const {
    double area = 0.0;
    int n = vertices.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += vertices[i].first * vertices[j].second;
        area -= vertices[j].first * vertices[i].second;
    }
    return std::abs(area) / 2.0;
}

Figure* Octagon::clone() const {
    return new Octagon(*this);
}

Figure* Octagon::moveClone() {
    return new Octagon(std::move(*this));
}

bool Octagon::operator==(const Figure& other) const {
    const Octagon* p = dynamic_cast<const Octagon*>(&other);
    if (!p) return false;
    return vertices == p->vertices;
}