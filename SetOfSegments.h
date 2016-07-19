#ifndef __SEGMENT__
    #define __SEGMENT__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>
    #include "Maze.h"
    #include "LinEqSystem2.h"
    #include "Ray.h"

    class SetOfSegments {
    public:

        class Segment {
        public:
            sf::Vector2f a, b;
            Segment(sf::Vector2f a, sf::Vector2f b);
        };

        std::vector<Segment> segments;

        bool intersect(Ray ray, sf::Vector2f& p);

        SetOfSegments() = default;
        SetOfSegments(const SetOfSegments& ) = default;

    };


#endif // __SEGMENT__
