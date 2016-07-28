#ifndef __SEGMENT__
    #define __SEGMENT__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>
    #include "Maze.h"
    #include "LinEqSystem2.h"

    class SetOfSegments {
    public:

        class Segment {
        public:
            sf::Vector2f a, b;
            Segment();
            Segment(sf::Vector2f a, sf::Vector2f b);
        };

        class HZ {
        public:
            sf::Vector2f point;
            Segment segment;
            bool intersect;
        };

        std::vector<Segment> segments;

        HZ intersect(sf::Vector2f p, sf::Vector2f v);
        void Add(Segment s);
        void Add(sf::Vector2f a, sf::Vector2f b);
        void eraseEqual();

        void clear();

        SetOfSegments() = default;
        SetOfSegments(const SetOfSegments& ) = default;

    };


#endif // __SEGMENT__
