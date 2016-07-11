#ifndef __OBJECT__
    #define __OBJECT__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>
    #include "Consts.h"

    class Object {
    public:
        virtual void draw(sf::RenderWindow &window) = 0;
    };

#endif // __OBJECT__
