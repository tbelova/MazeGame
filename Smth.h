#ifndef __SMTH__
    #define __SMTH__

    #include <SFML/Graphics.hpp>

    template<class T>
    float sqrLength(sf::Vector2<T> v) {
        return v.x * v.x + v.y * v.y;
    }

#endif // __SMTH__
