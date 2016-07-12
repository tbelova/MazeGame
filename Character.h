#ifndef __CHARACTER__
    #define __CHARACTER__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>
    #include "Consts.h"
    #include "Manager.h"

    class Character: public Manager<sf::Drawable>::Object {
    private:
        sf::Vector2<int> pos;
        sf::RectangleShape rect;

    public:
        Character(sf::Vector2<int> v, Manager<sf::Drawable>& mng);
        sf::Vector2<int> getPos();
        void setPos(sf::Vector2<int> v);
        void move(sf::Vector2<int> v);
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        virtual ~Character();

    };

#endif
