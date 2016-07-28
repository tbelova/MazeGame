#ifndef __SMTH__
    #define __SMTH__

    #include <SFML/Graphics.hpp>
    #include <cstdio>

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


#endif // __SMTH__
