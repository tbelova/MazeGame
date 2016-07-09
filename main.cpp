#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

using namespace std;

const int C = 10;

class Edge {
public:
    sf::Vector2<int> v1, v2;
    sf::Vector2<int> pos;

    Edge(sf::Vector2<int> v1, sf::Vector2<int> v2): v1(v1), v2(v2) {}

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
        Edge e(Edge(sf::Vector2<int>(i1, j1), sf::Vector2<int>(i2, j2)));
        e.pos = sf::Vector2<int>(i1 * 2 + (j1 == j2), j1 * 2 + (i1 == i2));

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

int main()
{
    srand(time(0));

    int n, m;
    cin >> n >> m;
    Maze maze(n, m);

    sf::RenderWindow window(sf::VideoMode(C * maze.getWidth(), C * maze.getHeight()), "MAZE");

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        maze.draw(window);

        window.display();
    }

    return 0;
}

