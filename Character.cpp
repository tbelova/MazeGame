#include "Character.h"

Character::Character(sf::Vector2f v, Manager<sf::Drawable>& mng, Manager<Updatable>& updMng, Maze& maze):
    Manager<sf::Drawable>::Object(mng), Manager<Updatable>::Object(updMng), pos(v + sf::Vector2f(0.5, 0.5)) {

    rect.setSize(sf::Vector2f(C / 2, C / 2));
    rect.setPosition(sf::Vector2f(0, 0));
    rect.setFillColor(sf::Color::Green);

    for (int i = 0; i < maze.getWidth(); ++i) {
        for (int j = 0; j < maze.getHeight(); ++j) {
            if (!maze.getCell(sf::Vector2<int>(i, j))) {
                segments.push_back(Segment(sf::Vector2f(i, j), sf::Vector2f(i + 1, j)));
                segments.push_back(Segment(sf::Vector2f(i + 1, j), sf::Vector2f(i + 1, j + 1)));
                segments.push_back(Segment(sf::Vector2f(i + 1, j + 1), sf::Vector2f(i, j + 1)));
                segments.push_back(Segment(sf::Vector2f(i, j + 1), sf::Vector2f(i, j)));
            }
        }
    }
    segments.push_back(Segment(sf::Vector2f(0, 0), sf::Vector2f(0, maze.getWidth())));
    segments.push_back(Segment(sf::Vector2f(0, 0), sf::Vector2f(maze.getHeight(), 0)));
    segments.push_back(Segment(sf::Vector2f(maze.getWidth(), 0), sf::Vector2f(maze.getHeight(), maze.getWidth())));
    segments.push_back(Segment(sf::Vector2f(0, maze.getHeight()), sf::Vector2f(maze.getHeight(), maze.getWidth())));
}

sf::Vector2f Character::getPos() const {
    return pos;
}

void Character::setPos(sf::Vector2f v) {
    pos = v + sf::Vector2f(0.5, 0.5);
}

void Character::updatePos(sf::Vector2f v) {
    pos = v;
}

void Character::move(sf::Vector2f v) {
    pos += v;
}

void Character::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform = sf::Transform().translate((pos.x - 0.5) * C + C / 4, (pos.y - 0.5) * C + C / 4) * states.transform;
    target.draw(rect, states);
}

void Character::moveCharacter(sf::Vector2f v, sf::Time time) {
    sf::Vector2f u = v * time.asSeconds() * speed;
    sf::Vector2f p;
    Ray(pos, pos + u).intersect(segments, p);
    if ((p.x - pos.x) * (p.x - pos.x) + (p.y - pos.y) * (p.y - pos.y) > u.x * u.x + u.y * u.y)
        move(u);
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

    v /= std::sqrt(v.x * v.x + v.y * v.y);
    moveCharacter(v, time);
}


