#ifndef __LINEQSYSTEM2__
    #define __LINEQSYSTEM2__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>
    #include "Maze.h"

    class LinEqSystem2 {
    private:
        class Column {
        public:
            float first, second;

            Column(sf::Vector2f v);

        };

        static float determinant(Column v1, Column v2);

    public:
        static bool solve(Column a, Column b, Column c, float& t, float& l);

    };


#endif // __LINEQSYSTEM2__
