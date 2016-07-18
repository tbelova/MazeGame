#include "LinEqSystem2.h"

LinEqSystem2::Column::Column(sf::Vector2f v): first(v.x), second(v.y) {}

float LinEqSystem2::determinant(Column v1, Column v2) {
    return v1.first * v2.second - v1.second * v2.first;
}

bool LinEqSystem2::solve(Column a, Column b, Column c, float& t, float& l) {
    float detAB = determinant(a, b);
    if (detAB == 0) return false;
    t = determinant(c, b) / detAB;
    l = determinant(a, c) / detAB;

    return true;
}

