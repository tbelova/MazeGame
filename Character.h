#ifndef __CHARACTER__
    #define __CHARACTER__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>
    #include "Consts.h"
    #include "Manager.h"

    class Character: public Managable<sf::Drawable> {
    private:
        sf::Vector2f pos;
        sf::RectangleShape rect;

    public:
        Character(sf::Vector2f v, Manager<sf::Drawable>& mng);
        sf::Vector2f getPos() const;
        void setPos(sf::Vector2f v);
        void move(sf::Vector2f v);
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        virtual ~Character() = default;

    };

#endif
