#include "Maze.h"

int Maze::getNumber(sf::Vector2<int> p) {
    return p.x * heightOfMatrixInVertices + p.y;
}

Edge Maze::newEdge(int i1, int j1, int i2, int j2) {
    Edge e(Edge(sf::Vector2<int>(i1, j1), sf::Vector2<int>(i2, j2),
                sf::Vector2<int>(i1 * 2 + (j1 == j2), j1 * 2 + (i1 == i2))));

    return e;
}

void Maze::makeEdgeList(std::vector<Edge> &edges) {
    for (int i = 0; i < widthOfMatrixInVertices; ++i) {
        for (int j = 0; j < heightOfMatrixInVertices; ++j) {
            if (i < widthOfMatrixInVertices - 1) edges.push_back(newEdge(i, j, i + 1, j));
            if (j < heightOfMatrixInVertices - 1) edges.push_back(newEdge(i, j, i, j + 1));
        }
    }
}

void Maze::findST(std::vector<Edge> &edges) {

    random_shuffle(edges.begin(), edges.end());

    DSU dsu(widthOfMatrixInVertices * heightOfMatrixInVertices);

    for (auto &edge: edges) {
        if (dsu.join(getNumber(edge.v1), getNumber(edge.v2))) {
            maze[edge.pos.x][edge.pos.y] = 1;
        }
    }
}

void Maze::addRandomEdges(std::vector<Edge> &edges, int pr) {
    if (pr == 0) return;
    for (auto &edge: edges) {
        if (rand() % pr == 0) {
            maze[edge.pos.x][edge.pos.y] = 1;
        }
    }
}

void Maze::setVerticesCells(std::vector<Edge> &edges) {
    for (int i = 0; i < widthOfMatrixInVertices; ++i) {
        for (int j = 0; j < heightOfMatrixInVertices; ++j) {
            maze[i * 2][j * 2] = 1;
        }
    }
}

Maze::Maze(int w, int h): widthOfMatrixInVertices(w), heightOfMatrixInVertices(h) {
    std::vector<Edge> edges;

    widthOfMaze = widthOfMatrixInVertices * 2 - 1;
    heightOfMaze = heightOfMatrixInVertices * 2 - 1;

    maze.resize(widthOfMaze, std::vector<bool>(heightOfMaze, 0));

    makeEdgeList(edges);
    findST(edges);
    addRandomEdges(edges, 10);
    setVerticesCells(edges);
}

int Maze::getWidth() {
    return widthOfMaze;
}

int Maze::getHeight() {
    return heightOfMaze;
}

bool Maze::isInMaze(sf::Vector2<int> v) {
    return !(v.x < 0 || v.y < 0 || v.x >= Maze::widthOfMaze || v.y >= Maze::heightOfMaze);
}

bool Maze::getCell(sf::Vector2<int> v) {
    return maze[v.x][v.y];
}

