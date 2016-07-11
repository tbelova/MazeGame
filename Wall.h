#ifndef __WALL__
    #define __WALL__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>
    #include "Consts.h"

    class Wall: public sf::Drawable {
    private:
        sf::Vector2<int> pos;
        sf::RectangleShape rect;

    public:
        Wall(sf::Vector2<int> v);
        sf::Vector2<int> getPos();
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        virtual ~Wall();

    };

#endif // __WALL__
