#ifndef __SEGMENT__
    #define __SEGMENT__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>
    #include "Maze.h"
    #include "LinEqSystem2.h"
    #include "Ray.h"

    class SetOfSegments {
    private:
        class Segment {
        public:
            sf::Vector2f a, b;
            Segment(sf::Vector2f a, sf::Vector2f b);
        };

    public:
        std::vector<Segment> segments;

        SetOfSegments(Maze& maze);
        bool intersect(Ray ray, sf::Vector2f& p);
        SetOfSegments(const SetOfSegments& ) = default;

    };


#endif // __SEGMENT__
