#include "Wall.h"

Wall::Wall(sf::Vector2<int> v): pos(v) {
    rect.setSize(sf::Vector2f(C, C));
    rect.setPosition(sf::Vector2f(C * pos.y, C * pos.x));
    rect.setFillColor(sf::Color::Red);
}

sf::Vector2<int> Wall::getPos() {
    return pos;
}

void Wall::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(rect, states);
}

Wall::~Wall() {}

