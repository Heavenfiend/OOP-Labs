// Made bu Egor 24/10/25
//
//
#include <iostream>
#include <vector>
#include <memory>
#include "figure.h"
#include "pentagon.h"
#include "hexagon.h"
#include "octagon.h"

using namespace std;

int main() {
    vector<Figure*> figures;
    string type;

    cout << "Enter figures (pentagon, hexagon, octagon), type 'end' to finish:\n";
    while (cin >> type && type != "end") {
        Figure* fig = nullptr;
        if (type == "pentagon") {
            fig = new Pentagon();
        } else if (type == "hexagon") {
            fig = new Hexagon();
        } else if (type == "octagon") {
            fig = new Octagon();
        } else {
            cout << "Unknown figure type.\n";
            continue;
        }

        cin >> *fig;
        figures.push_back(fig);
    }

    cout << "\nFigures info:\n";
    double total_area = 0.0;
    for (const auto& fig : figures) {
        auto center = fig->center();
        cout << "Center: (" << center.first << ", " << center.second << ")\n";
        cout << "Area: " << static_cast<double>(*fig) << endl;
        cout << *fig << endl;
        total_area += static_cast<double>(*fig);
    }

    cout << "Total area: " << total_area << endl;

    int index;
    cout << "Enter index to remove figure (0-" << figures.size() - 1 << "): ";
    cin >> index;
    if (index >= 0 && index < figures.size()) {
        delete figures[index];
        figures.erase(figures.begin() + index);
    }

    cout << "After removal, remaining figures:\n";
    for (const auto& fig : figures) {
        cout << *fig << endl;
    }

    for (auto fig : figures) delete fig;

    return 0;
}