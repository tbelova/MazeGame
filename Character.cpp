#include "Character.h"

Character::Character(sf::Vector2f v, Manager<sf::Drawable>& mng, Manager<Updatable>& updMng):
    Manager<sf::Drawable>::Object(mng), Manager<Updatable>::Object(updMng),
    pos(sf::Vector2f(v.x * WallSize + WallSize / 2, v.y * WallSize + WallSize / 2)) {

    rect.setSize(sf::Vector2f(CharSize, CharSize));
    rect.setPosition(sf::Vector2f(0, 0));
    rect.setFillColor(sf::Color::Green);

}

sf::Vector2f Character::getPos() const {
    return pos;
}

void Character::setPos(sf::Vector2f v) {
    pos = v * WallSize;
    pos.x += WallSize / 2;
    pos.y += WallSize / 2;
}

void Character::move(sf::Vector2f v) {
    pos += v;
}

void Character::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform = sf::Transform().translate(pos.x - CharSize / 2, pos.y - CharSize / 2) * states.transform;
    target.draw(rect, states);
}

void Character::moveCharacter(sf::Vector2f v, sf::Time time) {
    sf::Vector2f u = v * time.asSeconds() * speed;
    sf::Vector2f p;
    SetOfSegments::Segment s;
    segments.intersect(Ray(pos, u), p, s);
    if (sqrLength(p - pos) > sqrLength(u)) {
        move(u);
    } else {
        sf::Vector2f b = s.b - s.a;
        b *= dot_product(u, b) / sqrLength(b);
        segments.intersect(Ray(pos, b), p, s);
        if (sqrLength(p - pos) > sqrLength(b))
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

    moveCharacter(v * WallSize, time);
}


