#include "Wall.h"

Wall::Wall(sf::Vector2<float> v, Manager<sf::Drawable>& mng):
    Manager<sf::Drawable>::Object(mng), pos(v) {
    rect.setSize(sf::Vector2f(WallSize, WallSize));
    rect.setPosition(pos);
    rect.setFillColor(sf::Color::Red);
}

sf::Vector2<float> Wall::getPos() const {
    return pos;
}

void Wall::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(rect, states);
}


