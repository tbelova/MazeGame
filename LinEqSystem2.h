#ifndef __LINEQSYSTEM2__
    #define __LINEQSYSTEM2__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>
    #include "Maze.h"

    class LinEqSystem2 {
    private:

        static float determinant(sf::Vector2f v1, sf::Vector2f v2);

    public:
        LinEqSystem2() = delete;

        static bool solve(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, float& t, float& l);

    };


#endif // __LINEQSYSTEM2__
