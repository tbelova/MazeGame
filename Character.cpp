#include "Character.h"

Character::Character(sf::Vector2f v, Manager<sf::Drawable>& mng):
    Manager<sf::Drawable>::Object(mng), pos(v) {
    rect.setSize(sf::Vector2f(C / 2, C / 2));
    rect.setPosition(sf::Vector2f(0, 0));
    rect.setFillColor(sf::Color::Green);
}

sf::Vector2f Character::getPos() const {
    return pos;
}

void Character::setPos(sf::Vector2f v) {
    pos = v;
}

void Character::move(sf::Vector2f v) {
    pos += v;
}

void Character::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform = sf::Transform().translate(pos.x * C + C / 4, pos.y * C + C / 4) * states.transform;
    target.draw(rect, states);
}


