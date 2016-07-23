#ifndef __SMTH__
    #define __SMTH__

    #include <SFML/Graphics.hpp>

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

#endif // __SMTH__
