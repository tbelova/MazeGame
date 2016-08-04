#ifndef __MONSTER__
    #define __MONSTER__

    #include <bits/stdc++.h>
    #include <SFML/Graphics.hpp>
    #include "Maze.h"
    #include "Consts.h"
    #include "Character.h"

    using namespace std;

    class Monster: public Managable<sf::Drawable>, public Managable<Updatable> {
    private:

        class Path {
        private:
            vector<sf::Vector2f> pathInGame;
            vector<sf::Vector2<int> > pathInMaze;
            vector<sf::Vector2<int> > dir = {sf::Vector2<int>(0, 1),
                                             sf::Vector2<int>(1, 0),
                                             sf::Vector2<int>(0, -1),
                                             sf::Vector2<int>(-1, 0)};
            vector<vector<bool> > used;

            void dfs(sf::Vector2<int> pos, Maze& maze) {
                used[pos.x][pos.y] = 1;
                pathInMaze.push_back(pos);

                auto curDir = dir;
                random_shuffle(curDir.begin(), curDir.end());
                for (auto d: curDir) {
                    auto to = pos + d;
                    if (maze.isInMaze(to) && !used[to.x][to.y] && maze.getCell(to)) {
                        dfs(to, maze);
                    }
                }
            }

            vector<sf::Vector2<int> > bfs(sf::Vector2<int> pos, sf::Vector2<int> finish, Maze& maze) {
                vector<vector<bool> > visited;
                visited.resize(maze.getWidth(), vector<bool>(maze.getHeight(), 0));

                vector<vector<sf::Vector2<int> > > parent;
                parent.resize(maze.getWidth(), vector<sf::Vector2<int> >(maze.getHeight(), sf::Vector2<int>(-1, -1)));
                parent[pos.x][pos.y] = pos;

                queue<sf::Vector2<int> > q;

                q.push(pos);
                visited[pos.x][pos.y] = 1;

                while (!q.empty()) {
                    sf::Vector2<int> v = q.front();
                    q.pop();

                    if (v == finish) {
                        vector<sf::Vector2<int> > curPath;
                        while (parent[v.x][v.y] != v) {
                            curPath.push_back(v);
                            v = parent[v.x][v.y];
                        }
                        reverse(curPath.begin(), curPath.end());
                        return curPath;
                    }

                    for (auto curDir: dir) {
                        auto to = v + curDir;
                        if (maze.isInMaze(to) && maze.getCell(to) && !visited[to.x][to.y]) {
                            visited[to.x][to.y] = 1;
                            parent[to.x][to.y] = v;
                            q.push(to);
                        }
                    }
                }
            }

        public:

            unsigned nextStep(unsigned int step) {
                if (step == pathInGame.size() - 1) return 0;
                return step + 1;
            }

            void makePath(Maze& maze) {
                used.resize(maze.getWidth(), vector<bool>(maze.getHeight(), 0));
                dfs(sf::Vector2<int>(1, 1), maze);
                pathInMaze.push_back(pathInMaze[0]);
                for (int i = 0; i < (int)pathInMaze.size() - 1; ++i) {
                    auto newPath = bfs(pathInMaze[i], pathInMaze[i + 1], maze);
                    for (auto cell: newPath) {
                        pathInGame.push_back(FromMazeToGame(cell));
                    }
                }
            }

            sf::Vector2f getIthCell(int i) {
                return pathInGame[i];
            }

            size_t size() {
                return pathInGame.size();
            }

        } path;

        vector<vector<int> > number;
        unsigned int cur;
        sf::Vector2f curPos, nextPos, lastSeenPoint = sf::Vector2f(-1, -1);
        sf::RectangleShape rect;
        const float speed = 1.5 * WallSize;
        const float eps = 1e-5;
        Character& character;

        const unsigned int SEEZONE = 20;


    public:

        Monster(Maze& maze, Manager<sf::Drawable>& mng, Manager<Updatable>& updMng, Character& character):
            Manager<sf::Drawable>::Object(mng), Manager<Updatable>::Object(updMng),
            character(character) {

            number.resize(maze.getWidth(), vector<int>(maze.getHeight(), -1));

            path.makePath(maze);

            cur = 0;
            nextPos = curPos = path.getIthCell(0);

            for (int i = 0; i < (int)path.size(); ++i) {
                number[FromGameToMaze(path.getIthCell(i)).x][FromGameToMaze(path.getIthCell(i)).y] = i;
            }


            rect.setSize(sf::Vector2f(MonsterSize, MonsterSize));
            rect.setOrigin(MonsterSize / 2, MonsterSize / 2);
            rect.setPosition(sf::Vector2f(0, 0));
            rect.setFillColor(sf::Color::Blue);

        }

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            states.transform = sf::Transform().translate(curPos) * states.transform;
            target.draw(rect, states);
        }

        void justGo(sf::Time time) {
            nextPos = path.getIthCell(path.nextStep(cur));
            goToPoint(time);
        }

        void runToCharacter(sf::Time time) {
            nextPos = lastSeenPoint;
            goToPoint(time);
            sf::Vector2<int> posCharacter = FromGameToMaze(lastSeenPoint);
            cur = number[posCharacter.x][posCharacter.y];
            if (curPos == lastSeenPoint) lastSeenPoint = sf::Vector2f(-1, -1);
        }

        void goToCenter(sf::Time time) {
            nextPos = FromMazeToGame(FromGameToMaze(curPos));
            goToPoint(time);
        }

        void goToPoint(sf::Time time) {
            float distance = time.asSeconds() * speed;
            if (distance > Length(nextPos - curPos)) {
                curPos = nextPos;
                cur = path.nextStep(cur);
            } else {
                curPos += distance * (nextPos - curPos) / Length(nextPos - curPos);
            }
        }

        bool isSeeingCharacter() {

            rect.setFillColor(sf::Color::Blue);

            sf::Vector2<int> posCharacter = FromGameToMaze(character.getPos());
            sf::Vector2<int> posMonster = FromGameToMaze(curPos);

            if (posCharacter.x != posMonster.x
             && posCharacter.y != posMonster.y) return false;

            if (abs(posCharacter.x - posMonster.x) > SEEZONE) return false;
            if (abs(posCharacter.y - posMonster.y) > SEEZONE) return false;

            for (int z = min(posCharacter.x, posMonster.x) + 1; z < max(posCharacter.x, posMonster.x); ++z) {
                if (number[z][posCharacter.y] == -1) return false;
            }
            for (int z = min(posCharacter.y, posMonster.y) + 1; z < max(posCharacter.y, posMonster.y); ++z) {
                if (number[posCharacter.x][z] == -1) return false;
            }

            rect.setFillColor(sf::Color::Yellow);

            return true;

        }

        bool onOneLine(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c) {
            if (a == b || a == c) return true;

            sf::Vector2f v1 = (b - a) / Length(b - a);
            sf::Vector2f v2 = (c - a) / Length(c - a);

            return v1 == v2 || v1 == -v2;
        }

        virtual void update(sf::Time time) override {
            if (isSeeingCharacter()) lastSeenPoint = FromMazeToGame(FromGameToMaze(character.getPos()));
            if (lastSeenPoint.x == -1) {
                justGo(time);
            } else if (onOneLine(curPos, FromMazeToGame(FromGameToMaze(curPos)), lastSeenPoint)) {
                runToCharacter(time);
            } else {
                goToCenter(time);
            }
        }

        virtual ~Monster() = default;

    };


#endif
