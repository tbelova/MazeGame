#include "Character.h"

Character::Character(sf::Vector2f v, Manager<sf::Drawable>& mng, Manager<Updatable>& updMng):
    Manager<sf::Drawable>::Object(mng), Manager<Updatable>::Object(updMng), pos(v) {
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

void Character::moveCharacter(sf::Vector2f v, sf::Time time) {
    move(v * time.asSeconds() * speed);
}

void Character::update(sf::Time time) {
    sf::Vector2f v;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        v += sf::Vector2f(-1, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        v += sf::Vector2f(1, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        v += sf::Vector2f(0, -1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        v += sf::Vector2f(0, 1);

    if (v != sf::Vector2f(0, 0))
        moveCharacter(v / std::sqrt(v.x * v.x + v.y * v.y), time);
}


