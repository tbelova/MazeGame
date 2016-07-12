#include "Wall.h"

Wall::Wall(sf::Vector2<int> v, Manager<sf::Drawable>& mng):
    Manager<sf::Drawable>::Object(mng), pos(v) {
    rect.setSize(sf::Vector2f(C, C));
    rect.setPosition(sf::Vector2f(C * pos.y, C * pos.x));
    rect.setFillColor(sf::Color::Red);
}

sf::Vector2<int> Wall::getPos() {
    return pos;
}

void Wall::setPos(sf::Vector2<int> v) {
    pos = v;
}

void Wall::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(rect, states);
}

Wall::~Wall() {}

