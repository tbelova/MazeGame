#ifndef __WALL__
    #define __WALL__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>
    #include "Consts.h"

    class Wall: public sf::Drawable {
    private:
        sf::Vector2<int> pos;

    public:
        Wall(sf::Vector2<int> v): pos(v) {}

        sf::Vector2<int> getPos() {
            return pos;
        }

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
            sf::RectangleShape rect(sf::Vector2f(C, C));
            rect.setPosition(sf::Vector2f(C * pos.y, C * pos.x));
            rect.setFillColor(sf::Color::Red);

            target.draw(rect, states);
        }

        virtual ~Wall() {}

    };

#endif // __WALL__
