#include "Wall.h"

Wall::Wall(sf::Vector2<int> v, Manager<sf::Drawable>& mng):
    Manager<sf::Drawable>::Object(mng), pos(v) {
    rect.setSize(sf::Vector2f(WallSize, WallSize));
    rect.setPosition(sf::Vector2f(WallSize * pos.x, WallSize * pos.y));
    rect.setFillColor(sf::Color::Red);
}

sf::Vector2<int> Wall::getPos() const {
    return pos;
}

void Wall::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(rect, states);
}


