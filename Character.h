#ifndef __CHARACTER__
    #define __CHARACTER__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>
    #include "Consts.h"
    #include "Manager.h"
    #include "Updatable.h"
    #include "Segment.h"
    #include "Maze.h"

    class Character: public Managable<sf::Drawable>, public Managable<Updatable> {
    private:
        sf::Vector2f pos;
        sf::RectangleShape rect;
        const float speed = 2;
        std::vector<Segment> segments;

    public:
        Character(sf::Vector2f v, Manager<sf::Drawable>& mng, Manager<Updatable>& updMng, Maze& maze);
        sf::Vector2f getPos() const;
        void setPos(sf::Vector2f v);
        void updatePos(sf::Vector2f v);
        void move(sf::Vector2f v);
        void moveCharacter(sf::Vector2f v, sf::Time time);
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        bool intersect(Segment v);
        virtual void update(sf::Time time) override;
        virtual ~Character() = default;

    };

#endif
