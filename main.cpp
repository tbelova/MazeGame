#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

using namespace std;

const int C = 10;

class Maze {
private:

    int w, h;
    vector<pair<int, int> > e;
    vector<bool> st;

    inline void addEdge(int i, int j, int i2, int j2) {
        e.push_back({i * h + j, i2 * h + j2});
    }

    void buildGraph() {
        for (int i = 0; i < w; ++i) {
            for (int j = 0; j < h; ++j) {
                if (i < w - 1) addEdge(i, j, i + 1, j);
                if (j < h - 1) addEdge(i, j, i, j + 1);
            }
        }
    }

    vector<int> p;

    int go(int v) {
        if (v == p[v]) return v;
        return p[v] = go(p[v]);
    }

    void findST() {
        srand(time(0));
        random_shuffle(e.begin(), e.end());

        st.resize(e.size(), 0);

        p.resize(e.size());
        for (int i = 0; i < (int)e.size(); ++i) p[i] = i;
        for (int i = 0; i < (int)e.size(); ++i) {
            int v = go(e[i].first);
            int u = go(e[i].second);
            if (v != u) {
                p[v] = u;
                st[i] = 1;
            }
        }
    }

    void addRandomEdges(int pr) {
        if (pr == 0) return;
        for (int i = 0; i < (int)e.size(); ++i) {
            if (!st[i] && rand() % pr == 0) st[i] = 1;
        }
    }

    vector<vector<int> > maze;

    void buildMaze() {
        maze.resize(w * 2 - 1);
        for (int i = 0; i < (int)maze.size(); ++i) {
            maze[i].resize(h * 2 - 1, 2);
        }
        for (int i = 0; i < w; ++i) {
            for (int j = 0; j < h; ++j) {
                maze[i * 2][j * 2] = 1;
            }
        }
        for (int i = 0; i < (int)e.size(); ++i) {
            int p1x = e[i].first / h;
            int p1y = e[i].first % h;

            int p2x = e[i].second / h;
            int p2y = e[i].second % h;

            if (p1x > p2x) swap(p1x, p2x);
            if (p1y > p2y) swap(p1y, p2y);

            if (p1x == p2x) {
                maze[p1x * 2][p1y * 2 + 1] = st[i];
            } else {
                maze[p1x * 2 + 1][p1y * 2] = st[i];
            }
        }
    }


public:
    Maze(): w(0), h(0) {}

    Maze(int w, int h): w(w), h(h) {
        buildGraph();
        findST();
        addRandomEdges(10);
        buildMaze();
    }

    int getW() {
        return w * 2 - 1;
    }

    int getH() {
        return h * 2 - 1;
    }

    void draw(sf::RenderWindow &window) {
        for (int i = 0; i < (int)maze.size(); ++i) {
            for (int j = 0; j < (int)maze[i].size(); ++j) {
                sf::RectangleShape shape(sf::Vector2f(C, C));
                shape.setPosition(sf::Vector2f(C * i, C * j));
                if (maze[i][j] == 1) {
                    shape.setFillColor(sf::Color::Black);
                } else { //if (maze[i][j] == 0) {
                    shape.setFillColor(sf::Color::Red);
                } /*else {
                    shape.setFillColor(sf::Color::White);
                }*/
                window.draw(shape);
            }
        }
    }

};

int main()
{
    int n, m;
    cin >> n >> m;
    Maze maze(n, m);

    sf::RenderWindow window(sf::VideoMode(C * maze.getW(), C * maze.getH()), "MAZE");

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

