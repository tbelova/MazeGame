#include "Character.h"

Character::Character(sf::Vector2f v, Manager<sf::Drawable>& mng, Manager<Updatable>& updMng):
    Manager<sf::Drawable>::Object(mng), Manager<Updatable>::Object(updMng), pos(v) {

    rect.setSize(sf::Vector2f(CharSize, CharSize));
    rect.setOrigin(CharSize / 2, CharSize / 2);
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
    states.transform = sf::Transform().translate(pos) * states.transform;
    target.draw(rect, states);
}

void Character::moveCharacter(sf::Vector2f v, sf::Time time) {
    sf::Vector2f u = v * time.asSeconds() * speed;
    SetOfSegments::HZ hz = segments.intersect(pos, u);
    if (sqrLength(hz.point - pos) > sqrLength(u)) {
        move(u);
    } else {
        sf::Vector2f b = hz.segment.b - hz.segment.a;
        b *= dot_product(u, b) / sqrLength(b);
        hz = segments.intersect(pos, b);
        if (sqrLength(hz.point - pos) > sqrLength(b))
            move(b);
    }
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

    if (v == sf::Vector2f(0, 0)) return;

    v /= Length(v);

    moveCharacter(v, time);
}


