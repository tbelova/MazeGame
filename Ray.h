#ifndef __RAY__
    #define __RAY__

    #include <SFML/Graphics.hpp>

    class Ray {
    public:
        sf::Vector2f p, v;

        Ray(sf::Vector2f p, sf::Vector2f v);

    };


#endif // __RAY__
