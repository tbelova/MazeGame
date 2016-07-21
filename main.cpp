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

using namespace std;


class Game {
private:
    sf::Vector2f winSize = sf::Vector2f(500, 500);

    Maze maze;
    int w, h;
    Manager<sf::Drawable> mng;
    Manager<Updatable> updMng;
    Character character;
    vector<Wall> walls;
    sf::RenderWindow window;
    sf::View view, viewAll;
    bool all = false;

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
                character.setPos(sf::Vector2f(x, y));

                break;
            }
        }
    }

    SetOfSegments getSegments() {

        SetOfSegments s;

        float off = 0.25;

        for (int i = 0; i < maze.getWidth(); ++i) {
            for (int j = 0; j < maze.getHeight(); ++j) {
                if (!maze.getCell(sf::Vector2<int>(i, j))) {
                    s.segments.push_back(SetOfSegments::Segment(sf::Vector2f(i - off, j - off), sf::Vector2f(i + 1 + off, j - off)));
                    s.segments.push_back(SetOfSegments::Segment(sf::Vector2f(i + 1 + off, j - off), sf::Vector2f(i + 1 + off, j + 1 + off)));
                    s.segments.push_back(SetOfSegments::Segment(sf::Vector2f(i + 1 + off, j + 1 + off), sf::Vector2f(i - off, j + 1 + off)));
                    s.segments.push_back(SetOfSegments::Segment(sf::Vector2f(i - off, j + 1 + off), sf::Vector2f(i - off, j - off)));
                }
            }
        }
/*
        s.segments.push_back(SetOfSegments::Segment(sf::Vector2f(off, 0), sf::Vector2f(off, maze.getHeight())));
        s.segments.push_back(SetOfSegments::Segment(sf::Vector2f(0, off), sf::Vector2f(maze.getWidth(), off)));
        s.segments.push_back(SetOfSegments::Segment(sf::Vector2f(maze.getWidth() - off, 0), sf::Vector2f(maze.getWidth() - off, maze.getHeight())));
        s.segments.push_back(SetOfSegments::Segment(sf::Vector2f(0, maze.getHeight() + off), sf::Vector2f(maze.getWidth(), maze.getHeight() + off)));
*/
        return s;

    }

public:
    Game(int _w, int _h):
        maze(_w, _h), w(maze.getWidth()), h(maze.getHeight()), mng(), updMng(),
        character(sf::Vector2f(0, 0), mng, updMng), window(sf::VideoMode(winSize.x, winSize.y), "MAZE") {

        character.segments = getSegments();
        getWalls();
        setCharacter();

        viewAll.setCenter(sf::Vector2f(w * C / 2, h * C / 2));
        viewAll.setSize(sf::Vector2f(w * C, h * C));

    }

    void draw() {
        view.setSize(sf::Vector2f(200, 200));
        view.setCenter(character.getRealPos());

        if (all)
            window.setView(viewAll);
        else window.setView(view);

        for (auto obj: mng) {
            window.draw(*obj, sf::RenderStates());
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

