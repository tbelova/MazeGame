#ifndef __WALL__
    #define __WALL__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>
    #include "Consts.h"
    #include "Manager.h"
    #include "Updatable.h"

    class Wall: public Managable<sf::Drawable> {
    private:
        sf::Vector2f pos;
        sf::RectangleShape rect;

    public:
        Wall(const Wall& w) = default;
        Wall(sf::Vector2f v, Manager<sf::Drawable>& mng);
        sf::Vector2f getPos() const;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        virtual ~Wall() = default;

    };

#endif // __WALL__
