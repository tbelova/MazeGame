#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "Consts.h"
#include "Wall.h"
#include "DSU.h"
#include "Maze.h"
#include "Character.h"
#include "Manager.h"
#include "Updatable.h"
#include "SetOfSegments.h"
#include "Smth.h"
#include "Monster.h"
#include "Light.h"

using namespace std;

class Game {
private:
    sf::Vector2f winSize = sf::Vector2f(500, 500);

    Maze maze;
    double w, h;
    Manager<sf::Drawable> mng;
    Manager<Updatable> updMng;
    Character character;
    Monster monster;
    vector<Wall> walls;
    sf::RenderWindow window;
    sf::View view, viewAll;
    bool all = false;
    Light light;
    sf::Vector2f ViewSize = sf::Vector2f(10, 10);

    void getWalls() {
        for (int i = 0; i < maze.getWidth(); ++i) {
            for (int j = 0; j < maze.getHeight(); ++j) {
                if (!maze.getCell(sf::Vector2<int>(i, j))) {
                    walls.push_back(Wall(sf::Vector2f(WallSize * i, WallSize * j), mng));
                }
            }
        }
    }

    void setCharacter() {
        while (true) {
            int x = rand() % maze.getWidth();
            int y = rand() % maze.getHeight();
            if (maze.getCell(sf::Vector2<int>(x, y))) {
                character.setPos(sf::Vector2f(x * WallSize + WallSize / 2, y * WallSize + WallSize / 2));

                break;
            }
        }
    }

    void getSegments() {

        SetOfSegments s;

        float off = CharSize / 2;

        for (int i = 0; i < maze.getWidth(); ++i) {
            for (int j = 0; j < maze.getHeight(); ++j) {
                if (!maze.getCell(sf::Vector2<int>(i, j))) {
                    vector<sf::Vector2f> points;
                    points.push_back(sf::Vector2f(WallSize * i - off, WallSize * j - off));
                    points.push_back(sf::Vector2f(WallSize * (i + 1) + off, WallSize * j - off));
                    points.push_back(sf::Vector2f(WallSize * (i + 1) + off, WallSize * (j + 1) + off));
                    points.push_back(sf::Vector2f(WallSize * i - off, WallSize * (j + 1) + off));
                    points.push_back(sf::Vector2f(WallSize * i - off, WallSize * j - off));

                    for (int k = 0; k < 4; ++k) {
                        character.segments.Add(SetOfSegments::Segment(points[k], points[k + 1]));
                    }

                }
            }
        }

    }

    void buildBigView() {

        viewAll.setCenter(sf::Vector2f(w / 2, h / 2));
        viewAll.setSize(sf::Vector2f(w, h));

        double w1, h1;

        if ((double)w / h > winSize.x / winSize.y) {
            w1 = winSize.x;
            h1 = h * winSize.x / w;
        } else {
            w1 = w * winSize.y / h;
            h1 = winSize.y;
        }

        viewAll.setViewport(sf::FloatRect(0.5 - w1 / winSize.x / 2, 0.5 - h1 / winSize.y / 2, w1 / winSize.x, h1 / winSize.y));

    }

public:
    Game(int _w, int _h):
        maze(_w, _h), w(maze.getWidth() * WallSize), h(maze.getHeight() * WallSize), mng(), updMng(),
        character(sf::Vector2f(0, 0), mng, updMng), monster(maze, mng, updMng),
        window(sf::VideoMode(winSize.x, winSize.y), "MAZE") {

        getSegments();
        getWalls();
        setCharacter();

        buildBigView();
        view.setSize(ViewSize);

    }

    void draw() {

        sf::RenderStates states;

        if (all) {
            window.setView(viewAll);
        } else {
            view.setCenter(character.getPos());

            window.setView(view);

            light.setWalls(walls);
            light.setCenter(character.getPos());
            light.setView(character.getPos() - ViewSize / (float)2, ViewSize);
            light.makeLight(window);

            states.blendMode = sf::BlendMultiply;

        }

        for (auto obj: mng) {
            window.draw(*obj, states);
        }
    }

    void update(sf::Time time) {
        for (auto obj: updMng) {
            obj->update(time);
        }
    }

    void start() {

        sf::Clock clock;

        //clock.restart();
        while (window.isOpen()) {

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::KeyPressed) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                        all = !all;
                    }
                }
            }

            update(clock.restart());

            window.clear();

            draw();

            window.display();

        }
    }

};

int main()
{
   // srand(time(0));

    int n, m;
    cin >> n >> m;

    Game game(n, m);
    game.start();

    return 0;
}

