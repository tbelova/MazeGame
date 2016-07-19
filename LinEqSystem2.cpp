#include "LinEqSystem2.h"

float LinEqSystem2::determinant(sf::Vector2f v1, sf::Vector2f v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

bool LinEqSystem2::solve(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, float& t, float& l) {
    float detAB = determinant(a, b);
    if (detAB == 0) return false;
    t = determinant(c, b) / detAB;
    l = determinant(a, c) / detAB;

    return true;
}

