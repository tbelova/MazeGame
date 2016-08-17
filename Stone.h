#ifndef __STONE__
    #define __STONE__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>
    #include "Consts.h"
    #include "Manager.h"
    #include "Updatable.h"
    #include "SetOfSegments.h"
    #include "Maze.h"
    #include "Smth.h"

    class Stone: public Managable<sf::Drawable> {
    private:
        sf::Vector2f pos;
        sf::CircleShape circle;
        //sf::Texture texture;
        //const float eps = 1e-3;

    public:
        Stone(Manager<sf::Drawable>& mng, sf::Vector2f v, sf::Texture* texture):
            Manager<sf::Drawable>::Object(mng), pos(v) {

            circle.setRadius(StoneSize);
            circle.setOrigin(StoneSize, StoneSize);
            circle.setPosition(sf::Vector2f(0, 0));
            circle.setTexture(texture);
            circle.setFillColor(sf::Color(rand() % 100 + 155, rand() % 100 + 155, rand() % 100 + 155));
            circle.setRotation(rand() % 360);
        }

        sf::Vector2f getPos() const {
            return pos;
        }
        void setPos(sf::Vector2f v) {
            pos = v;
        }
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            states.transform = sf::Transform().translate(pos) * states.transform;
            target.draw(circle, states);
        }
        virtual ~Stone() = default;
    };

#endif
