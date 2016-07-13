#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "Consts.h"
#include "Wall.h"
#include "DSU.h"
#include "Maze.h"
#include "Character.h"
#include "Manager.h"

using namespace std;

class Game {
private:
    Maze maze;
    int w, h;
    Manager<sf::Drawable> mng;
    Character character;
    vector<Wall> walls;
    sf::RenderWindow window;

    void getWalls() {
        for (int i = 0; i < w; ++i) {
            for (int j = 0; j < h; ++j) {
                if (!maze.getCell(sf::Vector2<int>(i, j))) {
                    walls.push_back(Wall(sf::Vector2<int>(i, j), mng));
                }
            }
        }
    }

    void setCharacter() {
        while (true) {
            int x = rand() % w;
            int y = rand() % h;
            if (maze.getCell(sf::Vector2<int>(x, y))) {
                character.setPos(sf::Vector2<int>(x, y));

                break;
            }
        }
    }

public:
    Game(int _w, int _h):
        maze(_w, _h), w(maze.getWidth()), h(maze.getHeight()), mng(),
        character(sf::Vector2<int>(0, 0), mng), window(sf::VideoMode(C * w, C * h), "MAZE") {

        getWalls();
        setCharacter();

    }

    void moveCharacter(sf::Vector2<int> v) {
        sf::Vector2<int> newPos = character.getPos() + v;

        if (maze.isInMaze(newPos) && maze.getCell(newPos))
            character.move(v);
    }

    void draw() {
        for (auto obj: mng) {
            window.draw(*obj, sf::RenderStates());
        }
    }

    void start() {

        while (window.isOpen()) {

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::KeyPressed) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                        moveCharacter(sf::Vector2<int>(-1, 0));
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                        moveCharacter(sf::Vector2<int>(1, 0));
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                        moveCharacter(sf::Vector2<int>(0, -1));
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                        moveCharacter(sf::Vector2<int>(0, 1));
                    }
                }
            }

            window.clear();

            draw();

            window.display();
        }
    }

};

int main()
{
    srand(time(0));

    int n, m;
    cin >> n >> m;

    Game game(n, m);
    game.start();

    return 0;
}

