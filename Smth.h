#ifndef __SMTH__
    #define __SMTH__

    #include <SFML/Graphics.hpp>
    #include <cstdio>
    #include "Consts.h"

    template <class T>
    float sqrLength(sf::Vector2<T> v) {
        return v.x * v.x + v.y * v.y;
    }

    template <class T>
    float Length(sf::Vector2<T> v) {
        return std::sqrt(sqrLength(v));
    }

    template <class T>
    T dot_product(sf::Vector2<T> a, sf::Vector2<T> b) {
        return a.x * b.x + a.y * b.y;
    }

    template <class T>
    bool cmp(sf::Vector2<T> a, sf::Vector2<T> b) {
        return atan2(b.y, b.x) - atan2(a.y, a.x) > 1e-9;
    }

    inline sf::Vector2<int> FromGameToMaze(sf::Vector2f v) {
        return sf::Vector2<int>(v.x / WallSize, v.y / WallSize);
    }

    inline sf::Vector2f FromMazeToGame(sf::Vector2<int> v) {
        return sf::Vector2f(v.x * WallSize + WallSize / 2, v.y * WallSize + WallSize / 2);
    }


#endif // __SMTH__
