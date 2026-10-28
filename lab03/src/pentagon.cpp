// Made bu Egor 24/10/25
//
//
#include "pentagon.h"
#include <cmath>

std::pair<double, double> Pentagon::center() const {
    double x = 0, y = 0;
    for (const auto& p : vertices) {
        x += p.first;
        y += p.second;
    }
    int n = vertices.size();
    return {x / n, y / n};
}

void Pentagon::print(std::ostream& os) const {
    os << "Pentagon vertices: ";
    for (const auto& p : vertices) {
        os << "(" << p.first << "," << p.second << ") ";
    }
    os << std::endl;
}

void Pentagon::read(std::istream& is) {
    vertices.resize(5);
    for (int i = 0; i < 5; ++i) {
        is >> vertices[i].first >> vertices[i].second;
    }
}

Pentagon::operator double() const {
    double area = 0.0;
    int n = vertices.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += vertices[i].first * vertices[j].second;
        area -= vertices[j].first * vertices[i].second;
    }
    return std::abs(area) / 2.0;
}

Figure* Pentagon::clone() const {
    return new Pentagon(*this);
}

Figure* Pentagon::moveClone() {
    return new Pentagon(std::move(*this));
}

bool Pentagon::operator==(const Figure& other) const {
    const Pentagon* p = dynamic_cast<const Pentagon*>(&other);
    if (!p) return false;
    return vertices == p->vertices;
}