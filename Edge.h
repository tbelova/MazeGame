#ifndef __EDGE__
    #define __EDGE__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>
    #include "Consts.h"


    class Edge {
    public:
        sf::Vector2<int> v1, v2;
        sf::Vector2<int> pos;

        Edge(sf::Vector2<int>, sf::Vector2<int>, sf::Vector2<int>);
    };

#endif // __EDGE__
