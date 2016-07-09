#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

using namespace std;

const int C = 10;

class Vertex {
public:
    int x, y, width, height;

    Vertex(int x, int y, int w, int h): x(x), y(y), width(w), height(h) {}

    int getIndex() {
        return x * height + y;
    }
};


class Edge {
public:
    Vertex p1, p2;
    int idx, idy;
    bool inSpanningTree;

    Edge(int p1x, int p1y, int p2x, int p2y, int w, int h): p1(p1x, p1y, w, h), p2(p2x, p2y, w, h) {
        inSpanningTree = 0;

        if (p1x > p2x) swap(p1x, p2x);
        if (p1y > p2y) swap(p1y, p2y);

        idx = p1x * 2;
        idy = p1y * 2;

        if (p1x == p2x) {
            idy++;
        } else {
            idx++;
        }
    }
};

class DSU {
private:
    vector<int> p;
    int width, height;

    int go(int v) {
        if (v == p[v]) return v;
        return p[v] = go(p[v]);
    }

public:
    DSU(int sz) {
        p.resize(sz);
        for (int i = 0; i < sz; ++i) p[i] = i;
    }

    bool connected(int v, int u) {
        return go(v) == go(u);
    }

    void join(int v, int u) {
        p[go(v)] = go(u);
    }

};

class Maze {
private:

    int widthOfMatrixInVertices, heightOfMatrixInVertices;
    int widthOfMazeInVertices, heightOfMazeInVertices;
    vector<vector<bool> > maze;

    void addEdge(vector<Edge> &edges, int i1, int j1, int i2, int j2) {
        edges.push_back(Edge(i1, j1, i2, j2, widthOfMatrixInVertices, heightOfMatrixInVertices));
    }

    void buildGraph(vector<Edge> &edges) {
        for (int i = 0; i < widthOfMatrixInVertices; ++i) {
            for (int j = 0; j < heightOfMatrixInVertices; ++j) {
                if (i < widthOfMatrixInVertices - 1) addEdge(edges, i, j, i + 1, j);
                if (j < heightOfMatrixInVertices - 1) addEdge(edges, i, j, i, j + 1);
            }
        }
    }

    void findST(vector<Edge> &edges) {

        random_shuffle(edges.begin(), edges.end());

        DSU dsu(widthOfMatrixInVertices * heightOfMatrixInVertices);

        for (auto &edge: edges) {
            if (!dsu.connected(edge.p1.getIndex(), edge.p2.getIndex())) {
                dsu.join(edge.p1.getIndex(), edge.p2.getIndex());
                edge.inSpanningTree = 1;
            }
        }
    }

    void addRandomEdges(vector<Edge> &edges, int pr) {
        if (pr == 0) return;
        for (auto &edge: edges) {
            if (!edge.inSpanningTree && rand() % pr == 0) edge.inSpanningTree = 1;
        }
    }

    void buildMaze(vector<Edge> &edges) {

        widthOfMazeInVertices = widthOfMatrixInVertices * 2 - 1;
        heightOfMazeInVertices = heightOfMatrixInVertices * 2 - 1;

        maze.resize(widthOfMazeInVertices, vector<bool>(heightOfMazeInVertices, 0));

        for (int i = 0; i < widthOfMatrixInVertices; ++i) {
            for (int j = 0; j < heightOfMatrixInVertices; ++j) {
                maze[i * 2][j * 2] = 1;
            }
        }

        for (auto &edge: edges) {
            if (edge.inSpanningTree) {
                maze[edge.idx][edge.idy] = 1;
            }
        }
    }


public:
    Maze(int w, int h): widthOfMatrixInVertices(w), heightOfMatrixInVertices(h) {
        vector<Edge> edges;

        buildGraph(edges);
        findST(edges);
        addRandomEdges(edges, 10);
        buildMaze(edges);
    }

    int getWidth() {
        return widthOfMazeInVertices;
    }

    int getHeight() {
        return heightOfMazeInVertices;
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

