// Made bu Egor 24/10/25
//
//
#include "figure.h"

std::ostream& operator<<(std::ostream& os, const Figure& fig) {
    fig.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Figure& fig) {
    fig.read(is);
    return is;
}