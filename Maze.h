#ifndef __MAZE__
    #define __MAZE__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>
    #include "Edge.h"
    #include "DSU.h"
    #include "Wall.h"
    #include "Consts.h"


    class Maze {
    private:
        int widthOfMatrixInVertices, heightOfMatrixInVertices;
        int widthOfMaze, heightOfMaze;
        std::vector<std::vector<bool> > maze;

        int getNumber(sf::Vector2<int> p);
        Edge newEdge(int i1, int j1, int i2, int j2);
        void makeEdgeList(std::vector<Edge> &edges);
        void findST(std::vector<Edge> &edges);
        void addRandomEdges(std::vector<Edge> &edges, int pr);
        void setVerticesCells(std::vector<Edge> &edges);

    public:
        Maze(int w, int h);

        int getWidth();
        int getHeight();
        bool isInMaze(sf::Vector2<int> v);
        bool getCell(sf::Vector2<int> v);
        std::vector<std::vector<bool> > getMaze();
    };

#endif // __MAZE__
