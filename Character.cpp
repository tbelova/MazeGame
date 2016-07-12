#include "Character.h"

Character::Character(sf::Vector2<int> v, Manager<sf::Drawable>& mng):
    Manager<sf::Drawable>::Object(mng), pos(v) {
    rect.setSize(sf::Vector2f(C / 2, C / 2));
    rect.setPosition(sf::Vector2f(C * pos.y + C / 4, C * pos.x + C / 4));
    rect.setFillColor(sf::Color::Green);
}

sf::Vector2<int> Character::getPos() {
    return pos;
}

void Character::setPos(sf::Vector2<int> v) {
    pos = v;
    rect.setPosition(sf::Vector2f(C * pos.y + C / 4, C * pos.x + C / 4));
}

void Character::move(sf::Vector2<int> v) {
    pos += v;
    rect.setPosition(sf::Vector2f(C * pos.y + C / 4, C * pos.x + C / 4));
}

void Character::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(rect, states);
}

Character::~Character() {};


