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
    Edge(int p1x, int p1y, int p2x, int p2y, int w, int h): p1(p1x, p1y, w, h), p2(p2x, p2y, w, h) {}
};

template<class TVertex>
class DSU {
private:
    vector<int> p;
    int width, height;

public:
    DSU() {}
    DSU(int sz) {
        p.resize(sz);
        for (int i = 0; i < sz; ++i) p[i] = i;
    }

    int go(int v) {
        if (v == p[v]) return v;
        return p[v] = go(p[v]);
    }

    bool connected(TVertex p1, TVertex p2) {
        return go(p1.getIndex()) == go(p2.getIndex());
    }

    void join(TVertex p1, TVertex p2) {
        int idx1 = go(p1.getIndex());
        int idx2 = go(p2.getIndex());
        p[idx1] = idx2;
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

    void findST(vector<Edge> &edges, vector<bool> &inSpanningTree) {

        random_shuffle(edges.begin(), edges.end());

        inSpanningTree.resize(edges.size(), 0);

        DSU<Vertex> dsu(widthOfMatrixInVertices * heightOfMatrixInVertices);

        for (int i = 0; i < (int)edges.size(); ++i) {
            if (!dsu.connected(edges[i].p1, edges[i].p2)) {
                dsu.join(edges[i].p1, edges[i].p2);
                inSpanningTree[i] = 1;
            }
        }
    }

    void addRandomEdges(vector<Edge> &edges, vector<bool> &inSpanningTree, int pr) {
        if (pr == 0) return;
        for (int i = 0; i < (int)edges.size(); ++i) {
            if (!inSpanningTree[i] && rand() % pr == 0) inSpanningTree[i] = 1;
        }
    }

    void buildMaze(vector<Edge> &edges, vector<bool> &inSpanningTree) {

        widthOfMazeInVertices = widthOfMatrixInVertices * 2 - 1;
        heightOfMazeInVertices = heightOfMatrixInVertices * 2 - 1;

        maze.resize(widthOfMazeInVertices, vector<bool>(heightOfMazeInVertices, 0));

        for (int i = 0; i < widthOfMatrixInVertices; ++i) {
            for (int j = 0; j < heightOfMatrixInVertices; ++j) {
                maze[i * 2][j * 2] = 1;
            }
        }

        for (int i = 0; i < (int)edges.size(); ++i) {
            if (inSpanningTree[i]) {
                int p1x = edges[i].p1.x;
                int p1y = edges[i].p1.y;

                int p2x = edges[i].p2.x;
                int p2y = edges[i].p2.y;

                if (p1x > p2x) swap(p1x, p2x);
                if (p1y > p2y) swap(p1y, p2y);

                if (p1x == p2x) {
                    maze[p1x * 2][p1y * 2 + 1] = 1;
                } else {
                    maze[p1x * 2 + 1][p1y * 2] = 1;
                }
            }
        }
    }


public:
    Maze(int w, int h): widthOfMatrixInVertices(w), heightOfMatrixInVertices(h) {
        vector<Edge> edges;
        vector<bool> inSpanningTree;

        buildGraph(edges);
        findST(edges, inSpanningTree);
        addRandomEdges(edges, inSpanningTree, 10);
        buildMaze(edges, inSpanningTree);
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

