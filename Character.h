#ifndef __CHARACTER__
    #define __CHARACTER__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>
    #include "Consts.h"

    class Character: public sf::Drawable {
    private:
        sf::Vector2<int> pos;
        sf::RectangleShape rect;

    public:
        Character();
        Character(sf::Vector2<int> v);
        sf::Vector2<int> getPos();
        void move(sf::Vector2<int> v);
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        virtual ~Character();

    };

#endif
