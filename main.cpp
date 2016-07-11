#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "Consts.h"
#include "Wall.h"
#include "Edge.h"
#include "DSU.h"
#include "Maze.h"

using namespace std;

class Character: public sf::Drawable {
private:
    sf::Vector2<int> pos;

public:
    Character() {}
    Character(sf::Vector2<int> v): pos(v) {}

    sf::Vector2<int> getPos() {
        return pos;
    }

    void move(sf::Vector2<int> v) {
        pos += v;
    }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        sf::RectangleShape rect(sf::Vector2f(C / 2, C / 2));
        rect.setPosition(sf::Vector2f(C * pos.y + C / 4, C * pos.x + C / 4));
        rect.setFillColor(sf::Color::Green);

        target.draw(rect, states);
    }

    virtual ~Character() {};

};

class Game {
private:
    int w, h;
    vector<sf::Drawable*> objects;
    Character character;
    Maze maze;

    void getWalls() {
        for (int i = 0; i < w; ++i) {
            for (int j = 0; j < h; ++j) {
                if (!maze.getCell(i, j)) {
                    objects.push_back(new Wall(sf::Vector2<int>(i, j)));
                }
            }
        }
    }

    void setCharacter() {
        while (true) {
            int x = rand() % w;
            int y = rand() % h;
            if (maze.getCell(x, y)) {
                character = Character(sf::Vector2<int>(x, y));
                objects.push_back(&character);

                break;
            }
        }
    }

public:
    Game(int _w, int _h) {
        maze = Maze(_w, _h);
        w = maze.getWidth();
        h = maze.getHeight();

        getWalls();
        setCharacter();
    }

    int getWidth() {
        return w;
    }

    int getHeight() {
        return h;
    }

    void moveCharacter(sf::Vector2<int> v) {
        sf::Vector2<int> newPos = character.getPos() + v;

        if (maze.getCell(newPos.x, newPos.y))
            character.move(v);
    }

    void draw(sf::RenderWindow &window) {
        for (int i = 0; i < (int)objects.size(); ++i) {
            window.draw(*objects[i]);
        }
    }

};

int main()
{
    srand(time(0));

    int n, m;
    cin >> n >> m;
    Game game(n, m);

    sf::RenderWindow window(sf::VideoMode(C * game.getHeight(), C * game.getWidth()), "MAZE");

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    game.moveCharacter(sf::Vector2<int>(0, -1));
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    game.moveCharacter(sf::Vector2<int>(0, 1));
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    game.moveCharacter(sf::Vector2<int>(-1, 0));
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    game.moveCharacter(sf::Vector2<int>(1, 0));
                }
            }
        }

        window.clear();

        game.draw(window);

        window.display();
    }

    return 0;
}

