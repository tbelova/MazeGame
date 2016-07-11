#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

using namespace std;

const double C = 20;

class Object {
public:
    virtual void draw(sf::RenderWindow &window) = 0;
};


class Character: public Object {
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

    virtual void draw(sf::RenderWindow &window) {
        sf::RectangleShape rect(sf::Vector2f(C / 2, C / 2));
        rect.setPosition(sf::Vector2f(C * pos.y + C / 4, C * pos.x + C / 4));
        rect.setFillColor(sf::Color::Green);

        window.draw(rect);
    }

};

class Wall: public Object {
private:
    sf::Vector2<int> pos;

public:
    Wall(sf::Vector2<int> v): pos(v) {}

    sf::Vector2<int> getPos() {
        return pos;
    }

    virtual void draw(sf::RenderWindow &window) {
        sf::RectangleShape rect(sf::Vector2f(C, C));
        rect.setPosition(sf::Vector2f(C * pos.y, C * pos.x));
        rect.setFillColor(sf::Color::Red);

        window.draw(rect);
    }

};

class Edge {
public:
    sf::Vector2<int> v1, v2;
    sf::Vector2<int> pos;

    Edge(sf::Vector2<int> v1, sf::Vector2<int> v2, sf::Vector2<int> pos): v1(v1), v2(v2), pos(pos) {}

};

class DSU {
private:
    vector<int> parent;

    int getRoot(int v) {
        if (v == parent[v]) return v;
        return parent[v] = getRoot(parent[v]);
    }

public:
    DSU(int sz) {
        parent.resize(sz);
        for (int i = 0; i < sz; ++i) parent[i] = i;
    }

    bool areConnected(int v, int u) {
        return getRoot(v) == getRoot(u);
    }

    bool join(int v, int u) {
        int pv = getRoot(v);
        int pu = getRoot(u);
        parent[pv] = pu;

        return pv != pu;
    }

};

class Maze {
private:

    int widthOfMatrixInVertices, heightOfMatrixInVertices;
    int widthOfMaze, heightOfMaze;
    vector<vector<bool> > maze;

    int getNumber(sf::Vector2<int> p) {
        return p.x * heightOfMatrixInVertices + p.y;
    }

    Edge newEdge(int i1, int j1, int i2, int j2) {
        Edge e(Edge(sf::Vector2<int>(i1, j1), sf::Vector2<int>(i2, j2),
                    sf::Vector2<int>(i1 * 2 + (j1 == j2), j1 * 2 + (i1 == i2))));

        return e;
    }

    void makeEdgeList(vector<Edge> &edges) {
        for (int i = 0; i < widthOfMatrixInVertices; ++i) {
            for (int j = 0; j < heightOfMatrixInVertices; ++j) {
                if (i < widthOfMatrixInVertices - 1) edges.push_back(newEdge(i, j, i + 1, j));
                if (j < heightOfMatrixInVertices - 1) edges.push_back(newEdge(i, j, i, j + 1));
            }
        }
    }

    void findST(vector<Edge> &edges) {

        random_shuffle(edges.begin(), edges.end());

        DSU dsu(widthOfMatrixInVertices * heightOfMatrixInVertices);

        for (auto &edge: edges) {
            if (dsu.join(getNumber(edge.v1), getNumber(edge.v2))) {
                maze[edge.pos.x][edge.pos.y] = 1;
            }
        }
    }

    void addRandomEdges(vector<Edge> &edges, int pr) {
        if (pr == 0) return;
        for (auto &edge: edges) {
            if (rand() % pr == 0) {
                maze[edge.pos.x][edge.pos.y] = 1;
            }
        }
    }

    void setVerticesCells(vector<Edge> &edges) {
        for (int i = 0; i < widthOfMatrixInVertices; ++i) {
            for (int j = 0; j < heightOfMatrixInVertices; ++j) {
                maze[i * 2][j * 2] = 1;
            }
        }
    }


public:
    Maze(int w, int h): widthOfMatrixInVertices(w), heightOfMatrixInVertices(h) {
        vector<Edge> edges;

        widthOfMaze = widthOfMatrixInVertices * 2 - 1;
        heightOfMaze = heightOfMatrixInVertices * 2 - 1;

        maze.resize(widthOfMaze, vector<bool>(heightOfMaze, 0));

        makeEdgeList(edges);
        findST(edges);
        addRandomEdges(edges, 10);
        setVerticesCells(edges);
    }

    int getWidth() {
        return widthOfMaze;
    }

    int getHeight() {
        return heightOfMaze;
    }

    vector<vector<bool> > getMaze() {
        return maze;
    }

    void getWalls(vector<vector<Object*> > &objects) {
        for (int i = 0; i < widthOfMaze; ++i) {
            for (int j = 0; j < heightOfMaze; ++j) {
                if (!maze[i][j]) {
                    objects[i][j] = new Wall(sf::Vector2<int>(i, j));
                }
            }
        }
    }

    void draw(sf::RenderWindow &window) {
        for (int i = 0; i < (int)maze.size(); ++i) {
            for (int j = 0; j < (int)maze[i].size(); ++j) {
                sf::RectangleShape shape(sf::Vector2f(C, C));
                shape.setPosition(sf::Vector2f(C * i, C * j));
                if (maze[i][j]) {
                    shape.setFillColor(sf::Color::Black);
                } else {
                    shape.setFillColor(sf::Color::Red);
                }
                window.draw(shape);
            }
        }
    }

};


class Window {
private:
    int w, h;
    vector<vector<Object*> > objects;
    Character character;

public:
    Window(int _w, int _h) {
        Maze maze(_w, _h);
        w = maze.getWidth();
        h = maze.getHeight();

        objects.resize(w, vector<Object*>(h, NULL));
        maze.getWalls(objects);
    }

    int getWidth() {
        return w;
    }

    int getHeight() {
        return h;
    }

    void setCharacter() {
        while (true) {
            int x = rand() % w;
            int y = rand() % h;
            if (!objects[x][y]) {
                character = Character(sf::Vector2<int>(x, y));
                objects[x][y] = &character;

                break;
            }
        }
    }

    void moveCharacter(sf::Vector2<int> v) {
        sf::Vector2<int> newPos = character.getPos() + v;
        if (newPos.x < 0 || newPos.y < 0 || newPos.x >= w || newPos.y >= h) return;

        if (!objects[newPos.x][newPos.y]) {
            objects[character.getPos().x][character.getPos().y] = NULL;
            objects[newPos.x][newPos.y] = &character;

            character.move(v);
        }
    }

    void draw(sf::RenderWindow &window) {
        for (int i = 0; i < w; ++i) {
            for (int j = 0; j < h; ++j) {
                if (objects[i][j])
                    objects[i][j]->draw(window);
            }
        }
    }

};

int main()
{
    srand(time(0));

    int n, m;
    cin >> n >> m;
    Window game(n, m);
    game.setCharacter();

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

