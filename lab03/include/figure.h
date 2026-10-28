#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <vector>
#include <utility>

typedef std::pair<double, double> Point;

class Figure {
public:
    virtual ~Figure() = default;
    virtual std::pair<double, double> center() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual operator double() const = 0;

    virtual Figure* clone() const = 0;
    virtual Figure* moveClone() = 0;
    virtual bool operator==(const Figure& other) const = 0;
    virtual bool operator!=(const Figure& other) const { return !(*this == other); }
};

std::ostream& operator<<(std::ostream& os, const Figure& fig);
std::istream& operator>>(std::istream& is, Figure& fig);

#endif