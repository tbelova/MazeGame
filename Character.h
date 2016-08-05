#ifndef __CHARACTER__
    #define __CHARACTER__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>
    #include "Consts.h"
    #include "Manager.h"
    #include "Updatable.h"
    #include "SetOfSegments.h"
    #include "Maze.h"
    #include "Smth.h"

    class Character: public Managable<sf::Drawable>, public Managable<Updatable> {
    private:
        sf::Vector2f pos;
        sf::RectangleShape rect;
        const float speed = 2 * WallSize;
        const float eps = 1e-3;

    public:
        SetOfSegments segments;

        Character(sf::Vector2f v, Manager<sf::Drawable>& mng, Manager<Updatable>& updMng);

        sf::Vector2f getPos() const;
        void setPos(sf::Vector2f v);
        void move(sf::Vector2f v);
        void moveCharacter(sf::Vector2f v, sf::Time time);
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        virtual void update(sf::Time time) override;
        virtual ~Character() = default;

    };

#endif
