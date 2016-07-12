#ifndef __WALL__
    #define __WALL__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>
    #include "Consts.h"
    #include "Manager.h"

    class Wall: public Manager<sf::Drawable>::Object {
    private:
        sf::Vector2<int> pos;
        sf::RectangleShape rect;

    public:
        Wall(const Wall& w) = default;
        Wall(sf::Vector2<int> v, Manager<sf::Drawable>& mng);
        sf::Vector2<int> getPos();
        void setPos(sf::Vector2<int> v);
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        virtual ~Wall();

    };

#endif // __WALL__
